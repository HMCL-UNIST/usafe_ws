#include "ros/ros.h"
#include "std_msgs/String.h"
#include "std_msgs/Int32.h"

#include <iostream>
#include <string>
#include <sstream>

#include "hmcl_v2x/HMCL_SPAT.h"
#include "hmcl_v2x/HMCL_SPATdata.h"
#include "hmcl_v2x/HMCL_PVD.h"
#include <time.h>
#include "v2x_info.h"

using namespace std;


V2XInfo::V2XInfo(ros::NodeHandle& nh, ros::NodeHandle& nh_local): 
    nh_(nh), nh_local_(nh_local)
{  
    pub_spat = nh_.advertise<hmcl_v2x::HMCL_SPAT>("SPAT", 10);
    sub_pvd = nh_local_.subscribe("/pvd", 1, &V2XInfo::car_info_callback,this);
    timer_ = nh_.createTimer(ros::Duration(0.001), &V2XInfo::connect_handler,this);    

    txPvd = get_clock_time();
    txBsm = get_clock_time();

    ROS_INFO("V2X Info Publisher Initialization");
}

V2XInfo::~V2XInfo()
{}

void V2XInfo::connect_handler(const ros::TimerEvent& time){
    // std::cout << "Debugging \n" <<std::endl;
    // 소켓이 연결되지 않은 경우(sockFd == -1) , OBU TCP 소켓 연결 시도

    if(sockFd < 0)
    {
        // sockFd = connect_obu_uper_tcp("192.168.10.10",23000); // OBU
        sockFd = connect_obu_uper_tcp("118.45.183.36",23000); // Test Server

        storedSize = 0;
        
        // printf("main function sockFd is : [%d] \n", sockFd);
        if(sockFd < 0){
            std::cout <<"DEBUG : connect failed, retry \n"<< std::endl;
            sleep(1);
            return;
        } 
    }
    if (((storedSize = receive_from_obu(sockFd, rxBuffer, OBU_RECEIVE_BUFFER_SIZE, storedSize, rxUperBuffer, MAX_UPER_SIZE, &uperSize)) < 0) || (tx_v2i_pvd(sockFd,&txPvd) < 0))
    {
        // OBU와 TCP 연결이 끊어진 경우, 연결 재시도
        close(sockFd);
        sockFd = -1;
        return;
    }
    parse_wave_msg();
}

unsigned long long V2XInfo::get_clock_time(){  
    struct timespec ts;
    clock_gettime(CLOCK_REALTIME, &ts);  
    uint64_t clock = ts.tv_sec * 1000 + (ts.tv_nsec / 1000000); 
    return clock;
}  

int V2XInfo::connect_obu_uper_tcp(char*ip, unsigned short port)
{
    // 소켓 파일디스크립터 생성
    sockFd = socket(PF_INET, SOCK_STREAM, 0);
    
    // 소켓 생성이 실패 여부 확인
    if (sockFd < 0)
    {
        std::cout << "DEBUG : step sock create error\n" <<std::endl;
        return -1;
    }

    // TCP 서버 주소, 포트 입력
    struct sockaddr_in addr; 
    memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = inet_addr(ip);
    addr.sin_port = htons(port);

    // connection error : here (no reachable)

    // TCP 서버 연결 
    if (connect(sockFd, (struct sockaddr *)&addr, sizeof(addr)) < 0)
    {
        std::cout << "DEBUG : step sock create error\n" <<std::endl;
        close(sockFd);
        return -1;
    }

    // 논 블록킹 소켓으로 동작
    int flag = fcntl(sockFd, F_GETFL, 0);
    fcntl(sockFd, F_SETFL, flag | O_NONBLOCK);

    return sockFd;
}

int V2XInfo::receive_from_obu(int sockFd, char *buffer, unsigned short bufferSize, int storedSize,
                     char *uperBuffer, unsigned short uperBufferSize, int *uperRes)
{
    int rxSize = -1;

    *uperRes = 0;

    if(sockFd < 0)
        return rxSize;

    int leftBufferSize = bufferSize - storedSize;

    if(leftBufferSize <= 0)
    {
        return -1;
    }

    rxSize = read(sockFd, buffer + storedSize, leftBufferSize);

    //read 리턴값이 0 인 경우, Socket 로부터 Read가 불가능한 상태를 의미하며,
    //대표적으로 소켓 연결이 종료된 상태가 있음
    //리턴값이 -1 인 경우, non-blocking 소켓에 대해 수신된 데이터가 존재하지 않는 경우를 의미
    if (rxSize == 0) 
    {
        return -1; 
    }

    if(rxSize < 0 && storedSize == 0)
    {
        return 0;
    }
    
    if(rxSize > 0)
    {
        storedSize += rxSize; 
    }
    // CEST OBU TCP 헤더 파싱 부문
    int headerByteLen = sizeof(struct CestObuUperPacketHeader); 
    int packetLen = headerByteLen;
    if(storedSize < headerByteLen){
        return storedSize;
    } 
    struct CestObuUperPacketHeader header;
    memcpy(&header,buffer,headerByteLen);
    
    packetLen += header.payloadLen;

    if (storedSize < packetLen) 
        return storedSize; 

    memcpy(uperBuffer,buffer + headerByteLen,header.payloadLen);
    *uperRes = header.payloadLen;
    
    storedSize -= packetLen;
    memcpy(buffer,buffer+packetLen,storedSize);

    if(header.messageType == 0x3411)
    {
        struct TxWaveUperResultPayload *payload = (struct TxWaveUperResultPayload*)uperBuffer;
        *uperRes = 0;
    }

    return storedSize;
}

int V2XInfo::request_tx_wave_obu(int sockFd, char *uper,unsigned short uperLength)
{
    if(sockFd < 0)
        return -1;

    int packetLen = uperLength + sizeof(struct CestObuUperPacketHeader);

    char packet[OBU_RECEIVE_BUFFER_SIZE];  // tcp header size + uper binary size 

    struct CestObuUperPacketHeader *ptrHeader = (struct CestObuUperPacketHeader *)&packet[0];
    ptrHeader->messageType = 0x4311;
    ptrHeader->seq = packetSeq++;
    ptrHeader->payloadLen = uperLength;
    ptrHeader->deviceType = 0xCE;
    memcpy(ptrHeader->deviceId,clientDeviceId,3);

    memcpy(packet + sizeof(struct CestObuUperPacketHeader), uper, uperLength);
    
    int res = write(sockFd,packet,packetLen);
    
    if (res > 0)
    {
        if (res != packetLen)
        {            
            printf("DEBUG tcp tx purge\n");
            return -1;
        }else
        {
            return res;
        }
    }
}

// vehicle to OBU
int V2XInfo::tx_v2i_pvd(int sockFd, unsigned long long *time)
{ 
    unsigned long long interval = get_clock_time() - *time;  // msec;

    if(interval < PVD_INTERVAL)
        return 0;
    
    *time += (interval - interval%PVD_INTERVAL); 
 
    MessageFrame_t msg;
    char uper[MAX_UPER_SIZE]; 
    cur_pTimeInfo = localtime(&rawTime);

    fill_j2735_pvd(&msg, cur_lat,  cur_lon,  cur_alt,  cur_dir,  cur_vel , cur_gear,
                        prev_lat, prev_lon, prev_alt, prev_dir, prev_vel, prev_gear,
                        cur_pTimeInfo, prev_pTimeInfo);
   
    int encodedBits = encode_j2735_uper(uper,MAX_UPER_SIZE,&msg);
 
    if(encodedBits < 0) // 인코딩 실패로 전송이 불가능한 상태
        return 0;
     
    int byteLen = encodedBits / 8 + ((encodedBits % 8)? 1:0);

    return request_tx_wave_obu(sockFd,uper,byteLen);
}

int V2XInfo::tx_v2v_bsm(int sockFd, unsigned long long *time){

    unsigned long long interval = get_clock_time() - *time;
 
    if(interval < BSM_INTERVAL)
        return 0; 
    
    *time += (interval - interval%BSM_INTERVAL);

    MessageFrame_t *msg = (MessageFrame_t *)malloc(sizeof(MessageFrame_t)); 
    char uper[MAX_UPER_SIZE]; 

    fill_j2735_bsm(msg);

    int encodedBits = encode_j2735_uper(uper,MAX_UPER_SIZE,msg);
    
    if (encodedBits < 0) 
        return 0;

    int byteLen = encodedBits / 8 + ((encodedBits % 8)? 1:0);

    return request_tx_wave_obu(sockFd, uper, byteLen);
}


void V2XInfo::parse_wave_msg()
{
    // cout<<"uperSize "<< uperSize << " rxUperBuffer " << rxUperBuffer[0]<< "::: asmdk " << "\n "<< endl;
    if (uperSize > 0)
    {
        printf("[INFO]  WAVE Message Received\n");
        MessageFrame_t *msgFrame = NULL;
        std_msgs::String msg;

        decode_j2735_uper(msgFrame, rxUperBuffer, uperSize);
        ASN_STRUCT_FREE(asn_DEF_MessageFrame, msgFrame);
    }
}

int V2XInfo::decode_j2735_uper(MessageFrame_t *dst, char *src, int size)
{
    int res = -1;
    MessageFrame_t *ptrMsg = NULL; 

    asn_dec_rval_t ret = uper_decode(NULL, &asn_DEF_MessageFrame, (void **)&dst, src, size, 0, 0);

    if (ret.code != RC_OK)
        return res;    
    res = ret.consumed;

    // asn_fprint(stdout,&asn_DEF_MessageFrame,dst);
    parse_decoded_j2735(dst);

    return res;
}

void V2XInfo::parse_decoded_j2735(MessageFrame_t *msg)
{   
    switch(msg->messageId){
        case DSRC_ID_BSM:
            // cout << ">> Parse J2735 : BSM\n"<< endl;
            break;
        case DSRC_ID_SPAT:
            // cout << ">> Parse J2735 : SPAT\n"<< endl;
            parse_spat(&msg->value.choice.SPAT);
            break;  
        case DSRC_ID_MAP:
            // cout << ">> Parse J2735 : MAP\n"<< endl;
            // parse_map(&msg->value.choice.MapData);
            break;
    }
}

void V2XInfo::parse_map(MapData_t *map)
{
    for (int i = 0; i < map->intersections->list.count; i++)
    {
        struct IntersectionGeometry *ptr= map->intersections->list.array[i];
        
    }
}

void V2XInfo::parse_spat(SPAT_t *spat)
{
    for (int i = 0; i < spat->intersections.list.count; i++)
    {
        struct IntersectionState *ptr = spat->intersections.list.array[i]; 
        hmcl_v2x::HMCL_SPAT msg;

        msg.name = "KIAPI SPAT";
        msg.id = ptr->id.id;
        for (int k = 0; k <ptr->states.list.count; k++)
        {              
            hmcl_v2x::HMCL_SPATdata msg_state;  
            std::stringstream ss;
            ss<< ptr->states.list.array[k]->movementName->buf[0]<<ptr->states.list.array[k]->movementName->buf[1]<<ptr->states.list.array[k]->movementName->buf[2];

            msg_state.states= k;
            msg_state.movementName=ss.str();
            msg_state.signalGroup= ptr->states.list.array[k]->signalGroup;
            msg_state.eventState= ptr->states.list.array[k]->state_time_speed.list.array[0]->eventState;
            msg_state.timing_min_End_Time= ptr->states.list.array[k]->state_time_speed.list.array[0]->timing->minEndTime/10;
            msg_state.connectionID=ptr->states.list.array[k]->maneuverAssistList->list.array[0]->connectionID;
            msg_state.pedBicycleDetect=ptr->states.list.array[k]->maneuverAssistList->list.array[0]->pedBicycleDetect[0];
            msg.States.push_back(msg_state);
        }            
        pub_spat.publish(msg);
    }    
}

int V2XInfo::encode_j2735_uper(char *dst, unsigned short dstLen, MessageFrame_t *src)
{
    int res = -1;
    
    asn_enc_rval_t ret = uper_encode_to_buffer(&asn_DEF_MessageFrame, NULL, src, dst, dstLen);
    
    if (ret.encoded > 0)
        return ret.encoded; //  UPER Encoding Success
    else
    { 
        if (ret.failed_type != NULL)
            printf("encoded error value name = %s\n", ret.failed_type->name);

        return -1; // UPER Encoding failed
    }
}

void V2XInfo::car_info_callback(const hmcl_v2x::HMCL_PVD& msg)
{
    prev_lat=cur_lat;
    prev_lon=cur_lon;
    prev_alt=cur_alt;
    prev_dir=cur_dir;
    prev_vel=cur_vel;
    prev_gear=cur_gear;
    cur_lat = msg.lat;
    cur_lon = msg.lon; 
    cur_alt = msg.alt;
    cur_dir = msg.dir;
    cur_vel = msg.vel;
    cur_gear = msg.gear;

    prev_pTimeInfo = cur_pTimeInfo;
    cur_pTimeInfo = localtime(&rawTime);
}

int main (int argc, char** argv)
{
    ros::init(argc, argv, "Info_pub");
    ros::NodeHandle nh, nhlocal;
    V2XInfo V2XInfo(nh, nhlocal);

    ros::CallbackQueue callback_queue_nh, callback_queue_nh_local_path;
    nh.setCallbackQueue(&callback_queue_nh);
    nhlocal.setCallbackQueue(&callback_queue_nh_local_path);

    std::thread spinner_thread_nh([&callback_queue_nh]()
    {
    ros::SingleThreadedSpinner spinner_nh;
    spinner_nh.spin(&callback_queue_nh);
    });

    std::thread spinner_thread_nh_local_path([&callback_queue_nh_local_path]() {
    ros::SingleThreadedSpinner spinner_nh_local_path;
    spinner_nh_local_path.spin(&callback_queue_nh_local_path);
    });

    ros::spin();

    spinner_thread_nh.join();
    spinner_thread_nh_local_path.join();

    return 0;

}
