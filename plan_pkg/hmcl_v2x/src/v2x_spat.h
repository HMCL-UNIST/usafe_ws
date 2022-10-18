#include "ros/ros.h"
#include <ros/time.h>
#include <time.h>
#include "std_msgs/String.h"
#include "std_msgs/Int32.h"
#include <thread> 
#include <boost/thread/thread.hpp>
#include <time.h>
#include <iostream>
#include <string>
#include <sstream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <fcntl.h>
#include <std_msgs/Float64.h>

#include "v2x_msgs/SPAT.h"
#include "v2x_msgs/SPATdata.h"
#include "v2x_msgs/PVD.h"
#include "j2735/MessageFrame.h"

#include <ros/spinner.h>
#include <ros/callback_queue.h>


#define DEBUG_OPTION
 
#define OBU_RECEIVE_BUFFER_SIZE 1500
#define MAX_UPER_SIZE 1400


using namespace std;


enum J2735_DsrcID
{
    DSRC_ID_MAP = 18,
    DSRC_ID_SPAT = 19,
    DSRC_ID_BSM = 20 
};

struct CestObuUperPacketHeader
{
    unsigned short messageType; // 메시지의 타입
    unsigned char seq;          // 메시지의 시퀀스
    unsigned short payloadLen;  // 페이로드 길이
    unsigned char deviceType;   // 장치 종류
    unsigned char deviceId[3];     // 장치 ID (MAC 하위 3바이트)
}__attribute__((packed));

struct TxWaveUperResultPayload
{
    unsigned char txWaveUperSeq;
    unsigned char resultCode;
    unsigned char size;
}__attribute__((packed)); 


class V2XSPAT
{
private:
    ros::NodeHandle nh_, nh_local_;
    ros::Publisher pub_spat;
    ros::Subscriber sub_pvd;

    // OBU와 연결할 차량시스템의 기본 정보
    unsigned char packetSeq = 0; // TCP 전송 Header 내 Sequence Number value
    unsigned char clientDeviceId[3] = {0x01,0x02,0x03}; // TCP 전송 Header 내 Device ID
    unsigned char temporaryId[4] = {0x00,0x01,0x02,0x03}; // BSM, PVD 전송 시 메시지 내 Temporary ID


    time_t rawTime= time(NULL);
    tm* cur_pTimeInfo= localtime(&rawTime);
    tm* prev_pTimeInfo= localtime(&rawTime);


    int sockFd= -1;
    int storedSize = 0;
    int uperSize;

    char rxBuffer[OBU_RECEIVE_BUFFER_SIZE], rxUperBuffer[MAX_UPER_SIZE];

public:
    V2XSPAT(ros::NodeHandle& nh, ros::NodeHandle& nh_local_);
    ~V2XSPAT();

    unsigned long long get_clock_time();
    int connect_obu_uper_tcp(char*ip, unsigned short port);
    int receive_from_obu(int sockFd, char *buffer, unsigned short bufferSize, int storedSize,
                            char *uperBuffer, unsigned short uperBufferSize, int *uperRes);

    int decode_j2735_uper(MessageFrame_t *dst, char *src, int size);
    void parse_decoded_j2735(MessageFrame_t *msg);
    void parse_spat(SPAT_t *spat);
    void whilecallback();


};
