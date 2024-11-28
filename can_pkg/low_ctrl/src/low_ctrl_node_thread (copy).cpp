#include <ros/ros.h>
#include <can_msgs/Frame.h>
#include <std_msgs/Float64.h>
#include "std_msgs/Float64MultiArray.h"
#include <std_msgs/Int8.h>
#include <hmcl_msgs/VehicleSteering.h>
#include <hmcl_msgs/VehicleWheelSpeed.h>
#include <hmcl_msgs/VehicleStatus.h>
#include <fstream>
#include <thread>

/* Check the Eautobahn Can-table sheets and EAIT_CAN(AVANTE_CN7).dbc file for detailed information! */

class LowCtrlNode {
private:
    ros::NodeHandle nh_;

    ros::Subscriber yebi_sub_;
    ros::Subscriber accel_sub_;
    ros::Subscriber steer_sub_;
    ros::Subscriber light_sub_;

    ros::Publisher yebi_pub_;
    ros::Publisher vs_feed_pub_;
    ros::Publisher pg_cmd_;
    ros::Publisher lla_cmd_;

    can_msgs::Frame can_setup_1;
    can_msgs::Frame can_setup_2;

    hmcl_msgs::VehicleStatus vs_feed;

    std_msgs::Int8 signal_feed;
    std_msgs::Float64MultiArray lla_feed;

    std::ofstream csv_file;

    bool EPS_Status = false;
    bool ACC_Status = false;

    float desir_accel = 0.0;
    float desir_steer = 0.0;
    float yaw_rate = 0.0;
    float EPS = 0.0;
    float wheel_base = 2.72;
    float light_cmd = 0.0;

    int pg_signal = 0;

    float lat_data = 0.0;
    float long_data = 0.0;

public:
    LowCtrlNode() {
        // Subscriber
        yebi_sub_ = nh_.subscribe("received_messages", 10, &LowCtrlNode::yebiCallback, this);
        accel_sub_ = nh_.subscribe("control_effort", 10, &LowCtrlNode::AccelCmdCallback, this);
        steer_sub_ = nh_.subscribe("steering_cmd_topic", 10, &LowCtrlNode::SteerCmdCallback, this);
        light_sub_ = nh_.subscribe("light_cmd", 10, &LowCtrlNode::LightCmdCallback, this);

        // Publisher
        yebi_pub_ = nh_.advertise<can_msgs::Frame>("sent_messages", 10);
        vs_feed_pub_ = nh_.advertise<hmcl_msgs::VehicleStatus>("CAN_VehicleStatus", 10);
        pg_cmd_ = nh_.advertise<std_msgs::Int8>("pg_signal", 10);
        lla_cmd_ = nh_.advertise<std_msgs::Float64MultiArray>("lla_signal", 10);

        initCanSetup();
        // csv_file.open("EPS_cali.csv");
        // if (!csv_file.is_open()){
        //     ROS_ERROR("Failed to open CSV file");
        //     return;
        // }
        // csv_file << "Steering ang, EPS\n";
    }

    void yebiCallback(const can_msgs::Frame::ConstPtr& feed_msg) {
        std::thread([this, feed_msg]() {
            if ((feed_msg->id == 1808) && (feed_msg->data[0] & 0b00000101) && (feed_msg->data[1] & 0b00000010)) {
                EPS_Status = true;
            }
            else {
                ROS_WARN_ONCE("EPS_Status not ready!");
            }

            if ((feed_msg->id == 1809) && (feed_msg->data[0] & 0b00000101) && (feed_msg->data[1] & 0b00000010)) {
                ACC_Status = true;
            }
            else {
                ROS_WARN_ONCE("ACC_Status not ready!");
            }

            if (EPS_Status == true && ACC_Status == true) {
                ROS_INFO_ONCE("All ready!");
            }

            if (feed_msg-> id == 292) {
                pg_signal = static_cast<int>(feed_msg->data[0] & 0b11111111);

                switch (pg_signal) {
                case 8: // SIG_SLOW_OFF
                    signal_feed.data = 4;
                    pg_cmd_.publish(signal_feed);
                    break;
                
                case 16: // SIG_SLOW_ON
                    signal_feed.data = 3;
                    pg_cmd_.publish(signal_feed);
                    break;
                
                case 32: // SIG_PIT_STOP
                    signal_feed.data = 2;
                    pg_cmd_.publish(signal_feed);
                    break;
                
                case 64: // SIG_STOP
                    signal_feed.data = 5;
                    pg_cmd_.publish(signal_feed);
                    break;
                
                case 128: // SIG_GO
                    signal_feed.data = 1;
                    pg_cmd_.publish(signal_feed);
                    break;
                
                default: // Default SIG_STOP
                    signal_feed.data = 0;
                    pg_cmd_.publish(signal_feed);
                    break;
                }
            }

            if (feed_msg-> id == 293) {
                lat_data = (feed_msg->data[3] << 24) | (feed_msg->data[2] << 16) | (feed_msg->data[1] << 8) | feed_msg->data[0];
                float pitzone_lat = (*((float*)&lat_data)) * 0.0000001;
                long_data = (feed_msg->data[7] << 24) | (feed_msg->data[6] << 16) | (feed_msg->data[5] << 8) | feed_msg->data[4];
                float pitzone_long = *((float*)&long_data) * 0.0000001;
                lla_feed.data = {pitzone_lat, pitzone_long};
                lla_cmd_.publish(lla_feed);
            }
            
            if (feed_msg-> id == 1808) {
                float ep = (feed_msg->data[3] << 8) | feed_msg->data[2];
                EPS = *((float*)&ep);
                if (EPS > 65535.0 / 2) {
                    EPS = (EPS - 65535.0) * 0.1;
                }
                else if (65535.0 / 2 >= EPS && EPS > 0.0) {
                    EPS = EPS * 0.1;
                }
            }
            else if (feed_msg-> id == 1810) {
                float fr = (feed_msg->data[1] << 8) | feed_msg->data[0];
                float fr_value = *((float*)&fr);
                vs_feed.wheelspeed.fr = fr_value * 0.03125;

                float fl = (feed_msg->data[3] << 8) | feed_msg->data[2];
                float fl_value = *((float*)&fl);
                vs_feed.wheelspeed.fl = fl_value * 0.03125;

                float rr = (feed_msg->data[5] << 8) | feed_msg->data[4];
                float rr_value = *((float*)&rr);
                vs_feed.wheelspeed.rr = rr_value * 0.03125;

                float rl = (feed_msg->data[7] << 8) | feed_msg->data[6];
                float rl_value = *((float*)&rl);
                vs_feed.wheelspeed.rl = rl_value * 0.03125;

                vs_feed.wheelspeed.wheel_speed = ((vs_feed.wheelspeed.fr + vs_feed.wheelspeed.fl + vs_feed.wheelspeed.rr + vs_feed.wheelspeed.rl)/4)/3.6;

                // vs_feed_pub_.publish(vs_feed);
            }
            else if (feed_msg-> id == 1811) { 
                float yr = (feed_msg->data[5] << 8) | feed_msg->data[4];
                yaw_rate = *((float*)&yr);
                yaw_rate = (yaw_rate - 4095) * 0.01;
                vs_feed.steering_info.steering_angle = (EPS/14)*3.141592/180;
            }
            // ROS_INFO("EPS : %f, Steering ang : %f", EPS, yaw_rate*2.72/ws_feed.wheel_speed);
            // csv_file << yaw_rate*2.72/ws_feed.wheel_speed << "," << EPS << "\n";
            vs_feed_pub_.publish(vs_feed);
        }).detach();
    }

    void AccelCmdCallback(const std_msgs::Float64::ConstPtr& accel_msg) {
        std::thread([this, accel_msg]() {
            desir_accel = accel_msg->data;
            ROS_INFO("Desir_Accel: %f", desir_accel);
        }).detach();
    }

    void SteerCmdCallback(const hmcl_msgs::VehicleSteering::ConstPtr& steer_msg) {
        std::thread([this, steer_msg]() {
            desir_steer = steer_msg->steering_angle;
            // ROS_INFO("Desir_Steer: %f");
        }).detach();
    }

    void LightCmdCallback(const std_msgs::Float64::ConstPtr& light_msg) {
        std::thread([this, light_msg]() {
            light_cmd = light_msg->data;
            // ROS_INFO("light_cmd: %f", light_cmd);
        }).detach();
    }

    void initCanSetup() {
        can_setup_1.id = 342; // id 0x156 setup
        can_setup_1.is_rtr = false;
        can_setup_1.is_extended = false;
        can_setup_1.is_error = false;
        can_setup_1.dlc = 8;
        can_setup_1.data[0] = 0b00000001;
        can_setup_1.data[1] = 0b10010110;
        can_setup_1.data[2] = 0b00000001;
        // can_setup_1.data[3] = 0b00000000; // Not used
        // can_setup_1.data[4] = 0b00000000; // Not used
        can_setup_1.data[5] = 0b00000000;
        can_setup_1.data[6] = 0b00000000;
        alive_cnt();

        updateCanSetup2();
    }

     void updateCanSetup2() {
        if (light_cmd == -1.0) {
            can_setup_1.data[5] = 0b00000010;
        }
        else if (light_cmd == 0.0) {
            can_setup_1.data[5] = 0b00000000;
        }
        else if (light_cmd == 1.0) {
            can_setup_1.data[5] = 0b00000100;
        }

        can_setup_2.id = 343; // id 0x157 setup
        can_setup_2.is_rtr = false;
        can_setup_2.is_extended = false;
        can_setup_2.is_error = false;
        can_setup_2.dlc = 8;
        int eps_cmd = -(65536 - (desir_steer * 10.0));
        can_setup_2.data[0] = eps_cmd & 0xFF;
        can_setup_2.data[1] = (eps_cmd >> 8) & 0xFF;
        // can_setup_2.data[2] = 0b00000000; // Not used
        int acc_cmd = (desir_accel + 10.23) * 100.0;
        can_setup_2.data[3] = acc_cmd & 0xFF;
        can_setup_2.data[4] = (acc_cmd >> 8) & 0xFF;
        // can_setup_2.data[5] = 0b00000000; // Not used
        // can_setup_2.data[6] = 0b00000000; // Not used
        // can_setup_2.data[7] = 0b00000000; // Not used
    }

    void alive_cnt() {
        if (can_setup_1.data[7] < 255)
            can_setup_1.data[7]++;
        else
            can_setup_1.data[7] = 0;
    }

    void publishCanMessage() {
        yebi_pub_.publish(can_setup_1);
        yebi_pub_.publish(can_setup_2);
        alive_cnt();
        updateCanSetup2();
    }
};

int main(int argc, char** argv) {
    ros::init(argc, argv, "low_ctrl_node");
    
    LowCtrlNode low_ctrl_node;

    ros::AsyncSpinner spinner(1);
    spinner.start();

    ros::Rate loop_rate(50);

    while (ros::ok()) {
        low_ctrl_node.publishCanMessage();
        loop_rate.sleep();
    }

    return 0;
}
