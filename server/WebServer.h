#ifndef WEB_SERVER_H
#define WEB_SERVER_H

#include "TcpListener.h"
#include "HTTPParser.h"
#include <string>

#define HTTP_METHOD_INDEX 	0
#define HTTP_RESOURCE_INDEX	1

class WebServer : public TcpListener
{
public:

	WebServer(const char* ipAddress, int port) :
		TcpListener(ipAddress, port) { }

protected:

	// Handler for client connections
	virtual void onClientConnected(int clientSocket);

	// Handler for client disconnections
	virtual void onClientDisconnected(int clientSocket);

	// Handler for when a message is received from the client
	//virtual void onMessageReceived(int clientSocket, const char* msg, int length);
	virtual void onMessageReceived(SSL *clientSocket, const char *msg, int length);

private:
	std::string contentType;
	HTTPParser http;
	// MIME Type genenrator
	void MIMEType(std::string *rType);
};
#endif
