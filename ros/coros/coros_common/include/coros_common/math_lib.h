
using namespace std;
#ifndef PI
#define PI 3.14159265359
#endif
/* makes conversion from radian to degree */
double radian2degree(double radianAngle){
  return (radianAngle*57.2957795);
}


/* makes conversion from degree to radian */
double degree2radian(double degreeAngle){
  return (degreeAngle/57.2957795);
}

/* check whether an angle is a valid radian angle between -PI/2 and PI/2*/
bool isRadianAngle (double angle){
  return ((angle < (PI/2))||(angle>(-PI/2))); 
  //return true;
}

/* check whether an angle is a valid degree angle between -180 and 180*/
bool isDegreeAngle (double angle){
  return ((angle < (180))||(angle>-180));
  //return false; 
}

/*return true is the angle is positive meaning that clockwise direction*/
bool isClockwise (double angle){
  return (angle>0); 
  //return true;
}


bool isRangesEqual (double f1, double f2){
  // if we increase the epsilon the total number of equal one decreases
  const double epsilon = 1e-2 /* some small number such as 1e-5 */;
  return std::abs(f1 - f2) <= epsilon * std::abs(f1);

  //return true;
}

