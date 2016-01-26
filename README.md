# ROS Web Services #
This package presents the tools needed to run and test ROS Web Services. 
To read in details about the design of ROS Web Service, read this paper
Anis Koubaa "ROS As a Service: Web Services for Robot Operating System", Journal of Software Engineering for Robotics, 6(1), Dec 2015.

Link: http://joser.unibg.it/index.php?journal=joser&page=article&op=view&path%5B%5D=97&path%5B%5D=30

#Working Environment #
The code was developed, tested and deployed on ROS Hydro. There is no guarantee that it will work on ROS Indigo or later versions due to probable incompatibilty of rosjava
You need to have Netbeans IDE.

#Warning#
You must have some basic understanding of ROSJAVA to be able to understand this code.

#Install#
1. Get a Ubuntu 12.04 machine with ROS Hydro installed
2. Install all rosjava and android_core components. Make sure that defaults example Talker/Listener works
3. Download the current repo https://github.com/aniskoubaa/ROSWebServices
4. In your home Directory create the folders Dropbox/mybot_ws/src, which will be consider as your catkin workspace.
There are some links that may refer to this directory hierarchy, otherwise you can create any directory. It may work with any other directory, but some tweaking may be needed.
5. Move all files in the directory "ros" in your ~/Dropbox/mybot_ws/src folder, which is you catkin worksapce.. 
6. Put the Netbeans project into a directory of your choice. 
7. Open the project with Netbeans.

#Check ROS Environment#
The demo presented in https://www.youtube.com/watch?v=WvjY5XjAX7U deploy ROS Web Services with Turtlbot simulated robot. The simulation used is that provided by the Book "ROS By Example 1: Hydro Version"


2. Compile the ros packages you moved in your catkin workspace. It is possible that some packages in rbx1 do not compile from the first time. 
There are certain dependendcies that must be installed as indicated in the book "ROS By Example 1: Hydro Version"
Get the book and download the dependencies.

If this is not possible, then you can simply run the simple example of Turtlesim and not the Turtlebot. 
In this case, you do not need any of the ROS packages provided. 

#Run the simple Turtlesim example#
run Turtlesim
```
$ roscore
$ rosrun turtlesim turtlesim_node
```
## SOAP Web Services ##
then, open in Netbeans, run the Web Service server first:
 go to the file org.mybot.turtlesim.rosjava.TurtleSim.java
 set the correct IP address of your machine (use ifconfig) for the variable 
  ```
  $public static String IPAddress 
 ```
 run the SOAP Web Server Server program 
  ```
  $org.mybot.turtlesim.soap.TurtlesimListenersWebServiceNodesRunner
  ```
Do not worry about the red message coming, unless you find an Exception. If you find an exception, fix the error.
If no Exception, then ignore red messages. 
run the SOAP Web Service Client program 
  ```
  $org.mybot.turtlesim.soap.client.TurtlesimListenersWebServiceClientRunner
  ```
  Do not worry about the red message coming, unless you find an Exception. If you find an exception, fix the error.
If no Exception, then ignore red messages. 
Press a key, you will see the Position of turtlesim coming as a result of a web service invocation. 

Browse the code to understand how it works. Read the paper above for more details. 

You can see the WSDL document, when the Web Service server is running by 
```
  $http://your_machine_ip_adress:1239/turtlesim_listerners_ws?wsdl
```
  
You can also run the REST Web service. You shoul be familar with REST to make it run.

#Run the Delivery Application#
 If the ROS package you moved into your catkin_ws compile and work, then you can run this example as follow:
 Run the simulation environment with RVIZ
 ```
  $roslaunch mybot_bringup fake_mybot_psu_map_partial.launch
  ```
  If all is fine, you should see rviz running. Zoom the map and place the robot in a location.
  
  run the Web Service server application
  ```
  $org.mybot.turtlebot.soap.TurtlebotPublishersWebServiceNodesRunner
  ```
  Do not worry about the red message coming, unless you find an Exception. If you find an exception, fix the error.
If no Exception, then ignore red messages. 
  Then, run the Web service client
 ```
  $org.mybot.turtlebot.soap.client.TurtlebotPublishersWebServiceClient
  ```
 


