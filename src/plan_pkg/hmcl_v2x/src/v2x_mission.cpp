#include "v2x_mission.h"

V2XMission::V2XMission(ros::NodeHandle& nh,ros::NodeHandle& nh_local): 
    nh_(nh), nh_local_(nh_local)
{
    sub_reply = nh_local_.subscribe("/mission_state", 2, &V2XMission::reply_callback,this);

    pub_mission1 = nh_.advertise<v2x_msgs::Mission1>("Mission1", 10);
    pub_mission2 = nh_.advertise<v2x_msgs::Mission2>("Mission2", 10);
    pub_item = nh_.advertise<v2x_msgs::Item>("Item", 10);
    pub_request = nh_.advertise<v2x_msgs::Request>("Request", 10);
    timer_ = nh_.createTimer(ros::Duration(0.1), &V2XMission::connect_handler,this);    
    
    ROS_INFO("V2X Mission Publisher Initialization");
}
    
V2XMission::~V2XMission()
{}

void V2XMission::connect_handler(const ros::TimerEvent& time){
  
    if(sock_connect_state == -1)
    {
        cout << " connect try" <<endl;
        Disconnect_socket();
        sock_connect_state = Connect_socket();
        buf.clear();
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        return;
    }

    unsigned char recvbuf[MAX_READ_LEN] = {0,};
    cout <<"sock_coonect_state :: "<<sock_connect_state<<endl;
    // cout << "clnt_sock :: " << clnt_sock<<endl;
    // cout << "recvbuf :: " << clnt_sock<<endl;
    int len = recv(clnt_sock, recvbuf, sizeof(recvbuf), 0); //blocking function!
    // cout <<"len "<<len<<endl;
    if(len <= 0)
    {
        sock_connect_state = Disconnect_socket();
        return;
    }

    if(len <= MAX_READ_LEN)
    {
        if(buf.size() > MAX_BUFFER_LEN)
        {
            buf.clear();
        }
        buf.append((char*)recvbuf, len);
    }

    if(buf.size() < sizeof(MsgHeader))
    {
        return;
    }
    unsigned char* temp_buf = (unsigned char*)buf.c_str();
    MsgHeader *header = (MsgHeader*)temp_buf;

    if(buf.size() < sizeof(MsgHeader) + header->payload_length )
    {
        printf("pay size error! buffering... %d / %d\n", buf.size(),  sizeof(MsgHeader) + header->payload_length);
        return;
    }

    switch (header->message_type)
    {
    case MessageType::MISSION_LIST_STAGE1 :
        {              
            RecvMissionStage1(temp_buf);
        }
        break;
    case MessageType::MISSION_LIST_STAGE2 :
        {
            RecvMissionStage2(temp_buf);
        }
        break;
    case MessageType::REQUEST_ACK :
        {
            RecvRequestAck(temp_buf);
        }
        break;
    case MessageType::ITEM_ACK :
        {
            RecvItemAck(temp_buf);
        }
        break;
    default:
        {
            printf("Recv unkown message\n");
            buf.clear();
        }
        break;
    }
    buf.erase(0, sizeof(MsgHeader) + header->payload_length);    
}

int V2XMission::Connect_socket()
{
    if(clnt_sock != -1)
    {
        printf("aleady create sock!!\n");
        return -1;
    }
    clnt_sock = socket(PF_INET,SOCK_STREAM,0);
    if(clnt_sock == -1)
    {
        printf("sock create error\n");
        return -1;
    }

    int opt_val = 1;
    setsockopt(clnt_sock, IPPROTO_TCP, TCP_NODELAY, (void*)&opt_val, sizeof(opt_val));
    setsockopt(clnt_sock, SOL_SOCKET, SO_REUSEADDR, (void*)&opt_val, sizeof(opt_val));
    
    sockaddr_in serv_addr;
    memset(&serv_addr,0,sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr. s_addr= inet_addr(ip.c_str());
    serv_addr.sin_port = htons(port);
   
    int res = -1;
    res = connect(clnt_sock,(sockaddr*)&serv_addr,sizeof(serv_addr));
    if(res == -1)
    {
        printf("sock connect error\n");
    }
    else
    {
        printf("sock connect success\n");
    }
    return res;
}

int V2XMission::Disconnect_socket()
{
    if(clnt_sock != -1)
    {
        shutdown(clnt_sock, SHUT_RDWR);
        close(clnt_sock);
        clnt_sock=-1;
        printf("sock disconnect\n");
    }    
    return -1;
}


int V2XMission::RecvMissionStage1(unsigned char* buf)
{
    printf("\n[RecvMissionStage1] start\n");
    MissionListStage1 msg = {0,};
    
    ParseMissionStage1(&msg, buf);
    PrintMissionStage1(&msg);
    if (select ==true)
    {
        PubMissionStage1(&msg);
    }
    // writeMissionpos1(&msg);
    
    //select mission
    // 0: wait , 1 : start, 2 : stop, 4 : test mode)
    if(msg.mission_count > 0 && msg.mission_status != 2 )
    {
        for(int i=0; i<msg.mission_count; i++)
        {
            if(msg.mission_list[i].status == 0 && msg.mission_list[mission_ind].event_count < msg.mission_list[i].event_count)
            {  
                mission_ind = i;
            }
        }
        printf("select mission %d \n", msg.mission_list[mission_ind].mission_id);

        // if (msg.mission_list[mission_ind].status == 0)
        // {
        printf("%d번 미션 선택 요구 \n", msg.mission_list[mission_ind].mission_id);
        SendRequest(msg.mission_list[mission_ind].mission_id, RequestType::REQ_SELECT_MISSION);
        select = true;
        // }
    }

    if(msg.mission_list != nullptr)
    {
        delete msg.mission_list;
    }
    if(msg.mission_route_list != nullptr)
    {
        delete msg.mission_route_list;
    }

    return 0;
}

int V2XMission::RecvMissionStage2(unsigned char* buf)
{
    printf("\n[RecvMissionStage2] start\n");

    MissionListStage2 msg = {0,};

    ParseMissionStage2(&msg, buf);
    PrintMissionStage2(&msg);
    PubMissionStage2(&msg);

    if(msg.item_list != nullptr)
    {
        delete msg.item_list;
    }
    return 0;
}

int V2XMission::RecvRequestAck(unsigned char* buf)
{
    printf("\n[RecvRequestAck] start\n");
    Request_Ack msg = {0,};

    ParseRequestAck(&msg, buf);
    PrintRequestAck(&msg);

    v2x_msgs::Request req_msg;
    req_msg.mission = false;
    req_msg.start = false;
    req_msg.goal = false;
    printf("%d 미션 \n", msg.mission_id);

    if(msg.request == RequestType::REQ_SELECT_MISSION && msg.response == ResponseType::RES_SUCCESS )
    {
        printf("%d번 미션 선택 완료\n", msg.mission_id);
        req_msg.mission = true;
        pub_request.publish(req_msg);
    }

    if(msg.request == RequestType::REQ_START_POSITION && msg.response == ResponseType::RES_SUCCESS )
    {
        printf("%d번 출발지 도착 완료\n", msg.mission_id);
        req_msg.mission = true;
        req_msg.start = true;
        pub_request.publish(req_msg);
    }

    if(msg.request == RequestType::REQ_END_POSITION && msg.response == ResponseType::RES_SUCCESS )
    {
        printf("%d번 목적지 도착 완료\n", msg.mission_id);
        req_msg.mission = true;
        req_msg.start = true;
        req_msg.goal = true;
        pub_request.publish(req_msg);
    }
    return 0;
}

int V2XMission::RecvItemAck(unsigned char* buf)
{
    printf("\n[RecvItemAck] start\n");
    Item_Ack msg = {0,};
    
    ParseItemAck(&msg, buf);
    PrintItemAck(&msg);

    if(msg.request == RequestType::REQ_ITEM)
    {
        v2x_msgs::Item item;
        item.item_id = msg.mission_id;
        if(msg.response == ItemType::ITEM_LAP_TIME_SUB)
        {
            item.description = 0;
            printf("%d번 아이템 획득 : Lap time 감소\n", msg.mission_id);
        }
        if(msg.response == ItemType::ITEM_LAP_TIME_ADD)
        {
            item.description = 1;
            printf("%d번 아이템 획득 : Lap time 증가\n", msg.mission_id);
        }
        if(msg.response == ItemType::ITEM_BOOST)
        {
            item.description = 2;
            printf("%d번 아이템 획득 : 가속 주행\n", msg.mission_id);
        }
        pub_item.publish(item);
    }

    return 0;
}

void V2XMission::ParseMissionStage1(MissionListStage1 *msg, unsigned char* buf)
{
    if(msg == nullptr)
    {
        printf("[ParseMissionStage1] fail : msg == nullptr\n");
        return;
    }
    printf("[ParseMissionStage1] start\n");
    
    size_t copy_len_1 = sizeof(MissionListStage1) - sizeof(MissionListStage1::mission_list) - sizeof(MissionListStage1::mission_route_list);
    memmove(msg,buf,copy_len_1);

    size_t copy_len_2 = sizeof(MissionData) * msg->mission_count;
    msg->mission_list = new MissionData[msg->mission_count];
    memmove(msg->mission_list, &buf[copy_len_1], copy_len_2);

	size_t copy_len_3 = sizeof(MissionRouteData) * msg->mission_route_count;
    msg->mission_route_list = new MissionRouteData[msg->mission_route_count];
    memmove(msg->mission_route_list, &buf[copy_len_1 + copy_len_2], copy_len_3);

}
void V2XMission::ParseMissionStage2(MissionListStage2 *msg, unsigned char* buf)
{
    if(msg == nullptr)
    {
        printf("[ParseMissionStage2] fail : msg == nullptr\n");
        return;
    }
    printf("[ParseMissionStage2] start\n");

    size_t copy_len_1 = sizeof(MissionListStage2) - sizeof(MissionListStage2::item_list);
    memmove(msg,buf,copy_len_1);

    size_t copy_len_2 = sizeof(ItemData) * msg->item_count;
    msg->item_list = new ItemData[msg->item_count];
    memmove(msg->item_list, &buf[copy_len_1],copy_len_2); 
}

void V2XMission::ParseRequestAck(Request_Ack *msg, unsigned char* buf)
{
    if(msg == nullptr)
    {
        printf("[ParseRequestAck] fail : msg == nullptr\n");
        return;
    }
    printf("[ParseRequestAck] start\n");
    memmove(msg,buf,sizeof(Request_Ack));
}

void V2XMission::ParseItemAck(Item_Ack *msg, unsigned char* buf)
{
    if(msg == nullptr)
    {
        printf("[ParseItemAck] fail : msg == nullptr\n");
        return;
    }
    printf("[ParseItemAck] start\n");
    memmove(msg,buf,sizeof(Item_Ack));
}

void V2XMission::reply_callback(const std_msgs::Int16ConstPtr& msg)
{   
    ROS_INFO("I am here");  
    if (msg->data ==4)
    {
        printf("출발지 도착 요구 \n");
        SendRequest(mission_ind+1, RequestType::REQ_START_POSITION);       
    }
    else if(msg->data==6)
    {
        printf("목적지 도착 요구 \n");
        SendRequest(mission_ind+1, RequestType::REQ_END_POSITION);  
    }
}

void V2XMission::SendRequest(unsigned char id, unsigned char req)
{
    Request msg = {0,};

    msg.header.message_type = MessageType::REQUEST;
    msg.header.sequence = seq++;
    msg.header.payload_length = sizeof(Request) - sizeof(MsgHeader);
    msg.header.device_type = 0xCE;
    msg.header.device_id[0] = 0x24;//team id
    msg.header.device_id[1] = 0x67;//team idsock disconnect
    msg.header.device_id[2] = 0x05;//team id

    msg.mission_id = id;
    msg.request = req;

    msg.response = 0x00;
    sprintf(msg.description,"UNIST");//team name
    msg.temporary; //all 0
    msg.end_point = 0x0D0A;
    
    int len = send(clnt_sock, (char*)&msg, sizeof(msg), 0); 
    if(len <=0)
    {
        printf("[SendRequest] fail send\n");
    }
    else
    {
        printf("[SendRequest] id : %d, req : %d, byte : %d\n",id, req, len);
    }
}

void V2XMission::writeMissionpos1(MissionListStage1 *msg)
{
    ofstream finw;
    finw.precision(12);
    finw.open("/home/xavier2/v2x_ros/mission1_pos.txt");
    finw <<"[WriteMissionPosition] start\n";
    for(int i=0; i<msg->mission_route_count; i++)
    {
        finw << (long double)(msg->mission_route_list[i].route_node_pos_lat)*1e-7 << ", " <<(long double)(msg->mission_route_list[i].route_node_pos_lon)*1e-7<<"\n";
    }
    finw<< "\n";
    finw.close();
}

void V2XMission::PubMissionStage1(MissionListStage1 *msg)
{
    v2x_msgs::Mission1 mission;

    route_id = msg->mission_list[mission_ind].route_id;
    mission.mission_id = msg->mission_list[mission_ind].mission_id;
    mission.status = msg->mission_list[mission_ind].status;
    mission.event_count = msg->mission_list[mission_ind].event_count;

    mission.distance = (double)(msg->mission_list[mission_ind].distance);
    mission.start_lat = (double)(msg->mission_list[mission_ind].start_lat)*1e-7;
    mission.start_lon = (double)(msg->mission_list[mission_ind].start_lon)*1e-7;
    mission.end_lat = (double)(msg->mission_list[mission_ind].end_lat)*1e-7;
    mission.end_lon = (double)(msg->mission_list[mission_ind].end_lon)*1e-7;

    for(int i=0; i<msg->mission_route_count; i++)
    {
        if (msg->mission_route_list[i].mission_route_id == route_id)
        {
            v2x_msgs::Mission1data data;
            data.route_node_index = msg->mission_route_list[i].route_node_index;
            data.route_node_type = msg->mission_route_list[i].route_node_type;
            data.route_node_pos_lat = (double)(msg->mission_route_list[i].route_node_pos_lat)*1e-7;
            data.route_node_pos_lon = (double)(msg->mission_route_list[i].route_node_pos_lon)*1e-7;
            mission.route_count = msg->mission_route_list[i].route_node_total_count;

            mission.States.push_back(data);
        }
    }
    pub_mission1.publish(mission);
}


void V2XMission::PubMissionStage2(MissionListStage2 *msg)
{
    v2x_msgs::Mission2 mission;
    mission.mission_status = msg->mission_status;
    mission.item_count = msg->item_count;
    cout << "Mission 2 status : " <<mission.mission_status <<endl;


    for(int i=0; i<msg->item_count; i++)
    {
        v2x_msgs::Mission2data data;
        data.item_id = msg->item_list[i].item_id;
        data.item_type = msg->item_list[i].item_type;
        data.item_status = msg->item_list[i].item_status;
        data.score = msg->item_list[i].score;
        data.speed = msg->item_list[i].speed;
        data.duration = msg->item_list[i].duration;
        data.pos_lat = msg->item_list[i].pos_lat*1e-7;
        data.pos_long = msg->item_list[i].pos_long*1e-7;
        data.extend = msg->item_list[i].extend;
        mission.States.push_back(data);
    }
    pub_mission2.publish(mission);

}


void V2XMission::PrintMissionStage1(MissionListStage1 *msg)
{

    if(!DISPLAY_PACKET)
    {
        return;
    }
    if(msg == nullptr)
    {
        printf("[PrintMissionStage1] fail : msg == nullptr\n");
        return;
    }
    printf("[PrintMissionStage1] start\n");

    ofstream fin1;
    fin1.open("/home/xavier2/v2x_ros/mission1.txt",ios::app);
    fin1 <<"[PrintMissionStage1] start\n";

    //print
    
    printf("\theader.message_type : 0x%04X\n", msg->header.message_type);
    printf("\theader.payload_length : %d\n", msg->header.payload_length);
    printf("\theader.device_type : 0x%02X\n", msg->header.device_type);
    printf("\theader.device_id : 0x%02X 0x%02X 0x%02x\n", msg->header.device_id[0], msg->header.device_id[1], msg->header.device_id[2]);
    printf("\n");
    printf("\tmission_status : 0x%02X\n", msg->mission_status);
    printf("\tmission_count : %d\n", msg->mission_count);
    printf("\tmission_route_count : %d\n", msg->mission_route_count);
    
    fin1 <<"\theader.message_type : 0x" << (double)(msg->header.message_type)<<"\n";
    fin1 << "\theader.sequence : " << (int)(msg->header.sequence)<<"\n";
    fin1 << "\theader.payload_length : " << msg->header.payload_length<<"\n";
    fin1 << "\theader.device_type : 0x" << (double)(msg->header.device_type)<<"\n";
    fin1 << "\theader.device_id : 0x"<<(double)(msg->header.device_id[0]) << ", 0x" << (double)(msg->header.device_id[1]) << ", 0x" << (double)(msg->header.device_id[2]) <<"\n";
    fin1 << "\n";
    fin1 << "\tmission_status : 0x" << (double)(msg->mission_status)<<"\n";
    fin1 << "\tmission_count : "<<(int)(msg->mission_count)<<"\n";
    fin1 << "\tmission_route_count : " <<msg->mission_route_count<<"\n";
    
    for(int i=0; i<msg->mission_count; i++)
    {
        printf("\tmission_list[%d].mission_id : %d\n", i, msg->mission_list[i].mission_id);
        printf("\tmission_list[%d].status : 0x%02X\n", i, msg->mission_list[i].status);
        printf("\tmission_list[%d].event_count : %d\n", i, msg->mission_list[i].event_count);
        printf("\tmission_list[%d].distance : %d\n", i, msg->mission_list[i].distance);
        printf("\tmission_list[%d].route_id : %d\n", i, msg->mission_list[i].route_id);
        printf("\tmission_list[%d].start_lat : %d\n", i, msg->mission_list[i].start_lat);
        printf("\tmission_list[%d].start_Lon : %d\n", i, msg->mission_list[i].start_lon);
        printf("\tmission_list[%d].end_lat : %d\n", i, msg->mission_list[i].end_lat);
        printf("\tmission_list[%d].end_lon : %d\n", i, msg->mission_list[i].end_lon);

        fin1 << "\t"<< i << "th "<< "mission_list.mission_id : " << (int)(msg->mission_list[i].mission_id)<<"\n";
        fin1 << "\t"<< i << "th "<< "mission_list.status : 0x" << (double)(msg->mission_list[i].status)<<"\n";
        fin1 << "\t"<< i << "th "<< "mission_list.event_count : " << msg->mission_list[i].event_count<<"\n";
        fin1 << "\t"<< i << "th "<< "mission_list.distance : " << msg->mission_list[i].distance<<"\n";
        fin1 << "\t"<< i << "th "<< "mission_list.route_id : " << (int)(msg->mission_list[i].route_id)<<"\n";
        fin1 << "\t"<< i << "th "<< "mission_list.start_lat : " <<msg->mission_list[i].start_lat<<"\n";
        fin1 << "\t"<< i << "th "<< "mission_list.start_Lon : " <<msg->mission_list[i].start_lon<<"\n";
        fin1 << "\t"<< i << "th "<< "mission_list.end_lat : " << msg->mission_list[i].end_lat<<"\n";
        fin1 << "\t"<< i << "th "<< "mission_list.end_lon : " << msg->mission_list[i].end_lon<<"\n";
    }
    for(int i=0; i<msg->mission_route_count; i++)
    {
        printf("\tmission_route_list[%d].mission_route_id : %d\n", i, msg->mission_route_list[i].mission_route_id);
        printf("\tmission_route_list[%d].route_node_total_count : %d\n", i, msg->mission_route_list[i].route_node_total_count);
        printf("\tmission_route_list[%d].route_node_index : %d\n", i, msg->mission_route_list[i].route_node_index);
        printf("\tmission_route_list[%d].route_node_type : %d\n", i, msg->mission_route_list[i].route_node_type);
        printf("\tmission_route_list[%d].route_node_pos_lat : %d\n", i, msg->mission_route_list[i].route_node_pos_lat);
        printf("\tmission_route_list[%d].route_node_pos_lon : %d\n", i, msg->mission_route_list[i].route_node_pos_lon);

        fin1 << "\t" << i << "th "<< "mission_route_list.mission_route_id : " << (int)(msg->mission_route_list[i].mission_route_id)<<"\n";
        fin1 << "\t"<< i << "th "<< "mission_route_list.route_node_total_count : " << (int)(msg->mission_route_list[i].route_node_total_count)<<"\n";
        fin1 << "\t"<< i << "th "<< "mission_route_list.route_node_index : " << (int)(msg->mission_route_list[i].route_node_index)<<"\n";
        fin1 << "\t"<< i << "th "<< "mission_route_list.route_node_type : " << (int)(msg->mission_route_list[i].route_node_type) <<"\n";
        fin1 << "\t"<< i << "th "<< "mission_route_list.route_node_pos_lat : " << msg->mission_route_list[i].route_node_pos_lat<<"\n";
        fin1 << "\t"<< i << "th "<< "mission_route_list.route_node_pos_lon : " << msg->mission_route_list[i].route_node_pos_lon<<"\n";
    }
    fin1 << "\n";
    fin1.close();
}


void V2XMission::PrintMissionStage2(MissionListStage2 *msg)
{

    if(!DISPLAY_PACKET)
    {
        return;
    }
    if(msg == nullptr)
    {
        printf("[PrintMissionStage2] fail : msg == nullptr\n");
        return;
    }
    printf("[PrintMissionStage2] start\n");
 
    ofstream fin2;
    fin2.open("/home/xavier2/v2x_ros/mission2.txt",ios::app);
    fin2 <<"[PrintMissionStage1] start\n";

    //print

    printf("\theader.message_type : 0x%04X\n", msg->header.message_type);
    printf("\theader.sequence : %d\n", msg->header.sequence);
    printf("\theader.payload_length : %d\n", msg->header.payload_length);
    printf("\theader.device_type : 0x%02X\n", msg->header.device_type);
    printf("\theader.device_id : 0x%02X 0x%02X 0x%02x\n", msg->header.device_id[0], msg->header.device_id[1], msg->header.device_id[2]);
    printf("\n");
    printf("\tmission_status : 0x%02X\n", msg->mission_status);
    printf("\titem_count : %d\n", msg->item_count);

    fin2 <<"\theader.message_type : 0x" << (double)(msg->header.message_type)<<"\n";
    fin2 << "\theader.sequence : " << (int)(msg->header.sequence)<<"\n";
    fin2 << "\theader.payload_length : " << msg->header.payload_length<<"\n";
    fin2 << "\theader.device_type : 0x" << (double)(msg->header.device_type)<<"\n";
    fin2 << "\theader.device_id : 0x"<<(double)(msg->header.device_id[0]) << ", 0x" << (double)(msg->header.device_id[1]) << ", 0x" << (double)(msg->header.device_id[2]) <<"\n";
    fin2 << "\n";
    fin2 << "\tmission_status : 0x" << (int)(msg->mission_status)<<"\n";
    fin2 << "\tmission_count : "<<(int)(msg->item_count)<<"\n";

    for(int i=0; i<msg->item_count; i++)
    {
        printf("\titem_list[%d].item_id : %d\n", i, msg->item_list[i].item_id);
        printf("\titem_list[%d].item_type : %d\n", i, msg->item_list[i].item_type);
        printf("\titem_list[%d].item_status : %d\n", i, msg->item_list[i].item_status);
        printf("\titem_list[%d].score : %d\n", i, msg->item_list[i].score);
        printf("\titem_list[%d].speed : %d\n", i, msg->item_list[i].speed);
        printf("\titem_list[%d].duration : %d\n", i, msg->item_list[i].duration);
        printf("\titem_list[%d].pos_lat : %d\n", i, msg->item_list[i].pos_lat);
        printf("\titem_list[%d].pos_long : %d\n", i, msg->item_list[i].pos_long);
        printf("\titem_list[%d].extend : %d\n", i, msg->item_list[i].extend);

        fin2 << "\t"<< i << "th "<< "item_list.item_id : " << (int)(msg->item_list[i].item_id)<<"\n";
        fin2 << "\t"<< i << "th "<< "item_list.item_type : " << (int)(msg->item_list[i].item_type)<<"\n";
        fin2 << "\t"<< i << "th "<< "item_list.item_status : " << (int)(msg->item_list[i].item_status)<<"\n";
        fin2 << "\t"<< i << "th "<< "item_list.score : " << msg->item_list[i].score<<"\n";
        fin2 << "\t"<< i << "th "<< "item_list.speed : " << (int)(msg->item_list[i].speed)<<"\n";
        fin2 << "\t"<< i << "th "<< "item_list.duration : " <<(int)(msg->item_list[i].duration)<<"\n";
        fin2 << "\t"<< i << "th "<< "item_list.pos_lat : " <<msg->item_list[i].pos_lat<<"\n";
        fin2 << "\t"<< i << "th "<< "item_list.pos_long : " << msg->item_list[i].pos_long<<"\n";
        fin2 << "\t"<< i << "th "<< "item_list.extend : " << (int) (msg->item_list[i].extend)<<"\n";
    }
    fin2 << "\n";
    fin2.close();

}
void V2XMission::PrintRequestAck(Request_Ack *msg)
{

    if(!DISPLAY_PACKET)
    {
        return;
    }
    if(msg == nullptr)
    {
        printf("[PrintRequestAck] fail : msg == nullptr\n");
        return;
    }
    printf("[PrintRequestAck] start\n");

    ofstream finR;
    finR.open("/home/xavier2/v2x_ros/request.txt",ios::app);
    finR <<"[PrintRequestAck] start\n";

    //print

    printf("\theader.message_type : 0x%04X\n", msg->header.message_type);
    printf("\theader.sequence : %d\n", msg->header.sequence);
    printf("\theader.payload_length : %d\n", msg->header.payload_length);
    printf("\theader.device_type : 0x%02X\n", msg->header.device_type);
    printf("\theader.device_id : 0x%02X 0x%02X 0x%02x\n", msg->header.device_id[0], msg->header.device_id[1], msg->header.device_id[2]);
    printf("\n");
    printf("\tmission_id : %d\n", msg->mission_id);
    printf("\trequest : %d\n", msg->request);
    printf("\tresponse : %d\n", msg->response);
    printf("\tdescription : %s\n", msg->description);
    printf("\ttemporary : %s\n", msg->temporary);
    printf("\tend_point : 0x%04X\n", msg->end_point);

    finR <<"\theader.message_type : 0x" << (double)(msg->header.message_type)<<"\n";
    finR << "\theader.sequence : " << (int)(msg->header.sequence)<<"\n";
    finR << "\theader.payload_length : " << msg->header.payload_length<<"\n";
    finR << "\theader.device_type : 0x" << (double)(msg->header.device_type)<<"\n";
    finR << "\theader.device_id : 0x"<<(double)(msg->header.device_id[0]) << ", 0x" << (double)(msg->header.device_id[1]) << ", 0x" << (double)(msg->header.device_id[2]) <<"\n";
    finR << "\n";
    finR << "\tmission_id : " << (int)(msg->mission_id)<<"\n";
    finR << "\trequest : "<<(int)(msg->request)<<"\n";
    finR << "\tresponse : "<<(int)(msg->response)<<"\n";
    finR << "\tdescription : "<<msg->description<<"\n";
    finR << "\ttemporary : "<<msg->temporary<<"\n";
    finR << "\tend_point : "<<(double)(msg->end_point)<<"\n";
    finR << "\n";
    finR.close();


}
void V2XMission::PrintItemAck(Item_Ack *msg)
{
    if(!DISPLAY_PACKET)
    {
        return;
    }
    if(msg == nullptr)
    {
        printf("[PrintItemAck] fail : msg == nullptr\n");
        return;
    }
    printf("[PrintItemAck] start\n");
    ofstream finI;
    finI.open("/home/xavier2/v2x_ros/item.txt",ios::app);
    finI <<"[PrintItemAck] start\n";
 
    printf("\theader.message_type : 0x%04X\n", msg->header.message_type);
    printf("\theader.sequence : %d\n", msg->header.sequence);
    printf("\theader.payload_length : %d\n", msg->header.payload_length);
    printf("\theader.device_type : 0x%02X\n", msg->header.device_type);
    printf("\theader.device_id : 0x%02X 0x%02X 0x%02x\n", msg->header.device_id[0], msg->header.device_id[1], msg->header.device_id[2]);
    printf("\n");
    printf("\tmission_id : %d\n", msg->mission_id);
    printf("\trequest : %d\n", msg->request);
    printf("\tresponse : %d\n", msg->response);
    printf("\tdescription : %s\n", msg->description);
    printf("\ttemporary : %s\n", msg->temporary);
    printf("\tend_point : 0x%04X\n", msg->end_point);

    finI <<"\theader.message_type : 0x" << (double)(msg->header.message_type)<<"\n";
    finI << "\theader.sequence : " << (int)(msg->header.sequence)<<"\n";
    finI << "\theader.payload_length : " << msg->header.payload_length<<"\n";
    finI << "\theader.device_type : 0x" << (double)(msg->header.device_type)<<"\n";
    finI << "\theader.device_id : 0x"<<(double)(msg->header.device_id[0]) << ", 0x" << (double)(msg->header.device_id[1]) << ", 0x" << (double)(msg->header.device_id[2]) <<"\n";
    finI << "\n";
    finI << "\tmission_id : " << (int)(msg->mission_id)<<"\n";
    finI << "\trequest : "<<(int)(msg->request)<<"\n";
    finI << "\tresponse : "<<(int)(msg->response)<<"\n";
    finI << "\tdescription : "<<msg->description<<"\n";
    finI << "\ttemporary : "<<msg->temporary<<"\n";
    finI << "\tend_point : "<<(double)(msg->end_point)<<"\n";
    finI << "\n";
    finI.close();
}

int main (int argc, char** argv)
{
    ros::init(argc, argv, "mission_pub");
    ros::NodeHandle nh, nhlocal;
    
    V2XMission V2XMission(nh,nhlocal);
   
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
