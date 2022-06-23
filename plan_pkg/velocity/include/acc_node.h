#include <sstream>
#include <string>
#include <list>
#include <iostream>
#include <fstream>
#include <queue>
#include <boost/filesystem.hpp>
#include <boost/thread/thread.hpp>

#include <ros/ros.h>
#include <ros/time.h>
#include <ros/package.h>

#include <eigen3/Eigen/Geometry>

#include <std_msgs/Float64MultiArray.h>
#include <std_msgs/Float64.h>
#include <std_msgs/Float32.h>
#include <nav_msgs/Odometry.h>
#include <geometry_msgs/Point.h>
#include <geometry_msgs/PoseStamped.h>
#include <visualization_msgs/Marker.h>
#include <visualization_msgs/MarkerArray.h>
#include <autoware_msgs/DetectedObject.h>
#include <autoware_msgs/DetectedObjectArray.h>
#include <hmcl_msgs/Lane.h>
#include <hmcl_msgs/Waypoint.h>
#include <hmcl_msgs/VehicleWheelSpeed.h>

#include <dynamic_reconfigure/server.h>
#include <velocity/testConfig.h>

class ACC 
{

    private:
    ros::NodeHandle nh_;
    ros::Publisher target_vel_pub, vel_debug;
    ros::Subscriber pose_sub, acc_sub, target_sub;


    float current_acc, current_vel, current_x, current_y;
    float object_x, object_y, object_vel;

    bool direct_control;
    int delay_step;
    double delay_in_sec, lag_tau, dt;
    double Q_dis, Q_vel, r_weight;
    double acc_cmd, d_safe, d_time;

    std::vector<double> acc_buffer;

    Eigen::VectorXd Xk;

    Eigen::MatrixXd mcQ, mcR;  
    Eigen::MatrixXd Abaroc, Bbaroc;
    Eigen::MatrixXd Abarc, Bbarc;
    Eigen::MatrixXd Ad, Bd;

    Eigen::MatrixXd mcAd, mcBd; 
    Eigen::MatrixXd mcP;

    dynamic_reconfigure::Server<velocity::testConfig> srv;
    dynamic_reconfigure::Server<velocity::testConfig>::CallbackType f;

    geometry_msgs::PoseStamped debug_msg;

    public:
    ACC();

    void computeMatrices();
    double computeGain();
    void dyn_callback(velocity::testConfig& config, uint32_t level);
    bool solveRiccatiIterationD(const Eigen::MatrixXd &Ad,
            const Eigen::MatrixXd &Bd, const Eigen::MatrixXd &Q,
            const Eigen::MatrixXd &R, Eigen::MatrixXd &P,
            const double &tolerance = 1.E-5,
            const uint iter_max = 100000);

    void poseCallback(const nav_msgs::Odometry& state_msg);
    void accCallback(const geometry_msgs::Point& msg);
    void objectCallback(const autoware_msgs::DetectedObjectArray& msg);

    void CalcVel();

};