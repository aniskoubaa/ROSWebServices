#ifndef BASE_ACTION_H
#define BASE_ACTION_H

class BaseAction
{
  
public:
  
  BaseAction(unsigned short id) : myActionId (id) {}
    
  virtual void execute() = 0;
  
protected:
  
  unsigned short myActionId;
 
};

#endif // BASE_ACTION_H
