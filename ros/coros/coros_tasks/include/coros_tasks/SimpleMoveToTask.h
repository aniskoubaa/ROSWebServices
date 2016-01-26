#ifndef SIMPLE_MOVE_TO_TASK_H
#define SIMPLE_MOVE_TO_TASK_H

#include "BaseTask.h"
#include <ros/ros.h>
#include <coros_common/nav_lib.h>

class SimpleMoveToTask : public BaseTask
{
  
public:
	SimpleMoveToTask(int id, int mode, double coordX, double coordY) :
		BaseTask(id), myTargetX(coordX), myTargetY(coordY), myMode(mode), myCost(0)
        {
        }
  
	void execute(Robot* robot)
	{
                static bool firstCall = true;
		
                ROS_INFO("Simple MoveTo Task prepares to be executed on robot '%s' of type '%s'...", robot->getName().c_str(), robot->getType().c_str());
		std::string frame ="map"; //TODO: send it in param

   		if (TurtlebotRobot* turtlebot = dynamic_cast<TurtlebotRobot*>(robot))
		{
                        if (myMode==1 && firstCall)
			{
				myInitialPositionX = turtlebot->getAmclX();
			        myInitialPositionY = turtlebot->getAmclY();
			        firstCall = false;
			} 

			moveTo(turtlebot, myTargetX, myTargetY, frame);
			ROS_INFO("... executing task %d ended.", myTaskID);
		}
		else
		{
			ROS_ERROR("Simple MoveTo Task cannot be performed on unknown type of Robot.");
		}
        successed = true;
  }

  double setTargetX(double x){ myTargetX = x; }

  double setTargetY(double y){ myTargetY = y; }

  double getCost() { return myCost; }
  
  double getInitialPositionX() { return myInitialPositionX; }

  double getInitialPositionY() { return myInitialPositionY; }

protected:
  
  double myInitialPositionX;
  
  double myInitialPositionY;

  double myTargetX;
  
  double myTargetY;
  
  int myMode;

  double myCost;

  
  void moveTo(TurtlebotRobot* robot, double x, double y, std::string frame)
  {
    ROS_INFO("... Robot moves to target (%f,%f)...", x, y);
    if (myMode==1)
    {
        myCost +=  (double) getEuclidianDistance( robot->getAmclX(), robot->getAmclY(), x, y);  
  
    	robot->moveGoal(x, y, frame);
    }
    else
    {
    	//TODO: here do the simulation of moving
    }
    ROS_INFO("... Robot reached the target (%f,%f)...", x, y);
    ROS_INFO("... Robot current location is (%f,%f)...", robot->getAmclX(), robot->getAmclY());
  }
  
};

#endif // SIMPLE_MOVE_TO_TASK_H
