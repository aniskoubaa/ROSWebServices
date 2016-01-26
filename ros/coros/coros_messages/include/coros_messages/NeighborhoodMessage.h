#ifndef NEIGHBORHOOD_MESSAGE_H
#define NEIGHBORHOOD_MESSAGE_H

#include "BaseMessage.h"
#include <coros_messages/NeighborhoodMsg.h>
#include <boost/serialization/access.hpp>
#include <boost/serialization/list.hpp>

class NeighborhoodMessage : public BaseMessage
{
  
public:
  
  friend class boost::serialization::access;
  
  NeighborhoodMessage() : BaseMessage('G') {}
  
  NeighborhoodMessage(const coros_messages::NeighborhoodMsg msg)
  : BaseMessage('G', msg.message_code)
  {
    int size = msg.ids.size();
    for (int i=0; i<size; i++)
      ids.push_back(msg.ids[i]);

    size = msg.ip_addresses.size();
    for (int i=0; i<size; i++)
      ip_addresses.push_back(msg.ip_addresses[i]);
    
    size = msg.ports.size();
    for (int i=0; i<size; i++)
      ports.push_back(msg.ports[i]);

    size = msg.timestamps.size();
    for (int i=0; i<size; i++)
      timestamps.push_back(msg.timestamps[i]);

    size = msg.roles.size();
    for (int i=0; i<size; i++)
    	roles.push_back(msg.roles[i]);

    size = msg.statuses.size();
    for (int i=0; i<size; i++)
    	statuses.push_back(msg.statuses[i]);
  }
   
  coros_messages::NeighborhoodMsg toMsg()
  {    
	coros_messages::NeighborhoodMsg msg;
    msg.message_code = message_code;

    std::list<int>::const_iterator iterator;
    for (iterator = ids.begin(); iterator != ids.end(); ++iterator) {
      msg.ids.push_back( *iterator);
    }
    
    std::list<std::string>::const_iterator iterator2;
    for (iterator2 = ip_addresses.begin(); iterator2 != ip_addresses.end(); ++iterator2) {
      msg.ip_addresses.push_back( *iterator2);
    }
    
    std::list<int>::const_iterator iterator3;
    for (iterator3 = ports.begin(); iterator3 != ports.end(); ++iterator3) {
      msg.ports.push_back( *iterator3);
    }
    
    std::list<double>::const_iterator iterator4;
    for (iterator4 = timestamps.begin(); iterator4 != timestamps.end(); ++iterator4) {
      msg.timestamps.push_back( *iterator4);
    }

    std::list<std::string>::const_iterator iterator5;
    for (iterator5 = roles.begin(); iterator5 != roles.end(); ++iterator5) {
      msg.roles.push_back( *iterator5);
    }

    std::list<std::string>::const_iterator iterator6;
    for (iterator6 = statuses.begin(); iterator6 != statuses.end(); ++iterator6) {
      msg.statuses.push_back( *iterator6);
    }

    return msg;
  }
  
  template<class Archive>
  void serialize(Archive & ar, const unsigned int version)
  {
    ar & message_code;
    ar & ids;
    ar & ip_addresses;
    ar & ports;
    ar & timestamps;
    ar & roles;
    ar & statuses;
  }

 std::list<int> ids;

 std::list<std::string> ip_addresses;

 std::list<int> ports;
 
 std::list<double> timestamps;
 
 std::list<std::string> roles;
 
 std::list<std::string> statuses;

};

#endif // NEIGHBORHOOD_MESSAGE_H
