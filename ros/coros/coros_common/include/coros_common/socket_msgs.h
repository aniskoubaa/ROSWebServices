#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h> 
#include <iostream>
#include <iomanip>
#include <vector>


struct common_target_type{
  int message_code;//code of the message
  unsigned short id;//id of the target
  double x;//x coordinate of the target
  double y;//y coordinate of the target
  double cost;// cost 
} target;
