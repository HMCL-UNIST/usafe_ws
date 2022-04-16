// #include <dynamic_reconfigure/server.h>
// #include <vehicle_bridge/testConfig.h>

// void callback(vehicle_bridge::testConfig &config, uint32_t level)
// {
//   ROS_INFO("Reconfigure Request: \n AD_STR_MODE_CMD: %s,\n AD_STR_POS_CMD: %d,\n AD_SCC_ACCEL_CMD: %d,\n AD_SCC_TAKEOVER_CMD: %s,\n AD_LEFT_TURNLAMP_STAT: %s,\n AD_RIGHT_TURNLAMP_STAT: %s,\n AD_HAZARD_STAT: %s,\n AD_GEAR_POS_CMD: %d,\n AD_SCC_MODE_CMD: %d,\n",
//   config.AD_STR_MODE_CMD?"True":"False", 
//   config.AD_STR_POS_CMD,
//   config.AD_SCC_ACCEL_CMD, 
//   config.AD_SCC_TAKEOVER_CMD?"True":"False",
//   config.AD_LEFT_TURNLAMP_STAT?"True":"False",
//   config.AD_RIGHT_TURNLAMP_STAT?"True":"False",
//   config.AD_HAZARD_STAT?"True":"False",
//   config.AD_GEAR_POS_CMD,
//   config.AD_SCC_MODE_CMD);
// }

// int main (int argc, char** argv)
// {
//   ros::init(argc, argv, "VehicleBridge");
//   dynamic_reconfigure::Server<vehicle_bridge::testConfig> srv;
//   dynamic_reconfigure::Server<vehicle_bridge::testConfig>::CallbackType f;
//   f = boost::bind(&callback, _1, _2);
//   srv.setCallback(f);
  
//   ros::NodeHandle nh_can, nh_acc, nh_steer, nh_light;
//   VehicleBridge VehicleBridge_(nh_can,nh_acc,nh_steer,nh_light);

//   ros::CallbackQueue callback_queue_can, callback_queue_acc, callback_queue_steer, callback_queue_light;
//   nh_can.setCallbackQueue(&callback_queue_can);
//   nh_acc.setCallbackQueue(&callback_queue_acc);
//   nh_steer.setCallbackQueue(&callback_queue_steer);
//   nh_light.setCallbackQueue(&callback_queue_light);

//   std::thread spinner_thread_can([&callback_queue_can]() {
//     ros::SingleThreadedSpinner spinner_can;
//     spinner_can.spin(&callback_queue_can);
//   });

//   std::thread spinner_thread_acc([&callback_queue_acc]() {
//     ros::SingleThreadedSpinner spinner_acc;
//     spinner_acc.spin(&callback_queue_acc);
//   });

//   std::thread spinner_thread_steer([&callback_queue_steer]() {
//     ros::SingleThreadedSpinner spinner_steer;
//     spinner_steer.spin(&callback_queue_steer);
//   });

//   std::thread spinner_thread_light([&callback_queue_light]() {
//     ros::SingleThreadedSpinner spinner_light;
//     spinner_light.spin(&callback_queue_light);
//   });

//   ros::spin();

//   spinner_thread_can.join();
//   spinner_thread_acc.join();
//   spinner_thread_steer.join();
//   spinner_thread_light.join();


//   return 0;

// }
