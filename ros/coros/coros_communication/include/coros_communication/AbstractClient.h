#ifndef ABSTRACT_CLIENT_H
#define ABSTRACT_CLIENT_H

#include <string>

/**
 * The AbstractClient is the (direct or indirect) parent of all UPD clients in any application.
 */

class AbstractClient{
  
public:
  
  AbstractClient (){ }
  
  void send(const std::string& msg, std::string ip, int port);
  
  void multicast(const std::string& message, std::string* destinations, int* ports, int size);

  void broadcast(const std::string& message, int destinationBroadcastPort);
  
protected: 
  
  virtual void init()=0;

};

#endif // ABSTRACT_CLIENT_H
