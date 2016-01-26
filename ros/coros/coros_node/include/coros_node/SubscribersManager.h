#ifndef SUBSCRIBERS_MANAGER_H
#define SUBSCRIBERS_MANAGER_H

#include <map>
#include <string>
#include <ros/ros.h>

/**
 * The SubscribersManager class provides facilities for managing several subscribers using a single NodeHandle. 
 */
class SubscribersManager
{

public:
 
  SubscribersManager();
  
  //keep this function here, in the header, otherwise link error
  template<class M , class T >
  bool createSubscriber(std::string subscriberId, std::string topicName, void(T::*fp)(M), T *object)
  { 
    if (findSubscriber(subscriberId) != NULL )
    {
      ROS_ERROR("Cannot create subscriber of topic \"%s\": subscriber with the same ID already exists (\"%s\").", topicName.c_str(), subscriberId.c_str());
      return false;  
    }
    
    ros::Subscriber subscriber = myNH->subscribe(topicName, 1000, fp, object);
    mySubscribers[subscriberId] = subscriber;
   
    
    ROS_INFO("Subscriber created with ID \"%s\" of topic \"%s\".", subscriberId.c_str(), topicName.c_str());
    return true;
  }
  
  /*
  template<class T >
  bool subscribeToService(std::string serviceId, std::string serviceName)
  { 
    if (findSubscribedServices(serviceId) != NULL )
    {
      ROS_ERROR("Cannot create subscribe to the service \"%s\": because already subscribed to. serviceID=  (\"%s\").", serviceName.c_str(), serviceId.c_str());
      return false;  
    }
    
    ros::ServiceClient srvClient = myNH->serviceClient<T>(serviceName);
    mySubscribedServices[serviceId] = srvClient;
   
    
    ROS_INFO("Subscriber created with ID \"%s\" of topic \"%s\".", serviceId.c_str(), serviceName.c_str());
    return true;
  }
  
  template <typename T> 
  bool callService(std::string serviceId)
  {
    ros::Publisher* publisher = findPublisher(publisherId); 
    if (publisher == NULL )
    {
      ROS_ERROR("Cannot publish a message: publisher doesn't exist with ID = \"%s\".", publisherId.c_str(), publisherId.c_str());
      return false;  
    }
    
    publisher->publish(message); 
    ROS_INFO("Publisher \"%s\" published a message.", publisherId.c_str()); //TODO: it is better to also print the message content (by calling a templated function then instanciated for every message type)
  }
  */

protected:

  ros::NodeHandle * myNH;
  
  std::map<std::string,ros::Subscriber> mySubscribers;
  //std::map<std::string,ros::ServiceClient> mySubscribedServices;
  
  ros::Subscriber* findSubscriber(std::string subscriberId);
  //ros::ServiceClient* findSubscribedServices(std::string serviceId);

};

#endif //PUBLISHERS_MANAGER_H
