#ifndef I_TASK_PERFORMER_H
#define I_TASK_PERFORMER_H

#include "coros_tasks/BaseTask.h"

/**
 * ITaskPerformer is an interface for classes that need to perform/execute tasks on robot.
 */
class ITaskPerformer
{

public:
  
  virtual ~ITaskPerformer() {};
  
  virtual void perform(BaseTask*) = 0;
  
};

#endif // I_TASK_PERFORMER_H
