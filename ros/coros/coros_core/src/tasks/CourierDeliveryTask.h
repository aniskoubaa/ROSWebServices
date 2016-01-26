#ifndef COURIER_DELIVERY_TASK_H
#define COURIER_DELIVERY_TASK_H

#include "../../../robot_control/src/TurtlebotRobot.h"
#include "MoveToTask.h"

class CourierDeliveryTask : public MoveToTask
{
  
public:
  
  CourierDeliveryTask(int id, double coordX[], double coordY[], int destCount) : 
    MoveToTask(id, coordX, coordY, destCount)
  {
    if (myTargetsCount != 2)
    {	//TODO: should be handled as an exception
        ROS_ERROR("Courier Delivery Task should have exactly 2 targets.");
    }
      
  }
  
   
  void execute(Robot* robot)
  {
    ROS_INFO("Courier Delivery Task prepares to be executed on robot '%s' of type '%s'...", robot->getName().c_str(), robot->getType().c_str());
    string frame ="map";
    myTotalCost = 0.0;
    
    if (TurtlebotRobot* turtlebot = dynamic_cast<TurtlebotRobot*>(robot))
    {
      ROS_INFO("... executing task %d started...", myTaskID);
      
      //save the initial robot position
      // double initial_x = robot->getAmclX();
      // double initial_y = robot->getAmclY();
      
      moveTo(turtlebot, myCoordX[0], myCoordY[0], frame);
      // robot->makeBip();
      myPerformedTasks[0];
      #ifdef ROBOT_EXP
        myDetailedCosts[0] =  (double) getEuclidianDistance( robot->getAmclX(), robot->getAmclY(), myCoordX[0], myCoordY[0]);  
      #else
        myDetailedCosts[0] = 0;
      #endif
      myTotalCost += myDetailedCosts[0];
      
      ROS_INFO("... Please post the courier on the top of the robot, then press 'Enter'...");
      getchar();
      
      moveTo(turtlebot, myCoordX[1], myCoordY[1], frame);
      // robot->makeBip();
      myPerformedTasks[1];
      #ifdef ROBOT_EXP
        myDetailedCosts[1] =  (double) getEuclidianDistance( myCoordX[0], myCoordY[0], myCoordX[1], myCoordY[1]);  
      #else
        myDetailedCosts[1] = 0;
      #endif
      myTotalCost += myDetailedCosts[1];
      ROS_INFO("... executing task %d ended.", myTaskID);   
      // restore the initial position
      //   moveTo(turtlebot, initial_x, initial_y, frame);
    }
    else
    {
      ROS_ERROR("Courier Delivery Task cannot perfomed on uknown type of Robot.");
    }
  }
  
};

#endif // COURIER_DELIVERY_TASK_H