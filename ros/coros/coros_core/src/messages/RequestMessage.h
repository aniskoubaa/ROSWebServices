#ifndef COURIER_DELIVERY_REQUEST_MESSAGE_H
#define COURIER_DELIVERY_REQUEST_MESSAGE_H

#include "BaseMessage.h"
#include <robot_controller/RequestMsg.h>
#include <boost/serialization/access.hpp>
#include <boost/serialization/list.hpp>

namespace courier_delivery 
{
  
class RequestMessage : public BaseMessage
{
  
public:
  
  friend class boost::serialization::access;
  
  RequestMessage() : BaseMessage('F') {}
  
  RequestMessage(int code) : BaseMessage('F', code) {}
  
  RequestMessage(const robot_controller::RequestMsg msg) 
  : BaseMessage('F', msg.message_code),
    source_x(msg.source_x), source_y(msg.source_y), target_x(msg.target_x), target_y(msg.target_y)
  {}
   
  robot_controller::RequestMsg toMsg()
  {    
    robot_controller::RequestMsg msg;
    msg.message_code = message_code;
    msg.robot_id = robot_id;
    msg.source_x = source_x;
    msg.source_y = source_y;
    msg.target_x = target_x;
    msg.target_y = target_y;
    return msg;
  }
  
  template<class Archive>
  void serialize(Archive & ar, const unsigned int version)
  {
    ar & message_code;
    ar & robot_id;
    ar & source_x;
    ar & source_y;  
    ar & target_x;
    ar & target_y;
  }

  int robot_id;
  
  double source_x;
  
  double source_y;
  
  double target_x;
  
  double target_y;
    
};

} //namespace courrier_delivery

#endif //COURIER_DELIVERY_REQUEST_MESSAGE_H
