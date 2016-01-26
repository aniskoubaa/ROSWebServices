#ifndef HELLO_MESSAGE_H
#define HELLO_MESSAGE_H

#include "BaseMessage.h"
#include <coros_messages/HelloMsg.h>


/**
 * HelloMessage used for Initilization phase
 */
class HelloMessage : public BaseMessage
{
  
public:
  
  HelloMessage() : BaseMessage('H') {}
  
  //HelloMessage(int code, unsigned short r_id, std::string r_ip, int r_port) : BaseMessage('H', code), id(r_id), ip(r_ip), port(r_port){}
  
  HelloMessage(int code, int r_id, std::string r_ip, int r_port, double r_ts, std::string r_role, std::string r_status) :
	  BaseMessage('H', code), id(r_id), ip(r_ip), port(r_port), timestamp (r_ts), role(r_role), status(r_status){}

  HelloMessage(coros_messages::HelloMsg msg) :
	  BaseMessage('H', msg.message_code), id(msg.id) , ip(msg.ip), port(msg.port),  timestamp (msg.timestamp), role(msg.role), status(msg.status){}
  
  coros_messages::HelloMsg toMsg()
  {
	  coros_messages::HelloMsg msg;
    msg.message_code = message_code;
    msg.id = id;
    msg.ip = ip;
    msg.port = port;
    msg.timestamp = timestamp;
    msg.role = role;
    msg.status = status;
    return msg;
  }
  
  template<class Archive>
  void serialize(Archive & ar, const unsigned int version)
  {
    ar & message_code;
    ar & id;
    ar & ip;
    ar & port;
    ar & timestamp;
    ar & role;
    ar & status;
  }

  int id;
  std::string ip;
  int port;
  double timestamp;
  std::string role;
  std::string status;

};

#endif // HELLO_MESSAGE_H
