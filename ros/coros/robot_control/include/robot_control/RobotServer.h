#ifndef ROBOT_SERVER_H
#define ROBOT_SERVER_H

#include "coros_communication/NodeServer.h"

/**
 * The RobotServer is a parent class for all servers to be run on the robot side.
 */
class RobotServer : public NodeServer
{

public:
  
  RobotServer(int robotId, const std::string& nodeName, int portNumber) : 
    NodeServer(nodeName, portNumber),  myRobotId(robotId){}
    
  void setRobotId(int id){ myRobotId = id; }
  
  int getRobotId(){ return myRobotId; }

private:
  
  int myRobotId;
  
  //NOTE: Unlike the client, the server doesn't need to aggregate 
  //      the Robot class since it forwards all needed actions  to the client
  
};
#endif //ROBOT_SERVER_H
