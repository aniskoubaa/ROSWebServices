#ifndef CONNECTION_MESSAGE_H
#define CONNECTION_MESSAGE_H

#include "BaseMessage.h"
#include <robot_controller/ConnectionMsg.h>
#include <boost/serialization/access.hpp>
#include <boost/serialization/list.hpp>

class ConnectionMessage : public BaseMessage
{
  
public:
  
  friend class boost::serialization::access;
  
  ConnectionMessage() : BaseMessage('A') {}
  
  ConnectionMessage(const robot_controller::ConnectionMsg msg) 
  : BaseMessage('A', msg.message_code), control_ip(msg.control_ip), control_port(msg.control_port)
  {
    int size = msg.robot_ports.size();
    for (int i=0; i<size; i++)
      robot_ports.push_back(msg.robot_ports[i]);

    size = msg.robot_ips.size();
    for (int i=0; i<size; i++)
      robot_ips.push_back(msg.robot_ips[i]);
  }
   
  robot_controller::ConnectionMsg toMsg()
  {    
    robot_controller::ConnectionMsg msg;
    msg.message_code = message_code;
    msg.control_ip = control_ip;
    msg.control_port = control_port;
    
    std::list<int>::const_iterator iterator;
    for (iterator = robot_ports.begin(); iterator != robot_ports.end(); ++iterator) {
      msg.robot_ports.push_back( *iterator);
    }
    
    std::list<std::string>::const_iterator iterator2;
    for (iterator2 = robot_ips.begin(); iterator2 != robot_ips.end(); ++iterator2) {
      msg.robot_ips.push_back( *iterator2);
    }
 
    return msg;
  }
  
  template<class Archive>
  void serialize(Archive & ar, const unsigned int version)
  {
    ar & message_code;
    ar & control_ip;
    ar & control_port;
    ar & robot_ports;
    ar & robot_ips;
  }

  std::string control_ip;

  int control_port;
  
  std::list<std::string>  robot_ips;
  
  std::list<int> robot_ports;
    
};

#endif // CONNECTION_MESSAGE_H
