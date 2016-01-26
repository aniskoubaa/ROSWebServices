#ifndef DISPATCHER_CONFIGURATION_H
#define DISPATCHER_CONFIGURATION_H

#include <vector>
#include <string>
#include "coros_kb/AgentConfiguration.h"

class DispatcherConfiguration : public AgentConfiguration
{

public:
  
  static DispatcherConfiguration* getInstance ();
  
  void setTopics(std::vector<std::string> topics);

  std::vector<std::string> getTopics() { return myTopics; }

protected:

  DispatcherConfiguration(int runningMode = SIMULATION_RUN_MODE);

private:
  
  static DispatcherConfiguration* sInstance;

  std::vector<std::string> myTopics;
  
};

#endif // DISPATCHER_CONFIGURATION_H
