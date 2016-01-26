#ifndef NEIGHBORHOOD_UPDATE_ACTION_H
#define NEIGHBORHOOD_UPDATE_ACTION_H

#include "SingleAction.h"

class NeighborhoodUpdateAction : public SingleAction
{
  
public:
  
  NeighborhoodUpdateAction(int id, std::list<unsigned short> ids, 
			            std::list<std::string> ips,
				    std::list<unsigned short> ports,
			            std::list<double> timestamp;) :
    GroupAction(id, size), myBidderId(bid), myBidderCost(cost) 
  {
    
    
  }
  
  void execute()
  {

  }
  
  
protected:

  
};

#endif // NEIGHBORHOOD_UPDATE_ACTION_H
