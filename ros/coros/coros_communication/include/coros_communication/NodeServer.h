#ifndef NODE_SERVER_H
#define NODE_SERVER_H


#include "coros_node/Node.h"
#include "AbstractServer.h"

/**
 * The NodeServer is the (direct or indirect) parent (abstract) class of all UPD servers in any application
 * in which the server forwards the messages to the client of the same machine using 
 * ROS topic mechanism.
 */
class NodeServer : public Node, public AbstractServer
{
  
public:
  
  NodeServer(const std::string& nodeName, int port);
  
  void process(const std::string&  message, const std::string& fromIP);
  
protected:
  
  virtual void forward(const std::string& message, const std::string& fromIP) = 0;
  
  bool again();
  
};

#endif //NODE_SERVER_H
