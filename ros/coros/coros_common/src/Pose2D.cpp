#include "coros_common/Pose2D.h"

#include <iostream>
#include <iomanip>
//#include <string>

using namespace std;

//Default Constructor
Pose2D::Pose2D (POSE Xr, POSE Yr, POSE Angle){
  setX(Xr);
  setY(Yr);
  setYaw(Angle);
}

//Get X Coordinate
POSE Pose2D::getX() const{
	return x;
}

//Get Y Coordinate
POSE Pose2D::getY()const {
	return y;
}

//Get Orientation
POSE Pose2D::getYaw()const {
	return yaw;
}


//Set X Coordinate
void Pose2D::setX(POSE Xr){
	x=Xr;
}


//Set Y Coordinate
void Pose2D::setY(POSE Yr){
	y=Yr;
}

//Set Orientation
void Pose2D::setYaw(POSE Angle){
	yaw=Angle;
}

std::ostream& operator<<(std::ostream &strm, const Pose2D &pose) {

  return strm << std::fixed << "[x: "<< std::setprecision(3) <<pose.getX()<<", y: "<< std::setprecision(3)<<pose.getY()<< ", yaw: "<< std::setprecision(3)<<pose.getYaw()<<" rad = "<< std::setprecision(1)<<radian2degree(pose.getYaw())<<" deg]";
}
