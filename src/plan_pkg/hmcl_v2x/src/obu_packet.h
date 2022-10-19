#ifndef __OBU_MSG_H__
#define __OBU_MSG_H__

#include <unistd.h>
#include <stdint.h>  

#define DEVICE_ID_SIZE 3 
#define MSG_ENDPOINT 0x0D0A


enum MessageType{

    MISSION_LIST_STAGE1 = 0x341A,
    MISSION_LIST_STAGE2 = 0x341B,
    REQUEST = 0x431C,
    REQUEST_ACK = 0x341C,
    ITEM_ACK = 0x341D

};
enum RequestType{

    REQ_SELECT_MISSION = 0x01,
    REQ_START_POSITION = 0x02,
    REQ_END_POSITION= 0x03,
    REQ_ITEM= 0x04,

};

enum ResponseType{
    
    RES_SUCCESS = 0x00

};


enum ItemType{

    ITEM_LAP_TIME_SUB    = 0x01,
    ITEM_LAP_TIME_ADD   = 0x02,
    ITEM_BOOST    = 0x03,
    
};

#pragma pack(1)
struct MsgHeader{

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
    uint8_t event_count;
    uint16_t distance;
    uint8_t route_id;
    int32_t start_lat;
    int32_t start_lon;
    int32_t end_lat;
    int32_t end_lon;
    
};

#pragma pack(1)
struct MissionRouteData{
    
    uint8_t mission_route_id;
    uint8_t route_node_total_count;
    uint8_t route_node_index;
    uint8_t route_node_type;
    int32_t route_node_pos_lat;
    int32_t route_node_pos_lon;

};

#pragma pack(1)
struct MissionListStage1{
    
    MsgHeader header;
    uint8_t mission_status;
    uint8_t mission_count;
    uint16_t mission_route_count;
    
    MissionData *mission_list;
    MissionRouteData *mission_route_list;
    
};

#pragma pack(1)
struct ItemData{
    
    uint8_t item_id;
    uint8_t item_type;
    uint8_t item_status;
    int32_t score;
    uint8_t speed;
    uint8_t duration;
    int32_t pos_lat;
    int32_t pos_long;
    uint8_t extend;

};

#pragma pack(1)
struct MissionListStage2{
    
    MsgHeader header;
    uint8_t mission_status;
    uint8_t item_count;
    
    ItemData *item_list;
    
};

#pragma pack(1)
struct Request{
    
    MsgHeader header;
    uint8_t mission_id;
    uint8_t request;
    uint8_t response;
    char description[10];
    char temporary[20];
    uint16_t end_point;

};

#pragma pack(1)
struct Request_Ack{
    
    MsgHeader header;
    uint8_t mission_id;
    uint8_t request;
    uint8_t response;
    char description[10];
    char temporary[20];
    uint16_t end_point;

};

#pragma pack(1)
struct Item_Ack{
    
    MsgHeader header;
    uint8_t mission_id;
    uint8_t request;
    uint8_t response;
    char description[10];
    char temporary[20];
    uint16_t end_point;

};
#endif