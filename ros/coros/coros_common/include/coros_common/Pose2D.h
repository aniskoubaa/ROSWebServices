

#ifndef POSE2D_H
#define POSE2D_H

#include "nav_lib.h"

class Pose2D {
public:
  Pose2D (POSE = 0,  POSE = 0, POSE = 0);
  
  //overloading << operator (similar to toString in Java)
  friend std::ostream& operator<<(std::ostream&, const Pose2D&);
  
  POSE getX() const;
  POSE getY() const;
  POSE getYaw() const;
  
  void setX(POSE);
  void setY(POSE);
  void setYaw(POSE );

private:
   POSE x;
   POSE y;
   POSE yaw;

};



#endif
