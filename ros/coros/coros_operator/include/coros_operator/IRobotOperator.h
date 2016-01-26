#ifndef IROBOT_OPERATOR_H
#define IROBOT_OPERATOR_H

#include "IAgentOperator.h"
#include "coros_processing/ITaskPerformer.h"


/**
 * IRobotOperator is an interface which is more specific than its super-
 * interface, IAgentOperator, and includes the usage of ITaskPerformer.
 * Usually, this interface should be realized by classes that are already
 * subclasses of the client robot class (RobotClient).
 */

class IRobotOperator: public IAgentOperator, public ITaskPerformer
{
  
public:
  
  ~IRobotOperator() {}
    
protected:

    
};

#endif // IROBOT_OPERATOR_H
