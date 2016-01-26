#include "Map.h"

class WeightedGraphMap : public Map {
 
public:
  
 //default constructor to initialize map
  WeightedGraphMap(int w=0, int h=0, float res=0.0);
  //four-argument constructor to initialize map
  WeightedGraphMap(int w, int h, float res, vector <int> mapVector);
  //constructor that loads a map from a file
  WeightedGraphMap(ofstream mpgMapFile); 
  //Copy constructor for the OccupancyGridMapGridMap
  WeightedGraphMap (OccupancyGridMapGridMap & map);
  
  //setEdgeCost with input parameter index in the map vector
  void setEdgeCost (vector<int>::iterator it);  
  //setEdgeCost input parameter with index (i,j) in the matrix map
  void setEdgeCost (int row, int col);
  
  //Check whether two points are connected
  bool isConnected (int WayPoint1, int WayPoint2 );  
};
