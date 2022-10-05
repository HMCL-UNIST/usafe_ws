#include <ros/ros.h>
#include <ros/time.h>
#include <tf/tf.h>
#include <algorithm>

#include <nav_msgs/Odometry.h>

#include <geometry_msgs/Pose.h>
#include <geometry_msgs/Point.h>
#include <hmcl_msgs/LaneArray.h>
#include <hmcl_msgs/Lane.h>
#include <hmcl_msgs/Waypoint.h>

#include <std_msgs/Int16.h>
#include <hmcl_msgs/VehicleStatus.h>

#include <visualization_msgs/Marker.h>
#include <visualization_msgs/MarkerArray.h>

using namespace std;

typedef enum{Init, Forward, Follow, StopAtStartPos, StartArrival, TrafficLightStop, LeftTurn, RightTurn, Crosswalk,
            Pedestrian, FrontLuggage, FrontCarStop, LaneChange, SpeedBump, StopAtGoalPos, GoalArrival} BehaviorState;

struct Sector 
{
    geometry_msgs::Pose section{};
    double length;
    double speed;
    int prepare_idx1;
    int prepare_idx2;
    int lc_idx1;
    int lc_idx2;
};

struct Point
{
    Sector start{};     // shift start point in absolute coordinate
    Sector end{};
};

class localplanner
{
private:
    ros::NodeHandle nh_;
    ros::Publisher pub_traj, pub_viz;
    ros::Subscriber sub_traj, sub_global, sub_pos, sub_vel, sub_flag;
    ros::Timer timer_;

    bool lc_flag = false;
    bool st_flag = false;
    bool vel_flag = false;
    Sector current_pos;

    double min_lc_len, lc_prepare_dur, lc_duration, min_lc_vel, lc_dec;
    double lc_prepare_dist, lc_dist, lc_prepare_vel, lc_vel;

    hmcl_msgs::Lane current_lane, change_lane;
    hmcl_msgs::LaneArray global_lane, range_lane;

    vector<int> global_index, range_index, global_change;

public:
    localplanner(ros::NodeHandle& nh_);
    ~localplanner();
    
    void connect_handler(const ros::TimerEvent& time);
    
    void poseCallback(const nav_msgs::Odometry& state_msg);
    void trajCallback(const hmcl_msgs::LaneArray& lane_msg);
    void wheelCallback(const hmcl_msgs::VehicleStatus& state_msg);

    void flagCallback(const std_msgs::Int16ConstPtr& flag_msg);
    void globalCallback(const hmcl_msgs::LaneArray& lane_msg);

    void PreparePhase(double deceleration);
    int FindIndex(const hmcl_msgs::Lane& lane, double dist, geometry_msgs::Pose pose);
    hmcl_msgs::LaneArray cuttraj(const hmcl_msgs::LaneArray& msg);

    hmcl_msgs::Lane getLaneChangePaths(hmcl_msgs::LaneArray lane_msgs, Point LC_Point);
    hmcl_msgs::Lane getLaneChangePathPrepareSegment(hmcl_msgs::Lane lane_data, Sector section);
    hmcl_msgs::Lane getLaneChangePathSegment(hmcl_msgs::Lane lane_data, Sector section);
    hmcl_msgs::Lane constructCandidatePath(Point LC_Point, hmcl_msgs::Lane lane_prepare, hmcl_msgs::Lane lane_end);

    hmcl_msgs::Lane bezier(hmcl_msgs::Lane lane, geometry_msgs::Pose pos1, geometry_msgs::Pose pos2, geometry_msgs::Pose pos3, geometry_msgs::Pose pos4, double lc_dist, int nn);
    float getPt( float n1 , float n2 , float perc);

    void viz_local(const hmcl_msgs::Lane& msg);
};