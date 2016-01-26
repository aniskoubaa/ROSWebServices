#ifndef ROBOT_OPERATOR_H
#define ROBOT_OPERATOR_H

#include "robot_control/RobotClient.h"
#include "IRobotOperator.h"


/**
 * RobotOperator is a class used instead of a client, because itself is subclass of a client 
 * and provide access to more functionnalities through the inherited methodes. This operator class
 * used when we need to have a client that deal with an instance of class Robot, in other words 
 * when we need to send commands or get information from a real robot runing the specified nodes.
 */

class RobotOperator: public IRobotOperator, public RobotClient
{
  
public:
  
  RobotOperator(int robotId, const std::string& nodeName) : RobotClient(robotId, nodeName) {}
    
protected:

  void perform(BaseTask* task) { task->execute(&myRobot); }
  
 // void multicast(const std::string& message, std::string* destinations, int* ports, int size) {
 //   RobotClient::multicast(message, destinations, ports, size);
 // }
  
 // void send(const std::string& message,  const std::string& destination, int port) {
 //   RobotClient::send(message, destination, port);
 // }
    
};

#endif //ROBOT_OPERATOR_H
