#include "coros_communication/NodeServer.h"


NodeServer::NodeServer(const std::string& nodeName, int port)
	: Node(nodeName),
	  AbstractServer(port)
{

}


void NodeServer::process(const std::string&  message, const std::string& fromIP)
{
  forward(message, fromIP);
}


bool NodeServer::again()
{
	return isOK();
}
