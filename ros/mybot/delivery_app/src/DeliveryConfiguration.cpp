#include "delivery_app/DeliveryConfiguration.h"

DeliveryConfiguration* DeliveryConfiguration::sInstance = NULL;


DeliveryConfiguration::DeliveryConfiguration(int runningMode) : 
	AgentConfiguration(runningMode) {}
 
  
DeliveryConfiguration* DeliveryConfiguration::getInstance()
{
  if (sInstance == NULL)
  {
    sInstance = new DeliveryConfiguration();
  }
  
  return sInstance;
}

