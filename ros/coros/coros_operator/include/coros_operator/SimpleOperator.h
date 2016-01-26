#ifndef SIMPLE_OPERATOR_H
#define SIMPLE_OPERATOR_H

#include "coros_communication/NodeClient.h"
#include "IAgentOperator.h"

/**
 * SimpleOperator is a class used instead of a client, because itself is subclass of a client 
 * and provide access to more functionnalities through the inherited methodes. This operator class
 * used when we need not to have a client that deals with an instance of class Robot.
 */

class SimpleOperator: public IAgentOperator, public NodeClient
{
  
public:
  
  SimpleOperator(const std::string& nodeName) : NodeClient(nodeName) {}
  

protected:

/*  void multicast(const std::string& message){
     IAgentOperator::multicast(message);
  }
*/
  //void send(const std::string& message, int agentId){
    // IAgentOperator::send(message, agentId);
  //}
  /*void multicast(const std::string& message, std::string* destinations, int* ports, int size) {
    NodeClient::multicast(message, destinations, ports, size);
  }  
  
  void send(const std::string& message,  const std::string& destination, int port) {
    NodeClient::send(message, destination, port);
  }*/
  
    
};

#endif //SIMPLE_OPERATOR_H
