#include <ros/ros.h>
#include <coros_messages/HelloMsg.h>

#include "coros_simulation_helper/DiscoveryHelperServer.h"
#include "coros_messages/HelloMessage.h"

#include "coros_common/string_lib.h"
#include "coros_common/serial_lib.h"
#include "coros_common/globals.h"


DiscoveryHelperServer::DiscoveryHelperServer(const std::string& nodeName, int portNumber)
  : NodeServer(nodeName, portNumber)
{
	init();
}


void DiscoveryHelperServer::init()
{

  ROS_INFO("\n[Simulation Server]\n\tAdvertising its topics...");
  
  createPublisher<coros_messages::HelloMsg>("hello_pub", "agent_simulation/hello_topic"); // HELLO Publisher
  
  ROS_INFO("\n[Simulation Server]\n\tTopics advertising completed.");
  
}


void DiscoveryHelperServer::forward(const std::string& strMessage, const std::string& fromIP)
{
  char serialization_letter = strMessage[0];
  std::string str = "";

  switch (serialization_letter) {
    case 'H': // message_code == HELLO_CODE
    {
      HelloMessage message =  deserializeMessage<HelloMessage>(strMessage);
      coros_messages::HelloMsg m = message.toMsg();
      publishMessage("hello_pub", m);
      ROS_INFO("[Simulation Server][Event]: received/forwarded HELLO message:\n%s.", mtos(m).c_str());
      break;
    }
    default:
     ROS_ERROR("[Simulation Server][Error]: unable to identify message serialization letter: %c.",  serialization_letter);
  }
  
}
