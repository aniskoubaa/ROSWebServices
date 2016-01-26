#ifndef NEIGHBORS_CONFIGURATION_H
#define NEIGHBORS_CONFIGURATION_H

#include "AgentState.h"
#include <vector>
/**
 * The class NeighborsConfiguration (was: NeighborsStateManager) is a singleton since we should have only one instance
 * of this manager in a specific robot/machine. Initial state can be read from a file, 
 * a database, or a distant server. In this version the class NeighborsStateManager
 * provides only accessors to its data members.
 */

class NeighborsConfiguration
{

public:
  
  static NeighborsConfiguration* getInstance ();
  
  void setNeighbors(std::vector<AgentState*>& n) 
  { 
    myNeighbors = n;
  }
  
  int getNeighborsNumber() { return myNeighbors.size(); }

  std::vector<AgentState*> getNeighbors() { return myNeighbors; }
  
  // returns the agent index if exists, otherwise -1 is returned
  int findNeighbor(int agentId);
  
  // returns the object representing the neighbor state.
  AgentState* getNeighbor(int agentId);

  AgentState* findNeighborByRole(std::string role);
  
  bool addNeighbor(AgentState* n);
  
  void printNeighbors();

 // bool getNeighborsAddresses(std::string* ip_addresses, int* ports);

protected:
  
  NeighborsConfiguration();
  
private:

  static NeighborsConfiguration* sInstance;
  
  std::vector<AgentState*> myNeighbors;
    
};

#endif //NEIGHBORS_CONFIGURATION_H
