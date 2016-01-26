#include <stdio.h>
#include <cstdio>
#include <cstdlib>
#include<iostream>
#include <fstream>
#include <stdlib.h>
#include <time.h>       /* time */
#include <random>

#include "path_planner/OccupancyGridMap.h"
    
    
using namespace std;

std::default_random_engine generator;

int chooseRandomCell(OccupancyGridMap * m, int max_value){
  long cellID=-1;
  int i = 0;
  int j = 0;
  
  do{ 
     cellID = (rand() % max_value);
     cout<<"cellID= "<<cellID<<endl;
     i=m->getCellRowID(cellID);
     j=m->getCellColID(cellID);
     //cout<<"(i,j)= "<<"("<<i<<","<<j<<")"<<endl;
  }while (m->getMapLayout()[i][j]==100);
  //cout<<"(i,j)= "<<"("<<i<<","<<j<<")"<<endl;
  return cellID;
}

int DrawSquare(OccupancyGridMap * m, int cellID, int width, int height){
  
  for (int i=m->getCellRowID(cellID)-width/2; i<=m->getCellRowID(cellID)+width/2;i++)
    for (int j=m->getCellColID(cellID)-height/2; j<=m->getCellColID(cellID)+height/2;j++){
      if ((i< m->getWidth())&&(i>=0)&&(j< m->getHeight())&&(j>=0)){
	m->getMapLayout()[i][j]=100;
      //cout<<"(i,j)= "<<"("<<i<<","<<j<<")"<<endl;
      }
    }
  
  
  
}

int AssignObstacles(OccupancyGridMap * m, int cellID, double dimension){
  
  
  std::normal_distribution<double> distribution(dimension,dimension/2.0);
  double width = distribution(generator);
  double height = distribution(generator);
  cout<<"width: "<<(int) width<<endl;
  cout<<"length: "<<(int) height<<endl;
  
  DrawSquare(m, cellID, (int) width, (int)height);
  
  return (int) (width*height);
  
  
}




    
int main(){    
  
  int width=1000;
  int height=1000;
  int numberOfObstacleCells=1;
  int AverageObstacleSize=100;
  float ObstacleRatio=0.3;
  
  string filePath;
  const char* file1 = "GridMap";
  const char* file2 = "exportAnisMap.pgm";
  int randomCell =0;
  

  OccupancyGridMap* map;
  map = new OccupancyGridMap(width,height,1);
  
  cout <<"*****************import the map from a file******************"<< endl;
  map->importMapLayout(filePath, file1);
  for (int i=0;i<map->getHeight(); i++)
  {
    for(int j=0; j<map->getWidth(); j++)
    {
      map->getMapLayout()[i][j]=0;
    //cout << map->getMapLayout()[i][j] << "\t";
    }
  cout << endl;
  }
    while (((double)numberOfObstacleCells)/((double)(width*height))<ObstacleRatio){
     cout<<"*********chooseRandomCell**********"<<endl;
     randomCell = chooseRandomCell(map, (width*height));
     cout<<"chooseRandomCell: "<<randomCell<<endl;
   cout<<"*********AssignObstacles**********"<<endl;
   
     int newObstacleNumber=AssignObstacles(map, randomCell, AverageObstacleSize);
      numberOfObstacleCells=numberOfObstacleCells+newObstacleNumber;
      cout<<"AssignObstacles: "<<newObstacleNumber<<endl;
      cout<<"numberOfObstacleCells: "<<numberOfObstacleCells<<endl;
      cout<<"((double)numberOfObstacleCells)/((double)(width*height)): "<<((double)numberOfObstacleCells)/((double)(width*height))<<endl;
      cout<<"(((double)(width*height)): "<<(((double)(width*height)))<<endl;
      
    }
   
    
    for (int i=0;i<map->getHeight(); i++)
  {
    for(int j=0; j<map->getWidth(); j++)
    {
      //map->getMapLayout()[i][j]=0;
    //cout << map->getMapLayout()[i][j] << "\t";
    }
  //cout << endl;
  }
   
   map->exportMapLayout(filePath, file2, map->getMapLayout());
   
  
    /*
    while ((double)(width*height)/(double)numberOfObstacleCells)<ObstacleRatio){
    
      chooseRandomCell((width*height));
      AssignObstacles(AverageObstacleSize);
          
    }*/
    
}
