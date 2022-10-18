#include "v2x_pvd.h"

using namespace std;


V2XPVD::V2XPVD(ros::NodeHandle& nh, ros::NodeHandle& nh_local):
    nh_(nh), nh_local_(nh_local)
{  
    sub_pos = nh_local_.subscribe("/fix", 1, &V2XPVD::pos_callback, this);
    sub_dir = nh_.subscribe("/heading_ned", 1, &V2XPVD::dir_callback, this);
    sub_veh = nh_.subscribe("/vehicle_status", 1, &V2XPVD::veh_callback,this);

    txPvd = get_clock_time();

    ROS_INFO("V2X PVD Publisher Initialization");
    boost::thread while_loop(&V2XPVD::whilecallback,this); 
}

V2XPVD::~V2XPVD()
{}

void V2XPVD::pos_callback(const sensor_msgs::NavSatFix::ConstPtr& nav_data){
    prev_alt = cur_alt;
    prev_lat = cur_lat;
    prev_lon = cur_lon;
    cur_alt = (nav_data -> altitude)*10;
    cur_lat = (nav_data -> latitude)*1e7;
    cur_lon = (nav_data -> longitude)*1e7;
}

void V2XPVD::dir_callback(const std_msgs::Float64::ConstPtr& dir_data){
    prev_dir = cur_dir;
    cur_dir = -(dir_data->data -90);    
    if (cur_dir <0){
        cur_dir +=360;
    }
    cur_dir = cur_dir/0.0125;
}

void V2XPVD::veh_callback(const hmcl_msgs::VehicleStatus::ConstPtr& veh_data){
    prev_vel = cur_vel;
    cur_vel = veh_data->wheelspeed.wheel_speed;
    cur_vel = cur_vel/0.02;
    prev_gear =cur_gear;
    cur_gear = veh_data->gear_info.gear;
}

void V2XPVD::whilecallback(){
ros::Rate loop_rate(10);
    while(ros::ok())
    {    
        // 소켓이 연결되지 않은 경우(sockFd == -1) , OBU TCP 소켓 연결 시도
        if(sockFd < 0)
        {
            sockFd = connect_obu_uper_tcp("192.168.10.10",23000); // OBU
            storedSize = 0;
            
            if(sockFd < 0){
                std::cout <<"DEBUG : connect failed, retry \n"<< std::endl;
                sleep(1);
                continue;
            } 
        }
        if (tx_v2i_pvd(sockFd,&txPvd) < 0)
        {
            // OBU와 TCP 연결이 끊어진 경우, 연결 재시도
            close(sockFd);
            sockFd = -1;
            loop_rate.sleep();
            continue;
        }
        
        loop_rate.sleep();
    }
}


unsigned long long V2XPVD::get_clock_time(){  
    struct timespec ts;
    clock_gettime(CLOCK_REALTIME, &ts);  
    uint64_t clock = ts.tv_sec * 1000 + (ts.tv_nsec / 1000000); 
    return clock;
}  

int V2XPVD::connect_obu_uper_tcp(char*ip, unsigned short port)
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

int V2XPVD::request_tx_wave_obu(int sockFd, char *uper,unsigned short uperLength)
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
            cout << "res return ::" <<res << endl;
            return res;
        }
    }
}

// vehicle to OBU
int V2XPVD::tx_v2i_pvd(int sockFd, unsigned long long *time)
{ 
    unsigned long long interval = get_clock_time() - *time;  // msec;

    if(interval < PVD_INTERVAL)
        return 0;
    
    *time += (interval - interval%PVD_INTERVAL); 
 
    MessageFrame_t msg;
    char uper[MAX_UPER_SIZE]; 
    prev_pTimeInfo = cur_pTimeInfo;
    cur_pTimeInfo = localtime(&rawTime);
    cout << "PVD :::: ::::: ::: :: ::: :: "<<endl;
    int res_=fill_j2735_pvd(&msg, cur_lat, cur_lon,  cur_alt,  cur_dir,  cur_vel,  cur_gear, prev_lat,  prev_lon,  prev_alt,  prev_dir,  prev_vel, prev_gear, cur_pTimeInfo, prev_pTimeInfo);
    cout << "PVD Debug ::::: ::: :: ::: :: "<<endl;
    int encodedBits = encode_j2735_uper(uper,MAX_UPER_SIZE,&msg);
    cout << "PVD Debug ::::: ::: :: ::: :: "<< encodedBits << endl;

    if(encodedBits < 0) // 인코딩 실패로 전송이 불가능한 상태
        return 0;
     
    int byteLen = encodedBits / 8 + ((encodedBits % 8)? 1:0);
    return request_tx_wave_obu(sockFd,uper,byteLen);
}

int V2XPVD::encode_j2735_uper(char *dst, unsigned short dstLen, MessageFrame_t *src)
{
    int res = -1;

    //error
    asn_enc_rval_t ret = uper_encode_to_buffer(&asn_DEF_MessageFrame, NULL, src, dst, dstLen);

    cout << "ret :: " <<ret.encoded <<endl;
    if (ret.encoded > 0)
        return ret.encoded; //  UPER Encoding Success
    else
    { 
        if (ret.failed_type != NULL)
            printf("encoded error value name = %s\n", ret.failed_type->name);

        return -1; // UPER Encoding failed
    }
}
int main (int argc, char** argv)
{
    ros::init(argc, argv, "pvd_pubs");
    ros::NodeHandle nh, nhlocal;
    V2XPVD V2XPVD(nh, nhlocal);

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


}
