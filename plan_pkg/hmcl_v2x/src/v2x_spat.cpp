#include "v2x_spat.h"
using namespace std;
V2XSPAT::V2XSPAT(ros::NodeHandle& nh, ros::NodeHandle& nh_local): 
    nh_(nh), nh_local_(nh_local)
{  
    pub_spat = nh_.advertise<v2x_msgs::SPAT>("SPAT", 1);

    // ros::Rate loop_rate(1);

    ROS_INFO("V2X Info Publisher Initialization");
    boost::thread while_loop(&V2XSPAT::whilecallback,this); 
}

V2XSPAT::~V2XSPAT()
{}

void V2XSPAT::whilecallback(){
ros::Rate loop_rate(100);
    while(ros::ok())
    {    
        // 소켓이 연결되지 않은 경우(sockFd == -1) , OBU TCP 소켓 연결 시도
        if(sockFd < 0)
        {
            sockFd = connect_obu_uper_tcp("192.168.10.10",23000); // OBU
            // sockFd = connect_obu_uper_tcp("118.45.183.36",23000); // Test Server

            storedSize = 0;
            
            if(sockFd < 0){
                std::cout <<"DEBUG : connect failed, retry \n"<< std::endl;
                sleep(0.1);
                continue;
            } 
        }
        if ((storedSize = receive_from_obu(sockFd, rxBuffer, OBU_RECEIVE_BUFFER_SIZE, storedSize, rxUperBuffer, MAX_UPER_SIZE, &uperSize)) < 0)
        {
            // OBU와 TCP 연결이 끊어진 경우, 연결 재시도
            close(sockFd);
            sockFd = -1;
            loop_rate.sleep();
            continue;
        }
        
        if (uperSize > 0)
        {
            printf("[HMCL] UPER Decoding...\n");
            // OBU로부터 수신된 WAVE 메시지가 존재할 경우, UPER 디코딩 -> J2735 메시지 파싱
            MessageFrame_t *msgFrame = NULL;
            decode_j2735_uper(msgFrame, rxUperBuffer, uperSize);
            // ASN_STRUCT_FREE(asn_DEF_MessageFrame, msgFrame);
            loop_rate.sleep();
        }

        loop_rate.sleep();
    }
}


unsigned long long V2XSPAT::get_clock_time(){  
    struct timespec ts;
    clock_gettime(CLOCK_REALTIME, &ts);  
    uint64_t clock = ts.tv_sec * 1000 + (ts.tv_nsec / 1000000); 
    return clock;
}  

int V2XSPAT::connect_obu_uper_tcp(char*ip, unsigned short port)
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

int V2XSPAT::receive_from_obu(int sockFd, char *buffer, unsigned short bufferSize, int storedSize,
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


int V2XSPAT::decode_j2735_uper(MessageFrame_t *dst, char *src, int size)
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

void V2XSPAT::parse_decoded_j2735(MessageFrame_t *msg)
{   
    cout << msg->messageId <<endl; 
    switch(msg->messageId){
        case DSRC_ID_BSM:
            // cout << ">> Parse J2735 : BSM\n"<< endl;
            break;
        case DSRC_ID_SPAT:
            cout << ">> Parse J2735 : SPAT\n"<< endl;
            parse_spat(&msg->value.choice.SPAT);
            break;  
        case DSRC_ID_MAP:
            // cout << ">> Parse J2735 : MAP\n"<< endl;
            break;
    }
}

void V2XSPAT::parse_spat(SPAT_t *spat)
{
    ROS_INFO(" parse spat");
    cout << "count " <<spat -> intersections.list.count << endl;
    for (int i = 0; i < spat->intersections.list.count; i++)
    {
        ROS_INFO("intersection %d :: ",i );
        cout << spat->intersections.list.array << endl;
        IntersectionState *ptr = spat->intersections.list.array[i];
        v2x_msgs::SPAT msg;

        msg.name = "KIAPI SPAT";
        msg.id = ptr->id.id;
        cout << "  id   ::  " << msg.id << endl;
        for (int k = 0; k <ptr->states.list.count; k++)
        {              
            v2x_msgs::SPATdata msg_state;  
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


int main (int argc, char** argv)
{
    ros::init(argc, argv, "spat_pubs");
    ros::NodeHandle nh, nhlocal;
    V2XSPAT V2XSPAT(nh, nhlocal);

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
