#include "coros_node/PublishersManager.h"


PublishersManager::PublishersManager() : myPublishers(), myNH(NULL)
{

}

ros::Publisher* PublishersManager::findPublisher(std::string publisherId)
{
  std::map<std::string, ros::Publisher>::iterator iter = myPublishers.find(publisherId);
  if (iter != myPublishers.end() )
    return &iter->second;
  
  return NULL;
}

ros::ServiceServer* PublishersManager::findService(std::string serviceId)
{
  std::map<std::string, ros::ServiceServer>::iterator iter = myServices.find(serviceId);
  if (iter != myServices.end() )
    return &iter->second;
  
  return NULL;
}
