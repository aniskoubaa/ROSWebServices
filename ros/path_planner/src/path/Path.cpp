#include "../../../path_planner/src/path/Path.h"

#include<vector>
#include <stdlib.h>

using namespace std;
ofstream file1 ("isValid.txt", ios::trunc) ;
//constructor
Path::Path(void)
{
  setCost(0);
  setName("Unnamed Path");
}
Path::Path(string pname)
{
 setCost(0);
  setName(pname);
}
Path::Path (vector<int> p)
{
  setCost(0); 
 setPath(p);
 setName("Unnamed Path");
}

Path::Path (vector<int> p, string pname)
{
 setCost(0); 
 setPath(p);
 setName(pname);
}


void Path::setPath(vector<int> p)
{
  for(uint i=0; i<p.size(); i++){
    path.push_back(p[i]);
  }
}

void Path::setName(string pname){
 name=pname;
}
void Path::setCost(float pCost){
  if (pCost>=0)
    cost=pCost;
  else 
  {
  //   cout << getName() << endl;
  //  cout<<"The cost is negative"<< getCost() << endl;
  }
}

vector<int> Path::getPath()
{
  return path;
}

string Path::getName(){
 return name;  
}
float Path::getCost(){
 return cost;  
}
//insert a cell in the path

void Path::insertCell (OccupancyGridMap* map,  int index, int cellID)
{
   path.insert(path.begin()+index, cellID);
   if (index==0) { //adding a cell in the head of the path. We have two cases:
     if (path.size()==1) // this is the first cell to be inserted in the path
       setCost(0.0); 
     
     else //adding a cell in the head of an existing path 
      setCost(getPathCost(map,false) + map->getMoveCost(cellID, path[1]));
   }
   else // if the index is not in the head
     if(index == path.size()-1) //inserting at the tail of the path
       setCost(getPathCost(map,false) + map->getMoveCost(path[index-1],cellID));
     else //inserting in the middle of the path
       setCost(getPathCost(map,false)-map->getMoveCost(path[index-1],path[index+1])
				      +map->getMoveCost(path[index-1],cellID)
				      +map->getMoveCost(cellID,path[index+1]));
}

//remove a cell from the path
 void Path::removeCell (OccupancyGridMap* map, int index)
{
  if (index==0)//remove a cell in the head of the path. We have two cases:
  {
     if((path.size()==1)||(path.size()==2)) //if only one or two cells remains in path
     setCost(0.0);
     else //if there are more than 2 cells in the path
        setCost(getPathCost(map,false)-map->getMoveCost(path[index],path[index+1]));
  }
  else // if index is not in the head
  {
    if(index==path.size()-1) //removing at the tail of the path
      setCost(getPathCost(map,false)- map->getMoveCost(path[index-1],path[index]));
    else //removing at the middle of the path
      setCost(getPathCost(map,false)-map->getMoveCost(path[index-1],path[index])
		      -map->getMoveCost(path[index],path[index+1])
		      +map->getMoveCost(path[index-1],path[index+1]));	 
  }
  path.erase(path.begin()+index);
}
//exchange the cell at index by "cell"
void Path::setCell (OccupancyGridMap* map,int cellID, int index)
{
  setCost(getPathCost(map,false)-map->getMoveCost(path[index-1],path[index])
           -map->getMoveCost(path[index],path[index+1])
	   +map->getMoveCost(path[index-1],cellID)
	   +map->getMoveCost(cellID,path[index+1]));
  path[index]= cellID;	
}

float Path::getPathCost(OccupancyGridMap* map, bool isRecalculate)
{
  if (isFeasible(map)){
    float pathCost=0.0;
    if (isRecalculate)
      for (uint k=0; k<getPath().size()-1; k++)
	pathCost = pathCost + map->getMoveCost(map->getCellRowID(getPath()[k]), map->getCellColID(getPath()[k]), map->getCellRowID(getPath()[k+1]), map->getCellColID(getPath()[k+1]));
     else
       pathCost = getCost();
      return pathCost;
  }
  else  return -1.0;}

// calculate distance between two cell in a path
float Path::calculateDistance(OccupancyGridMap* OGM, int startIndex, int goalIndex){
	float distance = 0;

	for (int i = startIndex; i < goalIndex; i++)
		distance = distance + OGM->getMoveCost(OGM->getCellRowID(getPath()[i]), OGM->getCellColID(getPath()[i]), OGM->getCellRowID(getPath()[i + 1]), OGM->getCellColID(getPath()[i + 1]));
	return distance;
}


 /******************************************************************
 * isValid checks wether the cost of the path is valid
 * *************************************************************/
bool Path::isValidCost(OccupancyGridMap* map)
{
  file1 << "*************In isValidCost***************"<< endl;
  if(getPathCost(map, true)==getPathCost(map, false))
  {
    file1<< "in if"<< endl;
    file1 << "PathCostFalse= "<< getPathCost(map,false) << endl;
    file1 << "PathCostTrue= "<< getPathCost(map,true) << endl;
    return true;
  }
  else
  {
    file1<< "in else"<< endl;
    file1 << "PathCostFalse= "<< getPathCost(map,false) << endl;
    file1 << "PathCostTrue= "<< getPathCost(map,true) << endl;
    return false;
  }
}
/******************************************************************
 * isFeasible checks wether the path is feasible
 * the path is not feasible if:
 *     one cell is an obstacle
 *     two consecutive cells in the path are not connected (not implemented in this version)
 * *************************************************************/

bool Path::isFeasible(OccupancyGridMap* map)
{
  for(uint i=0; i<getPath().size()-1; i++)
  {
    if (map->isObstacle(getPath()[i]))
      return false;
    if (map->getMoveCost(getPath()[i], getPath()[i+1])==OccupancyGridMap::INFINIT_COST)
      return false;
  }
  if (map->isObstacle(getPath()[getPath().size()-1]))
      return false;
   return true;
}
/******************************************************************
 * printPath it is used to display a path 
 
 * *************************************************************/
void Path::printPath()
{
  cout << getName() <<": ";
  for(uint i=0; i< getPath().size(); i++)
  {
   cout << getPath()[i] << "   ";
  }
  cout << endl;
}   


void Path::exportPath(OccupancyGridMap* map, const char* file_name)
{
  for (uint i=0; i<getPath().size(); i++){
     map->setCell(map->getCellRowID(getPath()[i]),map->getCellColID(getPath()[i]), 255);}
       
    ofstream file (file_name, ios::trunc);  
    file<<"P2";
    file<<endl;
    file<<"#Generated by exportMapLayout in Map.h";
    file<<endl;
    file<<map->getWidth();
    file<<" ";
    file<<map->getHeight();
    file<<endl;
    file<<"255";
    file<<endl;
    
    for(uint i=0;i<map->getHeight();i++)
    {
      
      for(uint j=0;j<map->getWidth();j++)
      {
       	if (map->getMapLayout()[i][j]==0){
           file<<map->getMapLayout()[i][j];
           file<<"  ";
	}
	else
	file<<map->getMapLayout()[i][j];
	if(j<map->getWidth()-1)
	  file<<" ";
      }
      if(i<map->getHeight()-1)
	file<<endl;
     }   
}

