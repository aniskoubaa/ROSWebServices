#ifndef ROBOT_CLIENT_H
#define ROBOT_CLIENT_H

#include <string>

#include "TurtlebotRobot.h"
#include "coros_common/string_lib.h"
#include "coros_communication/NodeClient.h"

/**
 * The RobotClient is a parent (abstract) class for all robot client apps.
 */
class RobotClient : public NodeClient
{
  
public:
  
  RobotClient(int robotId, const std::string& nodeName) : 
    NodeClient(nodeName), myRobotId(robotId), 
    myRobot( myNH, std::string("turtlebot_" + itos(robotId)) ) { }
  
  
protected:
  
  int myRobotId;
  
  TurtlebotRobot myRobot;
  
  std::string myControlStationIP; // IP addr of the controlling station
  
  int myControlStationPort; // Port number of the controlling station

  double * myCoordsX;
  
  double * myCoordsY;
  
};
#endif //ROBOT_CLIENT_H
