#include "dispatcher_app/DispatcherReceiver.h"
#include "dispatcher_app/DispatcherConfiguration.h"

#include <ros/ros.h>
#include "std_msgs/String.h"

DispatcherReceiver::DispatcherReceiver(const std::string& nodeName, int portNumber)
  : NodeServer(nodeName, portNumber)
{
  	myLocalConfig = DispatcherConfiguration::getInstance();
	init();
}


void DispatcherReceiver::init()
{
    std::vector<std::string> topics = myLocalConfig->getTopics();
    int size = topics.size();
   
    for (int i=0; i<size; i++) 
    {
	createPublisher<std_msgs::String>(topics[i], topics[i]);
    }

    ros::spinOnce();
}


void DispatcherReceiver::forward(const std::string& strMessage, const std::string& fromIP)
{
  unsigned first = strMessage.find("/");
  unsigned last = strMessage.find("{");
  //added by Anis: because the message may contain undesired additional characters after the of the json because the receiving buffer size is larger than actual data received
  unsigned end_of_json = strMessage.find_last_of("}");
  std::string message_type = strMessage.substr(first+1,last-first-1);
  ROS_INFO("end_of_json %d", end_of_json);
  //end_of_json instead of strMessage.size()-1
  std::string json_string  ="";
  json_string = strMessage.substr(last, end_of_json);
  
  ROS_INFO("\n\n[DispatcherReceiver] message_type:\n%s.", message_type.c_str());
  ROS_INFO("\n\n[DispatcherReceiver] strMessage:\n%s.", strMessage.c_str());
  ROS_INFO("\n\n[DispatcherReceiver] json_string:\n%s.", json_string.c_str());

  std_msgs::String msg; 
  msg.data = json_string;
  publishMessage(message_type+"/in_box", msg);
  
}
