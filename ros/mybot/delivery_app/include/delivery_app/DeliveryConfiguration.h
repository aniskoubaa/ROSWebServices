#ifndef DELIVERY_CONFIGURATION_H
#define DELIVERY_CONFIGURATION_H

#include "coros_kb/AgentConfiguration.h"
#include "coros_common/Pose2D.h"

/**
 * The class DeliveryConfiguration is also a singleton as its superclass. In addition to the
 * parent data memebers, this class contains 2 addition data members related to the application:
 * the coordinates of the courier request.
 */

class DeliveryConfiguration : public AgentConfiguration
{

public:
  
  /* returns the single instance of this class */
  static DeliveryConfiguration* getInstance ();
    
  void setSourcePositionX(double x) { mySourcePositionX = x; }

  void setSourcePositionY(double y) { mySourcePositionY = y; }

  void setTargetPositionX(double x) { myTargetPositionX = x; }

  void setTargetPositionY(double y) { myTargetPositionY = y; }

  double getSourcePositionX() { return mySourcePositionX; }

  double getSourcePositionY() { return mySourcePositionY; }

  double getTargetPositionX() { return myTargetPositionX; }

  double getTargetPositionY() { return myTargetPositionY; }
  
protected:
  
  DeliveryConfiguration(int runningMode = SIMULATION_RUN_MODE);
 
private:

  static DeliveryConfiguration* sInstance;
  
  double mySourcePositionX;

  double mySourcePositionY;  

  double myTargetPositionX;

  double myTargetPositionY;
  
};

#endif //DELIVERY_CONFIGURATION_H
