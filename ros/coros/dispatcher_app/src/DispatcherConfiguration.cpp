#include "dispatcher_app/DispatcherConfiguration.h"

DispatcherConfiguration* DispatcherConfiguration::sInstance = NULL;

DispatcherConfiguration::DispatcherConfiguration(int runningMode) :
  	  AgentConfiguration(runningMode) {}

  
DispatcherConfiguration* DispatcherConfiguration::getInstance()
{
  if (sInstance == NULL)
  {
    sInstance = new DispatcherConfiguration();
  }
  
  return sInstance;
}

void DispatcherConfiguration::setTopics(std::vector<std::string> topics)
{
    int size = topics.size();

    for (int i=0; i<size; i++)
       myTopics.push_back( topics[i] );
}
