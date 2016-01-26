#ifndef I_ACTION_HANDLER_H
#define I_ACTION_HANDLER_H

#include "coros_actions/BaseAction.h"

/**
 * IActionHandler is an interface for classes that need to handle actions. Usualy,
 * this interface is implemented in the case of the client classes when they receive a
 * forwarded message from the server and need to handle an action accordingly.
 */

class IActionHandler
{
  
public:
  
  virtual ~IActionHandler() {};
  
protected:
  
  virtual void handle(BaseAction*) = 0;
  
};

#endif // I_ACTION_HANDLER_H
