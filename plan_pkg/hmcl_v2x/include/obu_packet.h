#ifndef __OBU_MSG_H__
#define __OBU_MSG_H__

#include <unistd.h>
#include <stdint.h>  

#define DEVICE_ID_SIZE 3 
#define MSG_ENDPOINT 0x0D0A

enum MessageType{
    TX_WAVE_UPER = 0x4311,
    TX_WAVE_UPER_RESULT = 0x3411,
    RX_WAVE_UPER = 0x3412,
    MISSION_LIST = 0x341A,
    MISSION_STATUS = 0x341B,
    AUTONOMOUS_REQUEST = 0x431C,
    AUTONOMOUS_REQUEST_ACK = 0x341C
};
enum ServerStateCode{
    NOT_CONNECTED = 0x00,
    CONNECTED = 0x01
};
enum MissionStatusCode{
    UNAVAILABLE = 0x00,
    OFFLINE_TEST = 0x01,
    ONLINE_TEST = 0x02,
    MISSION_READY = 0x03,
    MISSION_START = 0x04,
    MISSION_PAUSE = 0x05,
    MISSION_END = 0x06
};
enum ProgressingMissionID{
    NOT_MISSION = 0x00
};
enum ProgressingMissionState{
    REQUEST_MISSION = 0x00,
    MOVE_START_POSITION = 0x01,
    MOVE_END_POSITION = 0x02
};

enum RequestCode{
    NOT_REQ = 0x00,
    MISSION_REQ = 0x01,
    START_POINT_REQ = 0x02,
    END_POINT_REQ = 0x03
};

enum ResponseCode{
    SEND_SERVER = 0x00,
    MISSION_CONFIRM = 0x01,
    START_POINT_CONFIRM = 0x02,
    END_POINT_CONFIRM = 0x03
};

#pragma pack(1)
struct ObuTcpHeader{
   
    uint16_t message_type;
    uint8_t sequence;
    uint16_t payload_length;
    uint8_t device_type;
    uint8_t device_id[DEVICE_ID_SIZE];

};

#pragma pack(1)
struct MissionData{
  
    uint8_t mission_id;
    uint8_t status;
    uint8_t included_mission;
    uint16_t score;
    uint16_t distance;
    uint8_t irregular_id;
    double start_lat;
    double start_Lon;
    double end_lat;
    double end_lon;
    
};

#pragma pack(1)
struct IrregularData{
    
    uint8_t irregular_id;

    double lat_1;
    double lon_1;
    double lat_2;
    double lon_2;
    double lat_3;
    double lon_3;
    double lat_4;
    double lon_4;

};

#pragma pack(1)
struct MissionList{
    
    ObuTcpHeader header;
    uint8_t total_mission_count;
    uint8_t available_count;
    uint8_t irregular_count;

    MissionData *mission_list;
    IrregularData *irregular_list;

};

#pragma pack(1)
struct MissionStatus{
    
    ObuTcpHeader header;
    uint8_t v2x_server_connected;
    uint8_t mission_status;
    uint8_t progressed_mission_id;
    uint8_t progressed_mission_status;
    
};

#pragma pack(1)
struct AutonomousRequest{
    
    ObuTcpHeader header;
    uint8_t mission_id;
    uint8_t request;
    uint8_t response;
    char description[10];
    char temporary[20];
    uint16_t end_point;

};

#pragma pack(1)
struct AutonomousRequest_ACK{
    
    ObuTcpHeader header;
    uint8_t mission_id;
    uint8_t request;
    uint8_t response;
    char description[10];
    char temporary[20];
    uint16_t end_point;

};


#endif