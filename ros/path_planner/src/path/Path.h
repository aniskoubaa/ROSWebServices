#include <iostream>
#include <fstream>
#include <vector>
#include <string>

#include "../../../path_planner/src/map/OccupancyGridMap.h"
using namespace std;

class Path {
 
public:
  
  //default constructor to initialize path
  Path(void);
  Path(string pname);
  //Copy constructor for the map
 // Path (Path & path);
  Path (vector<int> p);
  Path (vector<int> p, string pname);
  //Define Mutators
  void setPath(vector<int> p);
  void setName(string pname);
  void setCost(float c);
  
  //Define Accessors
  vector<int> getPath();
  string getName();
  float getCost();
  
  //Insert cell
  void insertCell (OccupancyGridMap* map,  int index, int cell);
  //remove cell
  void removeCell (OccupancyGridMap* map, int index);
  //exchange 2 cells
  void setCell (OccupancyGridMap* map,int cell, int index); 
  //get the cost of the path
  float getPathCost(OccupancyGridMap* map, bool isRecalculate);
  // calculate distance between two cell in a path
  float calculateDistance(OccupancyGridMap* OGM, int startIndex, int goalIndex);

  //verify if the path is feasible
  bool isFeasible(OccupancyGridMap* map);
  void printPath();
  bool isValidCost(OccupancyGridMap* map);
  void exportPath(OccupancyGridMap* map, const char* file_name);
 
  
private:
  vector<int> path;//the path data structure 
  float cost;
  string name;
};

