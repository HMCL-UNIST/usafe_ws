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

// #include "j2735.h"

#include "v2x_msgs/SPAT.h"
#include "v2x_msgs/SPATdata.h"
#include "v2x_msgs/PVD.h"
#include "j2735/MessageFrame.h"

#define DEBUG_OPTION
 
#define OBU_RECEIVE_BUFFER_SIZE 1500
#define MAX_UPER_SIZE 1400

#define PVD_INTERVAL 200 //msec
#define BSM_INTERVAL 100 //msec

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

/**
 * @brief  PVD 메시지 생성 
 * 
 * @param dst  MessageFrame Pointer
 * @return int 
 */
int fill_j2735_pvd(MessageFrame_t *dst, float cur_lat, float cur_lon, float cur_alt, float cur_dir, float cur_vel, float cur_gear,
                                        float prev_lat, float prev_lon, float prev_alt, float prev_dir, float prev_vel, float prev_gear,
                                        struct tm *cur_pTimeInfo, struct tm *prev_pTimeInfo);

/**
 * @brief  BSM 메시지 생성 
 * 
 * @param dst   MessageFrame Pointer
 * @return int  
 */
int fill_j2735_bsm(MessageFrame_t *dst);

/**
 * int encode_j2735_uper(char *dst,unsigned short dstLen,MessageFrame_t *src);
 * @brief MessageFrame UPER 인코딩 
 * 
 * @param dst     UPER 인코딩된 Binary 데이터 저장 버퍼 Pointer
 * @param dstLen  저장 버퍼 크기 
 * @param src     MessageFrame Pointer
 * @return int    인코딩된 데이터 크기 
 */

/**
 * int decode_j2735_uper(MessageFrame_t *dst, char *src, int size, IntersectionGeometry *map_ptr, IntersectionState *spat_ptr);
 * @brief      UPER로 인코딩된 데이터 MessageFrame으로 디코딩
 * 
 * @param dst  Dst MessageFrame Pointer
 * @param src  디코딩할 UPER 데이터 Pointer
 * @param size  UPER 데이터 길이 
 * @return int  디코딩 성공 유무
 */


class V2XInfo
{
private:
    ros::NodeHandle nh_;
    ros::Publisher pub_spat;
    ros::Subscriber sub_pvd, sub_dir;

    // OBU와 연결할 차량시스템의 기본 정보
    unsigned char packetSeq = 0; // TCP 전송 Header 내 Sequence Number value
    unsigned char clientDeviceId[3] = {0x01,0x02,0x03}; // TCP 전송 Header 내 Device ID
    unsigned char temporaryId[4] = {0x00,0x01,0x02,0x03}; // BSM, PVD 전송 시 메시지 내 Temporary ID


    time_t rawTime= time(NULL);
    struct tm* cur_pTimeInfo= localtime(&rawTime);
    struct tm* prev_pTimeInfo= localtime(&rawTime);

    float cur_lat=0;
    float cur_lon=0;
    float cur_alt=0;
    float cur_dir=0;
    float cur_vel=0;
    float cur_gear=0; 
    float prev_lat=0;
    float prev_lon=0;
    float prev_alt=0;
    float prev_dir=0;
    float prev_vel=0;
    float prev_gear=0;

    int sockFd= -1;
    int storedSize = 0;
    int uperSize;

    char rxBuffer[OBU_RECEIVE_BUFFER_SIZE], rxUperBuffer[MAX_UPER_SIZE];
    unsigned long long txPvd, txBsm;

public:
    V2XInfo(ros::NodeHandle& nh);
    ~V2XInfo();

    unsigned long long get_clock_time();
    int connect_obu_uper_tcp(char*ip, unsigned short port);
    int receive_from_obu(int sockFd, char *buffer, unsigned short bufferSize, int storedSize,
                            char *uperBuffer, unsigned short uperBufferSize, int *uperRes);
    int request_tx_wave_obu(int sockFd, char *uper, unsigned short uperLength);
    int tx_v2i_pvd(int sockFd, unsigned long long *time);
    int tx_v2v_bsm(int sockFd, unsigned long long *time);

    void parse_wave_msg();

    void dir_callback(const std_msgs::Float64::ConstPtr& msg);

    int encode_j2735_uper(char *dst,unsigned short dstLen,MessageFrame_t *src);
    int decode_j2735_uper(MessageFrame_t *dst, char *src, int size);
    void parse_decoded_j2735(MessageFrame_t *msg);
    void parse_map(MapData_t *map);
    void parse_spat(SPAT_t *spat);
    void whilecallback();

    void car_info_callback(const v2x_msgs::PVDConstPtr& msg);

};
