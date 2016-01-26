#ifndef COST_MESSAGE_H
#define COST_MESSAGE_H

#include "BaseMessage.h"
#include <coros_messages/CostMsg.h>

/**
 * RobotTaskCostMessage used for Announcement and Bidding phases
 * NOTE: It is better that this class doesn't inherit from TaskeMessage 
 *       to avoid any eventual confusion at the template member functions instaciation/specialization
 */
class CostMessage : public BaseMessage
{

public:
  
  CostMessage() : BaseMessage('D') {}

  CostMessage(int code, int rid, int tid, double c) : BaseMessage('D', code), robot_id(rid), task_id(tid), cost(c) {}
  
  CostMessage(coros_messages::CostMsg msg) : BaseMessage('D', msg.message_code), robot_id(msg.robot_id), task_id(msg.task_id), cost(msg.cost){}
  
  coros_messages::CostMsg toMsg()
  {
	  coros_messages::CostMsg msg;
    msg.message_code = message_code;
    msg.task_id = task_id;
    msg.robot_id = robot_id;
    msg.cost = cost;
    return msg;
  }
  
  template<class Archive>
  void serialize(Archive & ar, const unsigned int version)
  {
    ar & message_code;
    ar & robot_id;
    ar & task_id;
    ar & cost;
  }
  
  int robot_id;
  
  int task_id;
  
  double cost;
  
};

#endif //COST_MESSAGE_H
