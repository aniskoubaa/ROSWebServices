#ifndef ROBOT_MESSAGE_H
#define ROBOT_MESSAGE_H

#include "BaseMessage.h"
#include <coros_messages/RobotMsg.h>


/**
 * RobotMessage used for Initilization phase
 */
class RobotMessage : public BaseMessage
{
  
public:
  
  RobotMessage() : BaseMessage('B') {}
  
  RobotMessage(int code, int rid) : BaseMessage('B', code), robot_id(rid){}
  
  RobotMessage(coros_messages::RobotMsg msg) : BaseMessage('B', msg.message_code), robot_id(msg.robot_id) {}
  
  coros_messages::RobotMsg toMsg()
  {
	coros_messages::RobotMsg msg;
    msg.message_code = message_code;
    msg.robot_id = robot_id;
    return msg;
  }
  
  template<class Archive>
  void serialize(Archive & ar, const unsigned int version)
  {
    ar & message_code;
    ar & robot_id;
  }

  int robot_id;

};

#endif // ROBOT_MESSAGE_H
