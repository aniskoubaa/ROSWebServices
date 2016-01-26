#ifndef AGENT_STATE_H
#define AGENT_STATE_H

#include <string>

class AgentState
{

public:
  
  AgentState(int id=-1, std::string ip="127.0.0.1", int ts=0,  int port=0, std::string role="Robot", std::string status=INITIALIZED_STATUS, std::string name="robot_no_name") :
             myId(id), myIpAddress(ip), myTimestamp(ts), myPort(port), myRole(role), myStatus(status), myName(name){}
  

  void setId(int id)                { myId = id;         }
  void setPort(int port)            { myPort = port;     }
  void setTimestamp(int ts)         { myTimestamp = ts;  }
  void setRole(std::string role)    { myRole = role;     }
  void setStatus(std::string status){ myStatus = status; }
  void setIpAddress(std::string ip) { myIpAddress = ip;  }
  void setName(std::string name) 	{ myName = name;  }
 
  int getId()    { return myId;       }  
  int getPort()             { return myPort;     }
  int getTimestamp()        { return myTimestamp;}
  std::string getRole()     { return myRole;     }
  std::string getStatus()   { return myStatus;   }
  std::string getIpAddress(){ return myIpAddress;}
  std::string getName(){ return myName;}
  

  static const std::string INITIALIZED_STATUS;

  static const std::string AVAILABLE_STATUS  ;

  static const std::string UNAVAILABLE_STATUS;

  static const std::string MOVING_STATUS;

private:
  
  int myId;     //id of the agent
  
  std::string myRole;      //the role played by an agent in the app or in the mission (Robot, Control Station, Monitor, etc.)
     
  std::string myStatus;    //current status of the agent (available, in_negociation, in_mission, etc)... use enum instead it will be better
  
  std::string myIpAddress; //ip of the agent
  
  std::string myName; //name of the agent - added by Anis

  int myPort;              //port of the agent - may be obsolete
  
  int myTimestamp;         //timestamp: time of the registration
  
};

#endif //AGENT_STATE_H
