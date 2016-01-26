#ifndef TASK_MESSAGE_H
#define TASK_MESSAGE_H

#include "BaseMessage.h"
#include <coros_messages/TaskMsg.h>

/**
 * TaskMessage used for Assignment phase
 */
class TaskMessage : public BaseMessage
{
  
public:
  
  TaskMessage() : BaseMessage('C') {}
  
  TaskMessage(int code, int rid, int tid) : BaseMessage('C', code), robot_id(rid), task_id(tid) {}
  
  TaskMessage(coros_messages::TaskMsg msg) : BaseMessage('C', msg.message_code), task_id(msg.task_id), robot_id(msg.robot_id)  {}
  
  coros_messages::TaskMsg toMsg()
  {
	coros_messages::TaskMsg msg;
    msg.message_code = message_code;
    msg.robot_id = robot_id;
    msg.task_id = task_id;
    return msg;
  }
  
  template<class Archive>
  void serialize(Archive & ar, const unsigned int version)
  {
    ar & message_code;
    ar & robot_id;
    ar & task_id;
  }
  
  int task_id;
  
  int robot_id;
};

#endif // TASK_MESSAGE_H
