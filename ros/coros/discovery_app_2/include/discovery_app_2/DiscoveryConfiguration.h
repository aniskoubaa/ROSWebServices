#ifndef DISCOVERY_CONFIGURATION_H
#define DISCOVERY_CONFIGURATION_H

#include "coros_kb/AgentConfiguration.h"

class DiscoveryConfiguration : public AgentConfiguration
{

public:
  
  static DiscoveryConfiguration* getInstance ();
  
  void setBroadcastFrequency(double freq) { myBroadcastFrequency = freq; }
  
  double getBroadcastFrequency() { return myBroadcastFrequency; }

protected:

  DiscoveryConfiguration(int frequency = 3, int runningMode = SIMULATION_RUN_MODE);

private:
  
  static DiscoveryConfiguration* sInstance;

  double myBroadcastFrequency; // in seconds
  
};

#endif // DISCOVERY_CONFIGURATION_H
