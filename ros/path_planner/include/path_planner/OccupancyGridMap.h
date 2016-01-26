#ifndef OCCUPANCY_GRID_MAP_H
#define OCCUPANCY_GRID_MAP_H

#include<limits.h>
#include "Map.h"

class OccupancyGridMap : public Map {
 
public:
  //define constants
  static const int FREE     = 0;  //for free cell
  static const int OBSTACLE = 100;//for obstacles
  static const int UNKNOWN  = -1; //for unknown cell
  
  static const float MOVE_COST = 1.0; //horizental or vertical move
  static const float DIAGONAL_MOVE_COST = 1.4; //Diagonal move
  
   static const float INFINIT_COST = INT_MAX; //cost of non connected nodes

  
  //default constructor to initialize map
  OccupancyGridMap(int w=0, int h=0, float res=0.0);
  //four-argument constructor to initialize map
  OccupancyGridMap(int w, int h, float res, int** mapMatrix, int obsSize, float obsRatio);
  //constructor that loads a map from a file
  OccupancyGridMap(ifstream mpgMapFile); 
  //Copy constructor for the OccupancyGridMapGridMap
  OccupancyGridMap (OccupancyGridMap* map);
  
  void setObstacle (int i, int j);
  void setFree (int i, int j);
  void setUnknown (int i, int j);
  void setCell (int i, int j, int occupancy); //give the cell(i,j) the value of occupancy 
  
  //float getMoveCost(int cellID1, int cellID2); //return the cost of the move between cell(i1,j1) and (i2,j2)
  float getMoveCost(int i1, int j1, int i2, int j2);
  bool isObstacle(int i, int j); //return true if the cell is an Obstacle
  bool isFree(int i, int j); //returns true if the cell is Free
  bool isUnknown(int i, int j); //returns true if the cell is Unknown
  
  float getMoveCost(int CellID1, int CellID2);
  bool isFree(int CellID); //returns true if the cell is Free
  bool isObstacle(int CellID); //return true if the cell is an Obstacle
  bool isUnknown(int CellID); //returns true if the cell is Unknown
  
  /*override the method defined in Map.h by adding ratio of obstacle*/
  void exportMapLayout(const char* file_name, int** mapMatrix); // write the MapLayout in a file
  
  /*override the method defined in Map.h by adding ratio of obstacle*/
  void printMapLayout(); // print the MapLayout in a file

  
};

#endif
