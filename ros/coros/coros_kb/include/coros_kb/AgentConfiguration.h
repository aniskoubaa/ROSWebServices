#ifndef AGENT_CONFIGURATION_H
#define AGENT_CONFIGURATION_H

#include "AgentState.h"

/**
 * The class AgentConfiguration is a singleton since we should have only one instance 
 * of configuration in a specific robot/machine. Configuration can be read from a file, 
 * a database, or a distant source (server). In this version the class AgentConfiguration
 * provides only accessors to its data members.
 * We qualify this class to manage the state of the current agent (robot or machine).
 * The LocalConfiguration or any other type of configuration should modified only by the operators of the local agent.
 */

class AgentConfiguration
{

public:
  
  /* returns the single instance of this class */
  static AgentConfiguration* getInstance ();
  
  /* Agent related configuration */
  void setAgentId(int id)       	     { myAgentState->setId(id);         	}

  void setAgentPort(int port)            { myAgentState->setPort(port);     	}

  void setAgentTimestamp(int ts)         { myAgentState->setTimestamp(ts);  	}

  void setAgentRole(std::string role)    { myAgentState->setRole(role);     	}

  void setAgentStatus(std::string status){ myAgentState->setStatus(status);     }

  void setAgentAddress(std::string ip)   { myAgentState->setIpAddress(ip);      }

  void setAgentName(std::string name)  	 { myAgentState->setName(name);      } //added by Anis

  int getAgentId()            			 { return myAgentState->getId();        }

  int getAgentPort()         			 { return myAgentState->getPort();      }

  int getAgentTimestamp()    			 { return myAgentState->getTimestamp(); }

  std::string getAgentRole()  			 { return myAgentState->getRole();      }

  std::string getAgentStatus() 			 { return myAgentState->getStatus();    }

  std::string getAgentAddress()			 { return myAgentState->getIpAddress(); }

  std::string getAgentName()			 { return myAgentState->getName(); } //added by Anis


  /* Running related configuration */
  void setRunningMode(int mode)          { myRunningMode = mode;       			}

  void setInitSimulationPort(int port)   { myInitSimulationPort = port; 		}

  int getAgentRunningMode()    			 { return myRunningMode;                }

  int getInitSimulationPort()  			 { return myInitSimulationPort;         }

  void setAvailableAgentStatus()		 { setAgentStatus(AgentState::AVAILABLE_STATUS);  }

  void setUnavailableAgentStatus()		 { setAgentStatus(AgentState::UNAVAILABLE_STATUS);}

  bool isAvailableAgent()				 { return (getAgentStatus()==AgentState::AVAILABLE_STATUS); }

  bool isUnavailableAgent()				 { return (getAgentStatus()==AgentState::UNAVAILABLE_STATUS); }


  void setWaitingTime(int s)			 { myWaitingTime = s; 					}

  int getWaitingTime()					 { return myWaitingTime; 				}

  void setMaxAgentNumber(int n)			 { myMaxAgentNumber = n; 				}

  int getMaxAgentNumber()				 { return myMaxAgentNumber;				}


  static const int SIMULATION_RUN_MODE = 0;

  static const int EXPERIMENTAL_RUN_MODE = 1;


protected:
  
  AgentConfiguration(int runningMode = SIMULATION_RUN_MODE);
  
private:
  
  static AgentConfiguration* sInstance;
   
  AgentState* myAgentState; 
  
  int myRunningMode; /* 0=simulation or 1=experimental*/

  int myInitSimulationPort;

  int myWaitingTime; // In seconds, time to wait for each agent to answer

  int myMaxAgentNumber; // The number of maximum agent supported for the app can be used alternatively to the waiting time

};

#endif // LOCAL_CONFIGURATION_H
