#ifndef COMPUTE_COST_ACTION_H
#define COMPUTE_COST_ACTION_H

#include "SingleAction.h"

#include "coros_common/nav_lib.h"

class ComputeCostAction : public SingleAction
{
  
public:
	enum ComputationType
	{
	   	EUCLIDIAN_DISTANCE
		// TODO: add more
	};

	ComputeCostAction(unsigned short id, ComputationType type, double current_x, double current_y, double target_x, double target_y) : SingleAction(id)
    {
		myDistanceComputationType = type;
		myCurrentX = current_x;
		myCurrentY = current_y;
		myTargetX  = target_x ;
		myTargetY  = target_y ;
		myComputedCost = 0.0;
    }

	void execute()
	{
		switch (myDistanceComputationType)
		{
			case EUCLIDIAN_DISTANCE:
				myComputedCost = (double) getEuclidianDistance( myCurrentX, myCurrentY, myTargetX, myTargetY);
				break;
			default:;
		}
	}

    double getComputedCost()	  {	return myComputedCost;    }

private:

    //provided data
    ComputationType myDistanceComputationType;

	double myCurrentX;

	double myCurrentY;

	double myTargetX;

	double myTargetY;

	//computed data
	double myComputedCost;

};

#endif // COMPUTE_COST_ACTION_H
