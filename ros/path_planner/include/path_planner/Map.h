#include <iostream>
#include <fstream>
#include <vector>
#include <string.h>
using namespace std;

#ifndef MAP_H
#define MAP_H

class Map {
 
public:
  
  //default constructor to initialize map
  Map(int w=0, int h=0, float res=0.0);
  //four-argument constructor o initialize map
  Map(int w, int h, float res, int** mapMatrix, int obsSize=0, float obsRatio=0.0);
  //constructor that loads a map from a file
 // Map(ifstream mpgMapFile); 
  //Copy constructor for the map
  Map (Map* map);
  
     
  //Define Mutators
  void setWidth(int w);
  void setHeight(int h);
  void setResolution (float res);
  void setMapLayout(int** mapMatrix);
  void setObstacleSize (int obsSize);
  void setObstacleRatio(float obsRatio);  
  
  //Define Accessors
  int getWidth();
  int getHeight();
  float getResolution();
  int** getMapLayout();
  int getObstacleSize();
  float getObstacleRatio();
  
  int getCellIndex(int i,int j); //get the index of the cell to be used in Path
  int getCellRowID(int index);//get the row ID from cell index
  int getCellColID(int index);//get colunm ID from cell index  
  
  void importMapLayout(string path_name, const char* file_name); // read the MapLayout from a file
  void exportMapLayout(const char* file_name, int** mapMatrix); // write the MapLayout in a file
  
private:
  int width; // Map width [cells]
  int height;// Map height [cells]
  float resolution;//The map resolution [m/cell]
  int** mapLayout;//the map data structure that contains all cells of the environment
  int obstacleSize;
  float obstacleRatio;
};

#endif