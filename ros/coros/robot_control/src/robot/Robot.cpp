#include "robot_control/Robot.h"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h> 
#include <fstream>
#include <iostream>
#include <iomanip>
#include <string>



using namespace std;

actionlib::SimpleActionClient<move_base_msgs::MoveBaseAction> * Robot::MoveBaseActionClient;

//Default Constructor
Robot::Robot (ros::NodeHandle &nh, POSE Xr, POSE Yr, POSE Angle, string IPaddr, string rName, unsigned short ROSPortNbr, unsigned short ServerPortNbr){
  
  ROSNodeHandle = nh;

  setX(Xr);
  setY(Yr);
  setYaw(Angle);
  setIPAddress(IPaddr); // it also sets "ServerHost = gethostbyname(IPAddress);"
  setType("Generic Robot");
  setName(rName);
  setROSPortNumber(ROSPortNbr);
  setServerPortNumber(ServerPortNbr);
  setLinearVelocity(0.0);
  setAngularVelocity(0.0);
  ALLOW_MOVE_F = true;
  /** check that TF works fine **/
  cout<<"Robot: [IP: "<< getIPAddress() <<", Name: "<< getName()<<"]\n --> [Robot Constructor] Attempting to listen to TF frames ..."<<endl<<endl;
  if (!TFListener.waitForTransform("base_footprint", "odom", ros::Time(0), ros::Duration(2.0)))
     cout<<"Robot: [IP: "<< getIPAddress() <<", Name: "<< getName()<<"]\n --> [ERROR] TF cannot find /base_footprint and /odom frames "<<endl<<endl;
  else
  cout<<"Robot: [IP: "<< getIPAddress() <<", Name: "<< getName()<<"]\n --> TF frames /base_footprint and /odom are found and can be transformed "<<endl<<endl;
  
  MoveBaseActionClient = new actionlib::SimpleActionClient<move_base_msgs::MoveBaseAction> ("move_base",true);
  
  
}

Robot::Robot (const ros::NodeHandle &nh, string rName){
  ROSNodeHandle = nh;
  setX(0);
  setY(0);
  setYaw(0);
  setIPAddress("127.0.0.1"); // it also sets "ServerHost = gethostbyname(IPAddress);"
  setType("Generic Robot");
  setName(rName);
  setROSPortNumber(ROS_PORT_NUMBER);
  setServerPortNumber(SERVER_PORT_NUMBER);
  setLinearVelocity(0.0);
  setAngularVelocity(0.0);
  ALLOW_MOVE_F = true;
  /** check that TF works fine **/
  cout<<"Robot: [IP: "<< getIPAddress() <<", Name: "<< getName()<<"]\n --> [Robot Constructor] Attempting to listen to TF frames ..."<<endl<<endl;
  if (!TFListener.waitForTransform("base_footprint", "odom", ros::Time(0), ros::Duration(2.0)))
     cout<<"Robot: [IP: "<< getIPAddress() <<", Name: "<< getName()<<"]\n --> [ERROR] TF cannot find /base_footprint and /odom frames "<<endl<<endl;
  else
  cout<<"Robot: [IP: "<< getIPAddress() <<", Name: "<< getName()<<"]\n --> TF frames /base_footprint and /odom are found and can be transformed "<<endl<<endl;
  
  MoveBaseActionClient = new actionlib::SimpleActionClient<move_base_msgs::MoveBaseAction> ("move_base",true);
}


Pose2D Robot::getPose(){
  return Pose;
}

//Get X Coordinate
POSE Robot::getX(){
  return Pose.getX();
}

//Get Y Coordinate
POSE Robot::getY(){
  return Pose.getY();
}

//Get Yaw
POSE Robot::getYaw(){
  return Pose.getYaw();
}

Pose2D Robot::getPoseCombined(){
  return PoseCombined;
}

//Get X Coordinate
POSE Robot::getXCombined(){
  return PoseCombined.getX();
}

//Get Y Coordinate
POSE Robot::getYCombined(){
  return PoseCombined.getY();
}

//Get Yaw
POSE Robot::getYawCombined(){
  return PoseCombined.getYaw();
}


Pose2D Robot::getAmclPose(){
  return AmclPose;
}

//Get X Coordinate
POSE Robot::getAmclX(){
  return AmclPose.getX();
}

//Get Y Coordinate
POSE Robot::getAmclY(){
  return AmclPose.getY();
}

//Get Yaw
POSE Robot::getAmclYaw(){
  return AmclPose.getYaw();
}



//Get Robot Type
string Robot::getType(){
  return Type;
}

//Get Robot Name
string Robot::getName(){
  return Name;
}

//Get IP Address
string Robot::getIPAddress(){
  return IPAddress;
}



//Get Port Number
short Robot::getROSPortNumber(){
  return ROSPortNumber;
}

//Get Port Number
short Robot::getServerPortNumber(){
  return ServerPortNumber;
}


//Set Pose
void Robot::setPose(Pose2D rPose){
  Pose=rPose;
}

//Set Pose
void Robot::setPose(POSE Xr, POSE Yr, POSE Orientation){
  setX(Xr);
  setY(Yr);
  setYaw(Orientation);
}

//Set X Coordinate
void Robot::setX(POSE Xr){
  Pose.setX(Xr);
}


//Set Y Coordinate
void Robot::setY(POSE Yr){
  Pose.setY(Yr);
}

//Set Yaw
void Robot::setYaw(POSE Angle){
  Pose.setYaw(Angle);
}


//Set Pose
void Robot::setPoseCombined(Pose2D rPose){
  PoseCombined=rPose;
}

//Set Pose
void Robot::setPoseCombined(POSE Xr, POSE Yr, POSE Orientation){
  setXCombined(Xr);
  setYCombined(Yr);
  setYawCombined(Orientation);
}

//Set X Coordinate
void Robot::setXCombined(POSE Xr){
  PoseCombined.setX(Xr);
}


//Set Y Coordinate
void Robot::setYCombined(POSE Yr){
  PoseCombined.setY(Yr);
}

//Set Yaw
void Robot::setYawCombined(POSE Angle){
  PoseCombined.setYaw(Angle);
}

//Set Pose
void Robot::setAmclPose(Pose2D rPose){
  AmclPose=rPose;
}

//Set Pose
void Robot::setAmclPose(POSE Xr, POSE Yr, POSE Orientation){
  setAmclX(Xr);
  setAmclY(Yr);
  setAmclYaw(Orientation);
}

//Set X Coordinate
void Robot::setAmclX(POSE Xr){
  AmclPose.setX(Xr);
}


//Set Y Coordinate
void Robot::setAmclY(POSE Yr){
  AmclPose.setY(Yr);
}

//Set Yaw
void Robot::setAmclYaw(POSE Angle){
  AmclPose.setYaw(Angle);
}



//Set RobotType
void Robot::setType(string RType){
  Type = RType;
}

//Set RobotType
void Robot::setName(string RName){
  Name = RName;
}

//Set IP Address
void Robot::setIPAddress(string IPAddr){
  IPAddress = IPAddr;
  //ServerHost = gethostbyname(IPAddress.c_str());
  
}



//Set RobotType
void Robot::setROSPortNumber(short PortNum){
  ROSPortNumber = PortNum;
}

void Robot::setServerPortNumber(short PortNum){
  ServerPortNumber = PortNum;
}

void Robot::setLinearVelocity(VELOCITY linear_vel){
  LinearVelocity = linear_vel;
}

void Robot::setAngularVelocity(VELOCITY ang_vel){
  AngularVelocity = ang_vel;
}

void Robot::printPose (){
  //cout << "----------------------------------------------------" <<endl;
  cout <<endl << "["<<getName() <<setw(18)<<"]: Pose: " <<getPose()<<endl;;
  //cout << left << setw(4) <<"[x: "<< left << setw(5) << getX() <<", ";
  //cout << left << setw(4) << "y: "<< left << setw(5) << getY() <<", ";
  //cout << left << setw(4) << "yaw: "<< left << setw(5) << radian2degree(getYaw())<<" degree]" <<endl;
  cout << "["<<getName() <<setw(18)<<"]: Pose Combined: " <<getPoseCombined()<<endl;
  cout << "["<<getName() <<setw(18)<<"]: Pose AMCL: " <<getAmclPose()<<endl;
  //cout << left << setw(4) <<"[x: "<< left << setw(5) << getXCombined() <<", ";
  //cout << left << setw(4) << "y: "<< left << setw(5) << getYCombined() <<", ";
  //cout << left << setw(4) << "yaw: "<< left << setw(5) << radian2degree(getYawCombined())<<" degree]" <<endl<<endl;
  //cout << "----------------------------------------------------" <<endl;
  
}



int Robot::startServer(){
  
  // Socket and connection descriptors which are just integer numbers used to access a socket
  int SocketID, connectionID;
  
  // Two socket address structures - One for the server itself and the other for client
  struct sockaddr_in serverAddress, clientAddress;
  
  // Buffer to store data read coming from the client
  unsigned char dataBuffer[BUFFER_SIZE];
  
  // Create socket of domain - Internet (IP) address, type - Stream based (TCP) and protocol unspecified
  // since it is only useful when underlying stack allows more than one protocol and we are choosing one.
  // 0 means choose the default protocol.
  SocketID = socket(AF_INET, SOCK_STREAM, 0);
  
  // A valid descriptor is always a positive value
  if(SocketID < 0)
    printf("[FUNCTION: Robot::startServer()]\n[ERROR] The socket could not be created. The creation of the socket has failed.\n");
  
  // Initialize the server address struct to zero
    bzero((char *)&serverAddress, sizeof(serverAddress));
    
    // Fill server's address family
    serverAddress.sin_family = AF_INET; //AF_INET for network protocol IPv4
    
    // Server should allow connections from any IP Address
    serverAddress.sin_addr.s_addr = INADDR_ANY;
    
    // 16 bit port number on which server listens
    // The function htons (host to network short) ensures that an integer is interpretted
    // correctly (whether little endian or big endian) even if client and server have different architectures
    serverAddress.sin_port = htons(getServerPortNumber()); //The htons() function converts the unsigned short integer hostshort from host byte order to network byte order.
    
    // Attach the server socket to a port. This is required only for server since we enforce
    // that it does not select a port randomly on it's own, rather it uses the port specified
    // in serverAddress struct.
    if (bind(SocketID, (struct sockaddr *)&serverAddress, sizeof(serverAddress)) < 0)
      // printf("[FUNCTION: Robot::startServer()]\n[ERROR] The binding of the server socket has failed.\nRobot Info: [IP: %s, Port Number: %d]...\n\n\n", static_cast<char*> (getIPAddress()), getPortNumber());
    cout<<"[FUNCTION: Robot::startServer()]\n[ERROR] The binding of the server socket has failed.\n Robot Info: [IP: "<< getIPAddress() <<", Port Number: "<< getServerPortNumber()<<"]" <<endl<<endl;
    // Server should start listening - This enables the program to halt on accept call (coming next)
    // and wait until a client connects. Also it specifies the size of pending connection requests queue
    // i.e. in this case it is 5 which means 5 clients connection requests will be held pending while
    // the server is already processing another connection request.
    listen(SocketID, 5);
    
    while(ros::ok()){
      //printf("Robot: [IP: %s, Port Number: %d]\n --> The robot server is waiting for connections ...\n", static_cast<char*> (getIPAddress()), getPortNumber());
      cout<<"Robot: [IP: "<< getIPAddress() <<", Port Number: "<< getServerPortNumber()<<"]\n --> The robot server is waiting for connections ...\n Type Ctrl+C to stop the server (wait for new data to stop)"<<endl<<endl;
      socklen_t size = sizeof(clientAddress);
      
      // Server blocks on this call until a client tries to establish connection.
      // When a connection is established, it returns a 'connected socket descriptor' different
      // from the one created earlier.
      
      connectionID = accept(SocketID, (struct sockaddr *)&clientAddress, &size);         
      if (connectionID == -1)
	cout<<"[FUNCTION: Robot::startServer()]\n[ERROR] The robot server failed to accept the connection from a client.\n Robot Info: [IP: "<< getIPAddress() <<", Port Number: "<< getServerPortNumber()<<"]" <<endl<<endl;
      
      // The new descriptor can be simply read from / written up just like a normal file descriptor
	if ( read(connectionID, dataBuffer, sizeof(dataBuffer)-1) > 0){
	  
	  cout<<"Robot: [IP: "<< getIPAddress() <<", Port Number: "<< getServerPortNumber()<<"]\n --> Data received. \nb[0]: "<<static_cast <int>(dataBuffer[0])<<"\nb[1]: "<<static_cast <int>(dataBuffer[1])<<endl<<endl;
	  bzero(dataBuffer,BUFFER_SIZE);
	  
	  dataBuffer[0]=0;
	  dataBuffer[1]=11;
	  dataBuffer[2]=12;
	  cout << "Sending Server Response ... "<<endl;
	  int requestResult = write(connectionID, dataBuffer,BUFFER_SIZE);
	  
	  if (requestResult < 0) { 
	    cout<<"ERROR writing to socket. Server Response not sent"<<endl<<endl;
	    return requestResult;
	  }
	  
	  cout << "Server Response Sent... "<<endl<<endl;
	  
	}
	  //printf("Received %s", dataBuffer);
	else
	  cout<<"Robot: [IP: "<< getIPAddress() <<", Port Number: "<< getServerPortNumber()<<"]\n --> Failed receiving / no data received. ...\n"<<endl<<endl;
	  //printf("Failed receiving / no data received.\n\n\n");
    }
    // Program should always close all sockets (the connected one as well as the listening one)
    // as soon as it is done processing with it
    cout<<"Robot: [IP: "<< getIPAddress() <<", Port Number: "<< getServerPortNumber()<<"]\n -->Closing Client Connection ... "<<endl;
    close(connectionID);
    cout<<"Robot: [IP: "<< getIPAddress() <<", Port Number: "<< getServerPortNumber()<<"]\n -->Client Connection Closed ... "<<endl;
    cout<<"Robot: [IP: "<< getIPAddress() <<", Port Number: "<< getServerPortNumber()<<"]\n -->Closing Server Socket ... "<<endl;
    close(SocketID); 
    cout<<"Robot: [IP: "<< getIPAddress() <<", Port Number: "<< getServerPortNumber()<<"]\n -->Server Socket Closed. "<<endl;
    cout<<"Robot: [IP: "<< getIPAddress() <<", Port Number: "<< getServerPortNumber()<<"]\n -->TCP Server Terminated. "<<endl<<endl;
    return 0; 
    
    
}

/** ********************************************************** **/
/** This function connects to the Robot using TCP connection * **/
/** ********************************************************** **/
int Robot::connect2TCPServer (short & SocketID, string ServerIPAddress,  unsigned short PortNum) {
  
  //define socket description, port number
  int ConResult;
  
  struct sockaddr_in ServerAddress;
  struct hostent *ServerHost;
  
  ServerHost = gethostbyname(ServerIPAddress.c_str());
  
  //Create a TCP socket 
  SocketID = socket(AF_INET, SOCK_STREAM, 0);
  //cout <<SocketID<<endl;
  //handle errors with socket initiation. 
  if (SocketID < 0) 
    cout<<"ERROR opening socket";
  
  if (ServerHost == NULL) {
    fprintf(stderr,"ERROR, no such host\n");
    exit(0);
  }
  //initialize serverAddress to zero
  bzero((char *) &ServerAddress, sizeof(ServerAddress));
  //set server_addr paramters
  ServerAddress.sin_family = AF_INET;
  bcopy((char *)ServerHost->h_addr, 
	(char *)&ServerAddress.sin_addr.s_addr,
	ServerHost->h_length);
  
  
  ServerAddress.sin_port = htons(PortNum);
  
  ConResult = connect(SocketID,(struct sockaddr *) &ServerAddress,sizeof(ServerAddress));
  
  return ConResult;
  
}

/** ****************************************************************** **/
/** This function allows the robot to send a request to the TCP server **/
/** ****************************************************************** **/


int Robot::sendRequest (short socketID){
  
  unsigned char dataBuffer[2];
  unsigned char RobotDataBuffer[15];
	int requestResult;
	
	
	struct student 
              {
                  char name [16];
                  unsigned short student_id;
                  char host[16];
                  unsigned short pid;
                  char email[60];

              }r1;
	
   	bzero(dataBuffer,2);
	
	dataBuffer[0]=1;
	dataBuffer[1]=2;
	cout << "Sending Client Request ... "<<endl;
	requestResult = write(socketID, dataBuffer,2);
	
	if (requestResult < 0) { 
		cout<<"ERROR writing to socket. Request not sent"<<endl<<endl;
		return requestResult;
		}
		
	cout << "Client Request Sent... "<<endl<<endl;
		
	//get robot data
	bzero(RobotDataBuffer,15);
    //requestResult = read(socketID, RobotDataBuffer,15);
    struct student pkt;
        
    requestResult = recv(socketID, &pkt, sizeof(struct student), 0);
    //requestResult = read(socketID, &pkt,sizeof(struct student));
    if (requestResult < 0){ 
		cout<<"ERROR reading from socket: student id: "<<pkt.student_id<<endl;
		return requestResult;
		}
		else{
		  cout<<" Good. student id: "<<pkt.student_id<<endl;
		  cout<<" Good. student email: "<<pkt.email<<endl;
		  cout<<" Good. student pid: "<<pkt.pid<<endl;
		  cout<<" Good. student name: "<<pkt.name<<endl;
		}
	return requestResult; 
}



