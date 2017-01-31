#ifndef PUSHNOTIFIER_H
#define PUSHNOTIFIER_H

#include <string>
#include <vector>

extern "C"
{
	#include "jsmn/jsmn.h"
}

#include "network/network.h"
#include "exception/exception.h"


#define TYPE_MESSAGE "MESSAGE"
#define TYPE_URL "URL"

#define API_TOKEN "YOUR API TOKEN"
#define APP_PACKAGE "YOUR APP PACKAGE"
#define USER_AGENT "PushNotifier-CPP/1.0"

#define URL_LOGIN "http://a.pushnotifier.de/1/login/"
#define URL_CHECK_TOKEN "http://a.pushnotifier.de/1/checkToken/"
#define URL_GET_DEVICES "http://a.pushnotifier.de/1/getDevices/"
#define URL_SEND_TO_DEVICE "http://a.pushnotifier.de/1/sendToDevice/"



class PushNotifier
{
public:
	struct device 
	{
		unsigned int id;
		std::string title;
		std::string model;
	};
	
	PushNotifier(std::string username, std::string password);
	PushNotifier(std::string token);
	
	std::string getToken();
	std::vector<device> getDevices();
	bool sendToDevice(std::string content, std::string type, unsigned int device);
	bool checkToken(std::string username);

private:
	std::string username;
	std::string token;

	class subNetwork : public Network
	{
	public:
		std::string httpHandler(std::string url, std::string data);
	} myNetwork;
};


//Exceptions & ErrorHandling
class LoginFailedException : public CustomException 
{
public:
	LoginFailedException(std::string status, int code) : CustomException(status, code) {};
};

class InvalidTokenException : public CustomException 
{
public:
	InvalidTokenException(std::string status, int code) : CustomException(status, code) {};
};

class PushFailedException : public CustomException 
{
public:
	PushFailedException(std::string status, int code) : CustomException(status, code) {};
};

class LimitExceededException : public CustomException 
{
public:
	LimitExceededException(std::string status, int code) : CustomException(status, code) {};
};

class UnexpectedValueException : public CustomException
{
public:
	UnexpectedValueException(std::string status, int code) : CustomException(status, code) {};
};

typedef enum  
{
	//General
	INVALID_API_TOKEN = 1,
	APP_TOKEN_MISSING = 2,
	APP_TOKEN_UNKNOWN = 3,
	LIMIT_EXCEEDED = 9001,

	//sendToDevice
	APP_IDENTIFIER_MISSING = 4,
	APP_INVALID = 5,
	APP_PIRATING = 6,
	DEVICE_ID_MISSING = 7,
	DEVICE_NOT_FOUND = 8,
	INVALID_TYPE = 9,
	PUSH_INVALID_URL = 10
} PNErrorCodes;

#endif
