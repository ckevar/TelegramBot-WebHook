#include "WebServer.h"

#include <cstdio>
#include <csignal>

#define HTTPPORT 80
#define HTTPSPORT 443

WebServer webServer("0.0.0.0", HTTPSPORT);

void signalHandler(int signum) {
	printf("Terminating Server\n");
	webServer.stop();
}

int main(int argc, char const *argv[]) {

	signal(SIGINT, signalHandler);

	if (webServer.init() != 0)
		return -1;

	if(webServer.run() < 0) return -1;

	return 0;
}
