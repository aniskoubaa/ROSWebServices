#ifndef BASE_TASK_H
#define BASE_TASK_H

/**
 * BaseTask is the parent for classes that encapsulate a task execution. Such classes
 * execute an algorithm (task) according to the data that they enclose, and save the 
 * resulting data in the data memebers accessible through getters.
 */

class BaseTask
{

public:

  BaseTask(int id) : myTaskID (id){successed=false;}
  
  virtual void execute(Robot*) = 0;
  
  bool isSuccessed() { return successed;}
  
  //unsigned short getRobotId() { return myRobotId; }
  
  double getTotalCost() { return myTotalCost; }
  
  int* getPerfomedTasks() { return myPerformedTasks; }
  
  double* getDetailedCosts() { return myDetailedCosts; }
  
protected:
  
  int myTaskID;
    
  //The following are the same data members of ResultMessage 
  //We declare this data members to avoid to make this class aggregates, associates, or depends on ResultMessage
  
  bool successed;
  
  //unsigned short myRobotId; // this is not yet needed at this stage
  
  double myTotalCost;
  
  int *myPerformedTasks;
  
  double* myDetailedCosts;
  
};

#endif // BASE_TASK_H
