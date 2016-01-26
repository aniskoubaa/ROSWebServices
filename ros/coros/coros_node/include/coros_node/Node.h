#ifndef ROS_NODE_H
#define ROS_NODE_H

#include <string>

#include "PublishersManager.h"
#include "SubscribersManager.h"

/**
 * The Node class represents a ROS node to be used as it is or extended if necessary.
 */

class Node : public SubscribersManager , public PublishersManager
{

public:
  
  Node(const std::string& name);

protected:
 
  std::string myName;
  
  ros::NodeHandle myNH;
  
  bool isOK();

};

#endif //ROS_NODE_H
