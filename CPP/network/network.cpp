#include "network.h"
#include <string.h>

using namespace std;

Network::Network()
{
	sock = -1;
	port = 0;
	address = "";
}

Network::~Network()
{

}

bool Network::connection(string address, int port)
{
	if(sock == -1)
	{
		sock = socket(AF_INET, SOCK_STREAM, 0);
		if(sock == -1) { return false; }
	}

	if(inet_addr(address.c_str()) == -1)
	{
		struct hostent *he;
		struct in_addr **addr_list;

		if((he = gethostbyname(address.c_str())) == NULL) { return false; }

		addr_list = (struct in_addr **) he->h_addr_list;

		for(int i = 0; addr_list[i] != NULL; i++)
		{
			server.sin_addr = *addr_list[i];

			break;
		}
	}
	else
	{
		server.sin_addr.s_addr = inet_addr(address.c_str());
	}

	server.sin_family = AF_INET;
	server.sin_port = htons(port);

	if(connect(sock, (struct sockaddr *)&server, sizeof(server)) < 0)
	{
		return 1;
	}

	return true;
}

bool Network::sendData(string data)
{
	if(send(sock, data.c_str(), strlen(data.c_str()), 0) < 0)
	{
		return false;
	}

	return true;
}

string Network::receive()
{
	char buffer[1024];
	int iReadBytes = 0;
	string strIn;

/**
	do
	{
		iReadBytes = recv(sock, buffer, sizeof(buffer), MSG_NOSIGNAL); //signals abgeschaltet
		
		cout << iReadBytes << endl;

		if(iReadBytes > 0)
		{
			for(int i = 0; i<=iReadBytes; i++)
			{
				strIn += buffer[i-1];
			}
		}
	} while( iReadBytes > 0);
**/


	while(true)
	{
		iReadBytes = recv(sock, buffer, sizeof(buffer), MSG_NOSIGNAL);

		if(!iReadBytes > 0)
		{
//			cout << "zero" << endl;
			break;
		}
		else
		{
			for(int x=0; x < iReadBytes; x++)
			{
				strIn += buffer[x];
			}

			if(iReadBytes < 1024)
			{
				break;
			}
		}
	}

	if(iReadBytes == 0) {/**Abbruch der Verbindung**/}
	if(iReadBytes < -1) {/**Socket Fehler**/}

	return strIn;
}
