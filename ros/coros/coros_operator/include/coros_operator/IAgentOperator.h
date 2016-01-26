#ifndef I_AGENT_OPERATOR_H
#define I_AGENT_OPERATOR_H

#include <ros/ros.h>

///#include "coros_common/globals.h"
#include "coros_processing/IMessageProcessor.h"
#include "coros_processing/IActionHandler.h"

/**
 * IAgentOperator is an interface that combines the usage of two other super
 * interfaces: IMessageHandler, IActionPerformer. Usually, this interface
 * should be realized by classes that are already subclasses of one of the
 * client base classes (AbstractClient or NodeClient). All developed
 * applications need only to use/extend a server class and an operator derived
 * class.
 */

class IAgentOperator: public IMessageProcessor, public IActionHandler
{

public:
  
  virtual ~IAgentOperator() {}
  
  void handle(BaseAction* a)
  {
    a->execute();
  }

  
protected:
  
 // virtual void send(const std::string& message,  const std::string& destinations, int port) = 0;
 
//  virtual void multicast(const std::string& message, std::string* destinations, int* ports, int size) = 0;
  
/*  void multicast(const std::string& message){
    
    NeighborsConfiguration* manager = NeighborsConfiguration::getInstance();
    std::vector<AgentState*>  agents = manager-> getNeighbors();
    

    int size = agents.size();
    std::string* destinations = new std::string[size];
    int* ports = new int[size];
 
    for( int i = 0; i < size; i++ )
    {
      destinations[i] = agents[i]->getIpAddress();
      ports[i] = agents[i]->getPort();
    }
    
    multicast(message, destinations, ports, size);
  }
  */
  /*
  void send(const std::string& message, int agentId){
    NeighborsConfiguration* manager = NeighborsConfiguration::getInstance();
    AgentState* agent = manager->findNeighbor(agentId);
    ROS_INFO("Operator send message to: %s, %d", agent->getIpAddress().c_str(), COURIER_PORT);
    send(message, agent->getIpAddress(), COURIER_PORT);
  }
  */
  
};

#endif //I_AGENT_OPERATOR_H
