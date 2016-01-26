#ifndef I_MESSAGE_PROCESSOR_H
#define I_MESSAGE_PROCESSOR_H

#include "coros_messages/BaseMessage.h"

/**
 * IMessageProcessor is an interface for classes that need to process messages. Usualy,
 * this interface is implemeted in the case of the client classes when they receive a 
 * forwarded message from the server.
 */
class IMessageProcessor
{
  
public:
  
  virtual ~IMessageProcessor() {};

protected:
  
  // processing a message will usualy resutling in handling an related action.
  // handling an action will usualy resulting in sending a new message.
  // So, this method returns the serialization of the new message.
  virtual std::string process(BaseMessage*) = 0;
  
};

#endif // I_MESSAGE_PROCESSOR_H
