#include "discovery_app_2/DiscoveryConfiguration.h"

DiscoveryConfiguration* DiscoveryConfiguration::sInstance = NULL;

DiscoveryConfiguration::DiscoveryConfiguration(int frequency, int runningMode) :
  	  AgentConfiguration(runningMode), myBroadcastFrequency(frequency) {}

  
DiscoveryConfiguration* DiscoveryConfiguration::getInstance()
{
  if (sInstance == NULL)
  {
    sInstance = new DiscoveryConfiguration();
  }
  
  return sInstance;
}
