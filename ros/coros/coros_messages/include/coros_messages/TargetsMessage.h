#ifndef TARGETS_MESSAGE_H
#define TARGETS_MESSAGE_H

#include "BaseMessage.h"
#include <coros_messages/TargetsMsg.h>
#include <boost/serialization/access.hpp>
#include <boost/serialization/list.hpp>

class TargetsMessage : public BaseMessage
{
  
public:
  
  friend class boost::serialization::access;
  
  TargetsMessage() : BaseMessage('T') {}
  
  TargetsMessage(const coros_messages::TargetsMsg msg)
  : BaseMessage('T', msg.message_code)
  {
    int size = msg.targets_list.size();
    for (int i=0; i<size; i++)
    	targets_list.push_back(msg.targets_list[i]);
  }

  TargetsMessage(int code, int aid, int targets_size, double targets[])
   : BaseMessage('T', code)
   {
	 agent_id = aid;
	 targets_number = targets_size;
     for (int i=0; i<targets_size; i++)
     	targets_list.push_back(targets[i]);
   }
   
  coros_messages::TargetsMsg toMsg()
  {    
	coros_messages::TargetsMsg msg;
    msg.message_code = message_code;
    msg.targets_number = targets_number;
    msg.agent_id = agent_id;

    std::list<double>::const_iterator iterator;
    for (iterator = targets_list.begin(); iterator != targets_list.end(); ++iterator) {
      msg.targets_list.push_back( *iterator);
    }
    
    return msg;
  }
  
  template<class Archive>
  void serialize(Archive & ar, const unsigned int version)
  {
    ar & message_code;
    ar & agent_id;
    ar & targets_number;
    ar & targets_list;
  }

 int agent_id;
 
 int targets_number;

 std::list<double> targets_list;
    
};

#endif // TARGETS_MESSAGE_H
