#include "coros_kb/NeighborsConfiguration.h"
#include <iostream>
#include <iomanip>
using namespace std;


NeighborsConfiguration* NeighborsConfiguration::sInstance = NULL;


NeighborsConfiguration::NeighborsConfiguration()
{

}
 
  
NeighborsConfiguration* NeighborsConfiguration::getInstance()
{
  if (sInstance == NULL)
  {
    sInstance = new NeighborsConfiguration();
  }
  
  return sInstance;
}

int NeighborsConfiguration::findNeighbor(int agentId)
{
  int size = myNeighbors.size();
  for (int i=0; i<size; i++)
    if (myNeighbors[i]->getId() == agentId)
      return i;
   return -1;
}

AgentState* NeighborsConfiguration::getNeighbor(int agentId)
{
	int index = findNeighbor(agentId);
	return (0 <= index && index < myNeighbors.size()) ? myNeighbors[index] : NULL;
}

AgentState* NeighborsConfiguration::findNeighborByRole(std::string role)
{
  int size = myNeighbors.size();
  for (int i=0; i<size; i++)
    if (myNeighbors[i]->getRole() == role)
      return myNeighbors[i];
   return NULL;
}


bool NeighborsConfiguration::addNeighbor(AgentState* n)
{
  int agentIndex = findNeighbor(n->getId());
  if (agentIndex != -1) // if the agent exists, delete it
  {
	  myNeighbors.erase(myNeighbors.begin() + agentIndex);
  }
  myNeighbors.push_back(n);
  return true;
}

void NeighborsConfiguration::printNeighbors(){
  cout<<"\nNeighborhood Table"<<endl;
  cout<<"|------------------------------------------------------------------------------|"<<endl;
  cout<<"|ID  |IP Address      |Port    |Timestamp      |Role           |Status         |"<<endl;
  cout<<"|------------------------------------------------------------------------------|"<<endl;
  int size = myNeighbors.size();
  for (unsigned i=0; i<size; i++){
      cout<<"|"<<left<<setw(4) <<myNeighbors.at(i)->getId();
      cout<<"|"<<left<<setw(16)<<myNeighbors.at(i)->getIpAddress();
      cout<<"|"<<left<<setw(8) <<myNeighbors.at(i)->getPort();
      cout<<"|"<<left<<setw(15)<<myNeighbors.at(i)->getTimestamp();
      cout<<"|"<<left<<setw(15)<<myNeighbors.at(i)->getRole();
      cout<<"|"<<left<<setw(15)<<myNeighbors.at(i)->getStatus()<<"|"<<endl;
    }
  cout<<"|------------------------------------------------------------------------------|"<<endl;
}

/*
bool NeighborsConfiguration::getNeighborsAddresses(std::string* ip_addresses, int* ports, int& size)
{
	if (! (size = myNeighbors.size()) )
		return false;

	ip_addresses = new std::string[size];
	ports 		 = new int[size];

	for (int i=0; i<size; i++)
	{
		ip_addresses[i] = myNeighbors.at(i)->getIpAddress();
	    ports[i] 	 	= myNeighbors.at(i)->getPort();
	}

	return true;
}
*/
/*
bool NeighborsConfiguration::getNeighborsAddresses(std::string* ip_addresses, int* ports)
{
	int size = myNeighbors.size();

	for (int i=0; i<size; i++)
	{
		ip_addresses[i] = myNeighbors.at(i)->getIpAddress();
	    ports[i] 	 	= myNeighbors.at(i)->getPort();
	}

	return true;
}
*/
