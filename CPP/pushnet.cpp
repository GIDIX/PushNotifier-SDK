#include "pushnotifier.h"

#include <string>
#include <sstream>
#include <string.h>

using namespace std;

#define URL_BASE "a.pushnotifier.de"

string PushNotifier::subNetwork::httpHandler(string url, string data)
{
	connection(URL_BASE, 80);

	url.erase(0,strlen("http://"));
	url.erase(0, strlen(URL_BASE));

	stringstream request;
	
	request << "POST " << url  << " HTTP/1.1\r\n";
	request << "Host: " << URL_BASE << "\r\n";
	request << "Content-type: application/x-www-form-urlencoded\r\n";
	request << "User-Agent: " << USER_AGENT << "\r\n";
	request << "Content-length: " << data.length();
	request << "\r\n\r\n" << data << "\r\n";

	string input;
	sendData(request.str());
	input = receive();

	string buffer;

	buffer = input.substr(input.find_first_of("{"), input.find_last_of("}")-input.find_first_of("{")+1);

	return buffer;
}
