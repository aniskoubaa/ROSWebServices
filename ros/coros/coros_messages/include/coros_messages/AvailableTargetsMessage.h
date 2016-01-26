#ifndef AVAILABLE_TARGETS_MESSAGE_H
#define AVAILABLE_TARGETS_MESSAGE_H

#include "BaseMessage.h"
#include <coros_messages/AvailableTargetsMsg.h>
#include <boost/serialization/access.hpp>
#include <boost/serialization/list.hpp>

class AvailableTargetsMessage : public BaseMessage
{
  
public:
  
  friend class boost::serialization::access;
  
  AvailableTargetsMessage() : BaseMessage('V') {}
  
  AvailableTargetsMessage(int code, int rid, std::vector<bool> availability) : BaseMessage('V', code), id(rid)
  {
	  for (int i=0; i<availability.size(); i++)
		  available_targets.push_back(availability[i]);
  }

  AvailableTargetsMessage(const coros_messages::AvailableTargetsMsg msg)
  : BaseMessage('V', msg.message_code)
  {
	  id = msg.id;

    int size = msg.available_targets.size();
    for (int i=0; i<size; i++)
    	available_targets.push_back(msg.available_targets[i]);
  }
   
  coros_messages::AvailableTargetsMsg toMsg()
  {    
	coros_messages::AvailableTargetsMsg msg;
    msg.message_code = message_code;

    msg.id = id ;

    std::list<bool>::const_iterator iterator;
    for (iterator = available_targets.begin(); iterator != available_targets.end(); ++iterator) {
      msg.available_targets.push_back( *iterator);
    }
    
    return msg;
  }
  
  template<class Archive>
  void serialize(Archive & ar, const unsigned int version)
  {
    ar & message_code;
    ar & id;
    ar & available_targets;
  }

 int id;

 std::list<bool> available_targets;

};

#endif // AVAILABLE_TARGETS_MESSAGE_H
