#ifndef ABSTRACT_SERVER_H
#define ABSTRACT_SERVER_H

#include <string>

/**
 * The AbstractServer is the (direct or indirect) parent of all UPD servers in any application.
 */
class AbstractServer {
  
public:

  AbstractServer (const int& port);
 
  bool bind();
  
  void listen();
  
  virtual void process(const std::string& message, const std::string& fromIP) = 0;  // processes the message. In the most of our cases, forwards the message to the relevant ros topic/node.
   
  void setPort(int number) {myPort = number;}
  
  int getPort() {return myPort;}
  
 
protected:
  
  virtual void init()=0; 
  
  virtual bool again()=0;

  int mySocket;
  
  int myPort;
    
};

#endif // ABSTRACT_SERVER_H
