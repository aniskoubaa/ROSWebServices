#include <ros/ros.h>
#include "coros_common/string_lib.h"
#include "coros_common/serial_lib.h"

#include "dispatcher_app/DispatcherSender.h"
#include "dispatcher_app/DispatcherConfiguration.h"


DispatcherSender::DispatcherSender(const std::string& nodeName) : SimpleOperator(nodeName)
{
  myLocalConfig = DispatcherConfiguration::getInstance();

  init();
}


void DispatcherSender::init()
{
    std::vector<std::string> topics = myLocalConfig->getTopics();
    int size = topics.size();
   
    for (int i=0; i<size; i++) 
    {
	createSubscriber(topics[i], topics[i], &DispatcherSender::outboxCallback, this); 
    }

    ros::spin();
}


void DispatcherSender::outboxCallback(const coros_messages::OutBoxMsg::ConstPtr& msg)
{
  ROS_INFO("[DispatcherSender][Event]: received OutBox message: \n%s.", mtos(*msg).c_str());
  
  // prepare the message: ros message type + json message content
  std::string message = msg->message_type + msg->message_content;
  
  // send the message
  if (msg->header.distribution_mode == "unicast")
  {
  	send(message, msg->header.ip_addresses[0], msg->header.ports[0]);
  } 
  else if (msg->header.distribution_mode == "multicast")
  {
  	//multicast(message, &(msg->header.ip_addresses)[0], &(msg->header.ports)[0], msg->header.ports.size());
	
  } 
  else if (msg->header.distribution_mode == "broadcast")
  {
  	broadcast(message, msg->header.ports[0]);
  } else {
    ROS_ERROR("[DispatcherSender][ERROR]: unknown distribution mode: %s.", (msg->header.distribution_mode).c_str());
  }
}
