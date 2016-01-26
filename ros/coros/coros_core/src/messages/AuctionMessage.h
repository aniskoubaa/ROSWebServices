#ifndef COURIER_DELIVERY_AUCTION_MESSAGE_H
#define COURIER_DELIVERY_AUCTION_MESSAGE_H

#include "BaseMessage.h"
#include <robot_controller/AuctionMsg.h>
#include <boost/serialization/access.hpp>
#include <boost/serialization/list.hpp>

namespace courier_delivery 
{
  
class AuctionMessage : public BaseMessage
{
  
public:
  
  friend class boost::serialization::access;
  
  AuctionMessage() : BaseMessage('E') {}
  
  AuctionMessage(const robot_controller::AuctionMsg msg) 
  : BaseMessage('E', msg.message_code), user_ip(msg.user_ip), user_port(msg.user_port),
    source_x(msg.source_x), source_y(msg.source_y), target_x(msg.target_x), target_y(msg.target_y)
  {}
   
  robot_controller::AuctionMsg toMsg()
  {    
    robot_controller::AuctionMsg msg;
    msg.message_code = message_code;
    msg.user_ip = user_ip;
    msg.user_port = user_port;
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
    ar & user_ip;
    ar & user_port;
    ar & source_x;
    ar & source_y;  
    ar & target_x;
    ar & target_y;
  }

  std::string user_ip;

  int user_port;
  
  double source_x;
  
  double source_y;
  
  double target_x;
  
  double target_y;
    
};

} //namespace courier_delivery

#endif // COURIER_DELIVERY_AUCTION_MESSAGE_H
