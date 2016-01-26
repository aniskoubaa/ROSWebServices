#include "coros_node/SubscribersManager.h"


SubscribersManager::SubscribersManager() : mySubscribers(), myNH(NULL)
{

}


ros::Subscriber* SubscribersManager::findSubscriber(std::string subscriberId)
{
  std::map<std::string, ros::Subscriber>::iterator iter = mySubscribers.find(subscriberId);
  if (iter != mySubscribers.end() )
    return &iter->second;
  
  return NULL;
}
/*
ros::ServiceClient* SubscribersManager::findSubscribedServices(std::string serviceId)
{
  std::map<std::string, ros::ServiceClient>::iterator iter = mySubscribedServices.find(serviceId);
  if (iter != mySubscribedServices.end() )
    return &iter->second;
  
  return NULL;
}
*/
