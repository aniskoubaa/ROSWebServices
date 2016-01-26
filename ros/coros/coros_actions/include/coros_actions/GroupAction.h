#ifndef GROUP_ACTION_H
#define GROUP_ACTION_H

#include "BaseAction.h"

class GroupAction : public BaseAction
{
  
public:
  
  GroupAction(int id, int size) : BaseAction(id), finished(false)
  {
    initCounter();
    setFalgsNumber(size);
    initFlags();
    setFlags();
  }
  
  
  virtual void initCounter() { int* counter = getCounter(); (*counter) = 0; }
  
  virtual void incrementCounter() { 
    int* counter = getCounter(); 
    int* number = getFlagsNumber();
    if (counter && number && ++(*counter) == (*number))
      finished = true; 
    
  }
  
  virtual void initFlagsNumber() { int* number = getFlagsNumber(); (*number) = 0; }
 
  virtual void setFalgsNumber(int size) { 
    int* number = getFlagsNumber(); 
    if (number && (*number) != size)
      (*number) = size; 
    
  }
  
  virtual void initFlags() {int* flags = getFlags(); if (flags != NULL) delete[] flags;}
  
  virtual void setFlags() {
    int* flags = getFlags();  
    int* number = getFlagsNumber(); 
    if (flags == NULL && (*number) != 0) 
      flags = new int[*number];
    for (int i=0; i <(*number); i++)
      flags[i] = 0;
  }
  
  virtual void setFlag(int position){ int* flags = getFlags(); flags[position] = 1; }
  
  bool isFinished(){ return finished; }

  void setFinished(){ finished = true; }

  void unsetFinished(){ finished = false; }
  
protected:
  
  bool finished;
  
  // the following are a simple static data members. Accessing them through a static member function
  // is the only existing way to declare and define them in a header (.h) file.
  // So, in our case these functions should redefined for each subclass to have a specific static data
  // memebers for each of them. In fact they are not virtual, 
  // which is impossible (to have a static virtual function), but when redefined they will hide the 
  // parent function.
  static int* getCounter() { static int myCounter = 0; return &myCounter; }
  
  static int* getFlagsNumber() {  static int myFalgsNumber = 0; return &myFalgsNumber; }
  
  static int* getFlags() {  static int * myFlags = NULL; return myFlags; }
  
};

#endif // GROUP_ACTION_H
