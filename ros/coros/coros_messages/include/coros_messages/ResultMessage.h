#ifndef RESULT_MESSAGE_H
#define RESULT_MESSAGE_H

#include "BaseMessage.h"
#include <robot_controller/ResultMsg.h>
#include <boost/serialization/access.hpp>
#include <boost/serialization/list.hpp>

class ResultMessage : public BaseMessage
{
  
public:
  
  friend class boost::serialization::access;
  
  ResultMessage() : BaseMessage('Z') {}
  
  ResultMessage(int code, bool b, int rid, double c, int tasks[], double costs[], int size) 
  : BaseMessage('Z', code), successed(b), robot_id(rid), robot_cost(c), tasks_number(size)
  {
    for (int i=0; i<tasks_number; i++)
      performed_tasks.push_back(tasks[i]);
    for (int i=0; i<tasks_number; i++)
      detailed_costs.push_back(costs[i]);
  }
  
  ResultMessage(robot_controller::ResultMsg msg) 
  : BaseMessage('Z', msg.message_code), successed(msg.successed), robot_id(msg.robot_id), robot_cost(msg.robot_cost)
  {
    int size = msg.performed_tasks.size();
    for (int i=0; i<size; i++)
      performed_tasks.push_back(msg.performed_tasks[i]);

    size = msg.detailed_costs.size();
    for (int i=0; i<size; i++)
      detailed_costs.push_back(msg.detailed_costs[i]);
  }
   
  robot_controller::ResultMsg toMsg()
  {
    robot_controller::ResultMsg msg;
    msg.message_code = message_code;
    msg.successed = successed;
    msg.robot_id = robot_id;
    msg.robot_cost = robot_cost;
    
    std::list<int>::const_iterator iterator;
    for (iterator = performed_tasks.begin(); iterator != performed_tasks.end(); ++iterator) {
      msg.performed_tasks.push_back( *iterator);
    }
    
    std::list<double>::const_iterator iterator2;
    for (iterator2 = detailed_costs.begin(); iterator2 != detailed_costs.end(); ++iterator2) {
      msg.detailed_costs.push_back( *iterator2);
    }
    
    return msg;
  }
  
  template<class Archive>
  void serialize(Archive & ar, const unsigned int version)
  {
    ar & message_code;
    ar & successed;
    ar & robot_id;
    ar & robot_cost;
    ar & performed_tasks;
    ar & detailed_costs;
    ar & tasks_number;
  }
  
  bool successed;
  
  int robot_id;
  
  double robot_cost;
  
  std::list<int> performed_tasks;
  
  std::list<double> detailed_costs;
  
  int tasks_number;

};

#endif // RESULT_MESSAGE_H
