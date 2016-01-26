#ifndef RECEIVED_BIDDING_ACTION_H
#define RECEIVED_BIDDING_ACTION_H

#include "GroupAction.h"

class ReceivedBiddingAction : public GroupAction
{
  
public:
  
  ReceivedBiddingAction(int id, int size, int bid, double cost) :
    GroupAction(id, size), myBidderId(bid), myBidderCost(cost) 
  {
    init(size);
    incrementCounter();
    //setFlag(myBidderId-1);
    
  }
  
  void execute()
  {
    int* bestId = getBestBidderId(); 
    double* bestCost = getBestBidderCost();
    
    if ( myBidderCost < (*bestCost) )
    {
      (*bestId) = myBidderId;
      (*bestCost) = myBidderCost;      
    }
  }
  
  void init(int size){
    if (  !finished && ( (*getCounter()) != 0 ) )
      return;
    finished = false;
    initCounter();
    setFalgsNumber(size);
    initFlags();
    setFlags();
    initBestBiddingInfo();
  }
  
  void initBestBiddingInfo() {
    setBestBiddingInfo(0, 1.79769e+308);
  }
  
  void setBestBiddingInfo(int id, double cost) {
    int* bestId = getBestBidderId(); 
    double* bestCost = getBestBidderCost();
    if (bestId) (*bestId) = id;
    if (bestCost) (*bestCost) = cost;
  }
     
   static int* getBestBidderId() { static int myBestBidderId = 0; return &myBestBidderId; }

   static double* getBestBidderCost() {  static double myBestBidderCost = 1.79769e+308; return &myBestBidderCost; }

   static int* getCounter() { static int myCounter = 0; return &myCounter; }


   void initCounter() { int* counter = getCounter(); (*counter) = 0; }
  
   void incrementCounter() { 
    int* counter = getCounter(); 
    int* number = getFlagsNumber();

    if (++(*counter) == (*number))
      finished = true; 
    
  }
  
  void initFlagsNumber() { int* number = getFlagsNumber(); (*number) = 0; }
 
  void setFalgsNumber(int size) { 
    int* number = getFlagsNumber(); 
     (*number) = size; 
  }
  
  void initFlags() {int* flags = getFlags(); if (flags != NULL) delete[] flags;}
  
  void setFlags() {
    int* flags = getFlags();  
    int* number = getFlagsNumber(); 
    if (flags == NULL && (*number) != 0) 
      flags = new int[*number];
    for (int i=0; i <(*number); i++)
      flags[i] = 0;
  }
  
  void setFlag(int position){ int* flags = getFlags(); flags[position] = 1; }
  
protected:

  int myBidderId; 
  
  double myBidderCost;

  static int* getFlagsNumber() { static int myFalgsNumber = 0; return &myFalgsNumber; }
  
  static int* getFlags() { static int * myFlags = NULL; return myFlags; }
};

#endif // RECEIVED_BIDDING_ACTION_H
