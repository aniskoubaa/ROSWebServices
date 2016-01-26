#ifndef COMPUTE_MINIMAL_COST_ACTION_H
#define COMPUTE_MINIMAL_COST_ACTION_H

#include "SingleAction.h"

#include <vector>
#include "coros_common/nav_lib.h"

class ComputeMinimalCostAction : public SingleAction
{
  
public:

	ComputeMinimalCostAction(unsigned short id, double current_x, double current_y, std::vector<double> coords, std::vector<bool> availability) : SingleAction(id)
    {
		myCurrentX = current_x;
		myCurrentY = current_y;
		myCoords   = coords;
		myAvailability = availability;

		myComputedCosts.reserve(myCoords.size());
    }

	void execute()
	{
		myMinimalCostId = -1;
	    myMinimalCostValue = -1;

	    // find the first available target and consider its cost as minimal
		int size = myCoords.size();
		int i;

		for(i=0; i<size; i+=2)
		{
				if (myAvailability[i/2]==true)
					break;
				myComputedCosts[i/2] = -1;
		}

		if (i<size)
		{
			myMinimalCostId    = (i/2) + 1;
			myMinimalCostValue = static_cast<double>(getEuclidianDistance( myCurrentX, myCurrentY, myCoords[i], myCoords[i+1]));
			//cout<<"myMinimalCostId="<<myMinimalCostId<<", myMinimalCostValue="<<myMinimalCostValue<<endl;
			myComputedCosts[i/2] = myMinimalCostValue;
		}

    	// find the minimal value
    	for(i+=2; i<size; i+=2)
    	{
    		if (myAvailability[i/2]==false)
    		{
    			myComputedCosts[i/2] = -1;
    			continue;
    		}
    		myComputedCosts[i/2] = (double) getEuclidianDistance( myCurrentX, myCurrentY, myCoords[i], myCoords[i+1]);

    		if (myMinimalCostValue > myComputedCosts[i/2])
    		{
    			myMinimalCostId = (i/2) + 1;
				myMinimalCostValue = myComputedCosts[i/2];
    		}
    	}
	}

    int getMinimalCostId()	  {	return myMinimalCostId;    }

    double getMinimalCostValue() {	return myMinimalCostValue; }

    std::vector<double> getComputedCosts() { return myComputedCosts; }

    void printResults()
    {
    	cout << "\nTargets Computed Costs:"<<endl;
    	cout << " - Current position  : ("<< myCurrentX << "," << myCurrentY << ")" << endl;
    	cout << " - Minimal target ID : "<< myMinimalCostId << endl;
     	cout << " - Minimal cost value: "<< myMinimalCostValue << endl;
    	int size = myCoords.size();
		cout << "|-------------------------------------------------|" << endl;
		cout << "|Target ID  |Coordinates  |Available  |Cost       |" << endl;
		cout << "|-------------------------------------------------|" << endl;

		for(unsigned i=0; i < size; i+=2)
		{
			cout << "|" << left << setw(11) << itos(i/2+1);
			cout << "|" << left << setw(13) <<("(" + mtos(myCoords[i]) + "," + mtos(myCoords[i+1]) + ")");
			cout << "|" << left << setw(11) << (myAvailability[i/2] ? "Yes" : "No");
			cout << "|" << left << setw(11) << myComputedCosts[i/2] << "|" << endl;
		}
		cout << "|-------------------------------------------------|" << endl;
    }

private:

    //provided data
	double myCurrentX;

	double myCurrentY;

	std::vector<double> myCoords;

	std::vector<bool> myAvailability;   // contains the last computed costs.

	//computed data
	int myMinimalCostId;

	double myMinimalCostValue;

	std::vector<double> myComputedCosts;  // contains the last computed costs.

};

#endif // COMPUTE_MINIMAL_COST_ACTION_H
