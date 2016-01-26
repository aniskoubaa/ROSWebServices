#ifndef NODE_CLIENT_H
#define NODE_CLIENT_H

#include "coros_node/Node.h"
#include "AbstractClient.h"

/**
 * The NodeClient (abstract) class is the (direct or indirect) parent of all UPD clients in any application
 * in which the client receives the messages from the server of the same machine using 
 * ROS topic mechanism.
 */
class NodeClient : public Node, public AbstractClient
{
  
public:
  
  NodeClient(const std::string& nodeName);
  
};

#endif //NODE_CLIENT_H
