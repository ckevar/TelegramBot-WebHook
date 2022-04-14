#ifndef HTTP_PARSER_H
#define HTTP_PARSER_H

/* REST Methods */
#define HTTP_METHOD_NONE 	0

#define HTTP_METHOD_GET_STR 	"GET"
#define HTTP_METHOD_GET_LEN 	3
#define HTTP_METHOD_GET 	1

#define HTTP_METHOD_POST_STR 	"POST"
#define HTTP_METHOD_POST_LEN	4
#define HTTP_METHOD_POST	2

#define HTTP_METHOD_PUT_STR 	"PUT"
#define HTTP_METHOD_PUT_LEN 	3
#define HTTP_METHOD_PUT 	3

#define HTTP_METHOD_DELETE_STR 	"DELETE"
#define HTTP_METHOD_DELETE_LEN 	6
#define HTTP_METHOD_DELETE 	4

#define HTTP_HTTP_1_1_STR 	"HTTP/1.1"
#define HTTP_HTTP_1_1_LEN 	8

/* Header Fields */
#define HTTP_CONTENT_LENGTH_STR "Content-Length: "
#define HTTP_CONTENT_LENGTH_LEN	16

#define HTTP_CONNECTION_STR 	"Connection: "
#define HTTP_CONNECTION_LEN 	12
#define HTTP_CONN_KEEPALIVE_STR "keep-alive"
#define HTTP_CONN_KEEPALIVE_LEN 10
#define HTTP_CON_CLOSE_STR 	"close"
#define HTTP_CON_CLOSE_LEN 	5

typedef struct HTTP_Resource_t {
	char *resource;
	short size;
} HTTP_Resource_t;


class HTTPParser
{
public:
	HTTPParser(){} // Default contructor
	void load(char *msg);
	char parse();
	void reset_http_iterator();

	// Properties
	char RESTMethod;
	HTTP_Resource_t resource;
	short ContentLength;
	char *Content;

private:
	// Properties
	char *http;
	char *http_it;

	// Methods
	void lookup_method();
	void locate_resource_ptr();
	void lookup_HeaderFields();
	void locate_Content();
};

#endif

/*
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
	// MIME Type genenrator
	void MIMEType(std::string *rType);
};
#endif
*/
