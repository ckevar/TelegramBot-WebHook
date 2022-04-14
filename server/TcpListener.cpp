#include "TcpListener.h"
#include <iostream>
#include <cstring>
#include <sstream>
#include <cstdio>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <openssl/err.h>

int TcpListener::init()
{
	// Create a socket
	m_socket = socket(AF_INET, SOCK_STREAM, 0);
	if (m_socket < 0) {
		fprintf(stderr,"[ERROR:] cannot open socket");
	}

	// Bind the ip address and port to a socket
	struct sockaddr_in hint;
	hint.sin_family = AF_INET;
	hint.sin_port = htons(m_port);
	inet_pton(AF_INET, m_ipAddress, &hint.sin_addr);
	int bindStatus = bind(m_socket, (sockaddr*)&hint, sizeof(hint));
	if (bindStatus < 0) {
		fprintf(stderr, "[ERROR:] at binding %d\n", bindStatus);
		return -1;
	}
	// Tell the socket is for listening 
	if (listen(m_socket, SOMAXCONN) < 0) {
		fprintf(stderr, "[ERROR:] at listening\n");
		return -1;
	}

	// Initialize SSL
	OpenSSL_add_all_algorithms(); // load & register all cryptos
	SSL_load_error_strings(); 	// load all error messages
	const SSL_METHOD *method = TLSv1_2_server_method(); // create a new server-method 
	//const SSL_METHOD *method = SSLv23_client_method();
	ctx = SSL_CTX_new(method); 		// crea a new context for that method
	if (ctx == NULL) {
		ERR_print_errors_fp(stderr);
		return -1;
	}

	// Load certificate
	//sslkeys/my-ssl-private.key
	//sslkeys/my-ssl-public.pem
	// set the local certifcate from Certfile
	if (SSL_CTX_use_certificate_file(ctx, "sslkeys/my-ssl-public.pem", SSL_FILETYPE_PEM) <= 0) {
		ERR_print_errors_fp(stderr);
		return -1;
	}
	// Set the private key from keyFile
	if (SSL_CTX_use_PrivateKey_file(ctx, "sslkeys/my-ssl-private.key", SSL_FILETYPE_PEM) <= 0) {
		ERR_print_errors_fp(stderr);
		return -1;
	}
	// verify private key 
	if(!SSL_CTX_check_private_key(ctx)) {
		fprintf(stderr, "Private key does not match the public certification\n");
		return -1;
	}
	// Create the master file descriptor set and assing -1 file descriptor, and no event
	for (int i = 0; i < (MAX_CLIENTS + 1); ++i) {
		m_master[i].fd = -1;
		m_master[i].events = 0;
	}

	// Add our first socket that we're interested in interacting with; the listening socket!
	// It's important that this socket is added for our server or else we won't 'hear' incoming
	// connections 
	available = MAX_CLIENTS;
	m_master[0].fd = m_socket; // the index zero is our listening socket

	running = true;	// Enable server to run
	return 0;
}

int TcpListener::run() {
	// this will be changed by the \quit command (see below, bonus not in video!)

	while (running) {
		std::cout << "[DEBUG:] Available seats " << available << " out of " << MAX_CLIENTS << std::endl;
		m_master[0].events = (available > 0) ? POLLIN : 0;	// Updating the event based on the availability

		// 30 miliseconds to wait in case there are clients,
		// otherwise let's get stuck in poll until, some clients show up
		// See who's talking to us
		int socketCount = poll(m_master, MAX_CLIENTS, -1);

		// Is it an inbound communication?
		if (m_master[0].revents == POLLIN) {
			// Accept a new connection
			int client = accept(m_socket, nullptr, nullptr);

			// Add the new connection to the list of connected clients
			allocateClient(client);

			onClientConnected(client);
			socketCount--;
		}

		int i = 1;
		// It's an inbound message
		// Loop through all the current connections / potential connect
		while (socketCount > 0) {

			if(m_master[i].revents == POLLIN) {
				char buf[4096];
				memset(buf, 0, 4096);
				int sock = m_master[i].fd;

				// Receive message
				//int bytesIn = recv(sock, buf, 4096, 0);
				int bytesIn = SSL_read(ssl_master[i], buf, 4096);
				if (bytesIn <= 0) {
					// Drop the client
					onClientDisconnected(sock);
					close(sock);
					deallocateClient(sock);
				}
				else {
					//onMessageReceived(sock, buf, bytesIn);
					onMessageReceived(ssl_master[i], buf, bytesIn);
				}
				socketCount--;
			}
			i++;
		}
	}

	// Remove the listening socket from the master file descriptor set and close it
	// to prevent anyone else trying to connect.
	int closeStatus = close(m_master[0].fd);
	if (closeStatus < 0) {
		fprintf(stderr, "failed closing listner port, trying again\n");
		close(m_master[0].fd);
	}

	int i = 1;

	while (available != MAX_CLIENTS) {

		if (m_master[i].fd) {
			// Get the socket number
			close(m_master[i].fd);
			// Remove it from the master file list and close the socket
			m_master[i].fd = -1;
			SSL_free(ssl_master[i]);
			available++;
		}
		i++;
	}

	return 0;
}

void TcpListener::stop(){
	running = false;
}

void TcpListener::allocateClient(int client) {
	unsigned i = 1;

	while(m_master[i].fd > -1) i++;
	available--;
	
	m_master[i].fd = client;
	m_master[i].events = POLLIN;

	ssl_master[i] = SSL_new(ctx);	// creates a new context for new client
	SSL_set_fd(ssl_master[i], client);	// set connection socket to SSL state

	if (SSL_accept(ssl_master[i]) == -1) {
		ERR_print_errors_fp(stderr);
		deallocateClient(client);
	} 
}

void TcpListener::deallocateClient(int client) {
	unsigned i = 1; // starts at 1, because internal listener socket is at 0
	
	while(m_master[i].fd != client) i++;
	available++;

	m_master[i].fd = -1;
	m_master[i].events = 0;

	SSL_free(ssl_master[i]);
}


//void TcpListener::sendToClient(int clientSocket, const char* msg, int length) {
//	send(clientSocket, msg, length, 0);
void TcpListener::sendToClient(SSL *clientSocket, const char *msg, int length){
	SSL_write(clientSocket, msg, length);
}

void TcpListener::broadcastToClients(int sendingClient, const char* msg, int length) {
	int j = available;
	int i = 1;			// start at 1, because the internal listener is at 0
	while (j > 0) {		// Send to all available devices
		int outSock = m_master[i].fd;
		if (outSock > -1) {	
			if (outSock != sendingClient) // dont sent to the one who's broadcasting
				//sendToClient(outSock, msg, length);
				sendToClient(ssl_master[i], msg, length);
			j--;
		}
		i++;
	}
}

void TcpListener::onClientConnected(int clientSocket) {

}

void TcpListener::onClientDisconnected(int clientSocket) {

}

//void TcpListener::onMessageReceived(int clientSocket, const char* msg, int length) {
void TcpListener::onMessageReceived(SSL *clientSocket, const char *msg, int length){

}
