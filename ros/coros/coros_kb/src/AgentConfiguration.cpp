#include "coros_kb/AgentConfiguration.h"


const int AgentConfiguration::SIMULATION_RUN_MODE;

const int AgentConfiguration::EXPERIMENTAL_RUN_MODE;

AgentConfiguration* AgentConfiguration::sInstance = NULL;


AgentConfiguration::AgentConfiguration(int runningMode) : myRunningMode(runningMode)
{
	myAgentState = new AgentState();
}


AgentConfiguration* AgentConfiguration::getInstance()
{
  if (sInstance == NULL)
  {
    sInstance = new AgentConfiguration();
  }
  
  return sInstance;
}
