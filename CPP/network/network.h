#ifndef NETWORK_H
#define NETWORK_H

#include <string>
#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netdb.h>

class Network
{
private:
	int port;
	int sock;
	std::string address;
	struct sockaddr_in server;

public:
	Network();
	~Network();

	bool connection(std::string, int);
	bool sendData(std::string);
	std::string receive();
};

#endif
