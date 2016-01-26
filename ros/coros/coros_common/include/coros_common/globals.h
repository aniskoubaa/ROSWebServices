#ifndef GLOBALS_H
#define GLOBALS_H

#include <string>

//namespace coros_common
//{
	//namespace globals
	//{
		//int RUNNING_MODE = 0; // 0 for simulation mode, 1 for experimental mode
	//} // namespace globals
//} // namespace coros_common

#define DISPLAY_DEBUG_MESSAGES_LEVEL_1
#define DISPLAY_DEBUG_MESSAGES_LEVEL_2
#define DISPLAY_DEBUG_MESSAGES_LEVEL_3

#define DISPLAY_EXEC_MESSAGES_LEVEL

//const int COURIER_PORT = 15500;

//unsigned short robot_ids[]={1,2,3,4,5};
//const unsigned short robot_ids[]={1,2};
//unsigned short task_ids[]={1,2,3,4,5};
//const unsigned short task_ids[]={1,2};

//const std::string robot_addrs[]={
//  "192.168.1.112", //robot 1
//    "192.168.1.106"//robot 2
//      "192.168.100.6",
//        "192.168.100.6",
//          "192.168.100.6",
//};

//const std::string control_station_addr = "192.168.1.140";

//const unsigned short control_station_port = 15000;

//const unsigned short robot_ports[]={
 // 15000,
   // 15000
//      15503,
//        15504,
//          15505,
//};

/*int robot_task_costs [][5]= {
  {5,4,3,2,1},
  {3,10,3,1,2},
  {5,3,1,3,2},
  {5,1,4,3,2},
  {1,5,4,3,2},
};*/

//const int robot_task_costs [][2]= {
  //{5,4},{3,10}
  
//};



enum { CONNECTION_CODE,      RESULT_CODE,  		INITIALIZATION_CODE,
	   ANNOUNCEMENT_CODE,    BIDDING_CODE, 		ASSIGNMENT_CODE,
	   SWAPPING_CODE,        AUCTION_CODE, 		REQUEST_CODE,
	   ACKNOWLEDGEMENT_CODE, HELLO_FROM_ROBOT, 	HELLO_FROM_CONTROL_STATION,
	   TARGETS_LIST_CODE,	 AVAILABILITY_CODE};

#endif //GLOBALS_H
