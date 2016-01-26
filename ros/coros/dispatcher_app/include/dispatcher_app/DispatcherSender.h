#ifndef DISPATCHER_SENDER_H
#define DISPATCHER_SENDER_H

#include <string>
#include <coros_messages/CorosHeader.h> 
#include <coros_messages/OutBoxMsg.h> 

#include "coros_operator/SimpleOperator.h"

#include "dispatcher_app/DispatcherConfiguration.h"

class DispatcherSender : public SimpleOperator
{
  
public:
  
  DispatcherSender(const std::string& nodeName);

  void outboxCallback(const coros_messages::OutBoxMsg::ConstPtr& msg);

protected:
  
  //init callbacks
  void init(); 

  std::string process(BaseMessage*){ return "";}

private:

  DispatcherConfiguration* myLocalConfig;

};

#endif // DISPATCHER_SENDER_H
