#include <ros/ros.h>
#include <iostream>
#include <fstream>
#include <thread>
#include <arpa/inet.h>
#include <netinet/tcp.h>
#include <string.h>
#include <std_msgs/Int16.h>

#include <ros/spinner.h>
#include <ros/callback_queue.h>

#include "v2x_msgs/Mission1.h"
#include "v2x_msgs/Mission1data.h"
#include "v2x_msgs/Mission2.h"
#include "v2x_msgs/Mission2data.h"
#include "v2x_msgs/Item.h"
#include "v2x_msgs/Request.h"
#include "v2x_msgs/Reply.h"

#include "obu_packet.h"

#define DISPLAY_PACKET false
#define MAX_READ_LEN  4096
#define MAX_BUFFER_LEN  1000000

using namespace std;

class V2XMission
{
private:
    ros::NodeHandle nh_, nh_local_;
    ros::Publisher debug_pub, pub_mission1, pub_mission2, pub_item, pub_request;
    ros::Subscriber sub_reply;

    ros::Timer timer_;

    int clnt_sock = -1;
    std::string buf;

    std::string ip = "192.168.10.10";
    uint32_t port = 24000;

    int sock_connect_state = -1;
    uint8_t seq = 0;
    
    int mission_ind = 0;
    int route_id = 0;

    bool get_item = false;
    bool select = false;

public:
    V2XMission(ros::NodeHandle& nh_, ros::NodeHandle& nh_local_);
    ~V2XMission();

    void connect_handler(const ros::TimerEvent& time);

    int Connect_socket();
    int Disconnect_socket();

    void PrintMissionStage1(MissionListStage1 *msg);
    void writeMissionpos1(MissionListStage1 *msg);
    void PubMissionStage1(MissionListStage1 *msg);
    void PrintRequestAck(Request_Ack *msg);
    void reply_callback(const std_msgs::Int16ConstPtr& msg);

    void PrintMissionStage2(MissionListStage2 *msg);
    void PubMissionStage2(MissionListStage2 *msg);
    void PrintItemAck(Item_Ack *msg);

    int RecvMissionStage1(unsigned char* buf);
    int RecvMissionStage2(unsigned char* buf);
    int RecvRequestAck(unsigned char* buf);
    int RecvItemAck(unsigned char* buf);

    void SendRequest(unsigned char id, unsigned char req);

    void ParseMissionStage1(MissionListStage1 *msg, unsigned char* buf);
    void ParseMissionStage2(MissionListStage2 *msg, unsigned char* buf);
    void ParseRequestAck(Request_Ack *msg, unsigned char* buf);
    void ParseItemAck(Item_Ack *msg, unsigned char* buf);

};
