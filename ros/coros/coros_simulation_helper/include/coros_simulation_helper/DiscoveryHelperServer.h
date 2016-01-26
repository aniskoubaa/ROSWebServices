#ifndef SIMULATION_SERVER_H
#define SIMULATION_SERVER_H

#include "coros_communication/NodeServer.h"

class DiscoveryHelperServer : public NodeServer
{

public:
  
	DiscoveryHelperServer (const std::string& nodeName, int portNumber);

private:
  
  void init();

  void forward(const std::string& message, const std::string& fromIP);

};

#endif // SIMULATION_SERVER_H
