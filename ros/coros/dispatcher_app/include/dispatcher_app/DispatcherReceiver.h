#ifndef DISPATCHER_RECEIVER_H
#define DISPATCHER_RECEIVER_H

#include "coros_communication/NodeServer.h"
#include "dispatcher_app/DispatcherConfiguration.h"

class DispatcherReceiver : public NodeServer
{

public:
  
  DispatcherReceiver (const std::string& nodeName, int portNumber);

private:
  
  void init();

  void forward(const std::string& message, const std::string& fromIP);
   
private:

  DispatcherConfiguration* myLocalConfig;

};

#endif // DISPATCHER_RECEIVER_H
