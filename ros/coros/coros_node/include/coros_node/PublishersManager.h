#ifndef PUBLISHERS_MANAGER_H
#define PUBLISHERS_MANAGER_H

#include <map>
#include <string>
#include <ros/ros.h>

/**
 * The PublishersManager class provides facilities for managing several publishers using a single NodeHandle. 
 */
class PublishersManager
{

public:
  
  PublishersManager();
  
  template <typename T> 
  bool createPublisher(std::string publisherId, std::string topicName)
  {
    if (findPublisher(publisherId) != NULL )
    {
      ROS_ERROR("Cannot create publisher on topic \"%s\": publisher with the same ID already exists (\"%s\").", topicName.c_str(), publisherId.c_str());
      return false;  
    }
    
    ros::Publisher publisher = myNH->advertise<T>(topicName, 1000); 
    myPublishers[publisherId] = publisher;
    
    usleep(2000*1000); // necessary to make ros wait before publishing
    ROS_INFO("Publisher created with ID \"%s\" on topic \"%s\".", publisherId.c_str(), topicName.c_str());
    
    return true;
  }


  template <typename T> 
  bool publishMessage(std::string publisherId, T message)
  {
    ros::Publisher* publisher = findPublisher(publisherId); 
    if (publisher == NULL )
    {
      ROS_ERROR("Cannot publish a message: publisher doesn't exist with ID = \"%s\".", publisherId.c_str());
      return false;  
    }
    
    publisher->publish(message); 
    ROS_INFO("Publisher \"%s\" published a message.", publisherId.c_str()); //TODO: it is better to also print the message content (by calling a templated function then instanciated for every message type)
  }
  
  template<class T, class MReq , class MRes >
   bool createService(std::string serviceId, std::string serviceName, bool(T::*srv_func)(MReq &, MRes &), T* object)
  {
    if (findService(serviceId) != NULL )
    {
      ROS_ERROR("Cannot create service on with name \"%s\": service with the same ID already exists (\"%s\").", serviceName.c_str(), serviceId.c_str());
      return false;  
    }
    
    ros::ServiceServer serv = myNH->advertiseService(serviceName, srv_func, object); 
    myServices[serviceId] = serv;
    
    usleep(1000*1000); // necessary to make ros wait before publishing
    ROS_INFO("Service Server created with ID \"%s\" on topic \"%s\".", serviceId.c_str(), serviceName.c_str());
    
    return true;
  }

protected:

  ros::NodeHandle* myNH;
  
  std::map<std::string,ros::Publisher> myPublishers;
  std::map<std::string,ros::ServiceServer> myServices;
  
  ros::Publisher* findPublisher(std::string publisherId);
  ros::ServiceServer* findService(std::string serviceId);

};

#endif //PUBLISHERS_MANAGER_H
