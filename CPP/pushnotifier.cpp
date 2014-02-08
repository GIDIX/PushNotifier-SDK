#include "pushnotifier.h"

#include <sstream>
#include <vector>
#include <string.h>
#include <algorithm>

#include <iostream>

using namespace std;


PushNotifier::PushNotifier(string token) 
{
	this->token = token;
}

PushNotifier::PushNotifier(string username, string password)
{
	stringstream data;
	data << "apiToken=" << API_TOKEN;
	data << "&username=" << username;
	data << "&password=" << password;

	//JSON stuff
	jsmn_parser p;
	jsmn_init(&p);
	jsmntok_t tokens[10];
	const char *js;
	string input;

	input = this->myNetwork.httpHandler(URL_LOGIN, data.str());

	js = input.c_str();
	jsmn_parse(&p, js, tokens, 10);

	string antwortCode, antwortStatus;

	for(int i = 0; i < p.toknext; i++)
	{
		if(tokens[i].type == JSMN_STRING)
		{
			string thisString;
			thisString = input.substr(tokens[i].start, tokens[i].end-tokens[i].start);

			if(thisString == "status")
			{	
				i++;
				antwortStatus = input.substr(tokens[i].start, tokens[i].end-tokens[i].start);
			}
			else if(thisString == "code")
			{
				i++;
				antwortCode = input.substr(tokens[i].start, tokens[i].end-tokens[i].start);
			}
			else if(thisString == "appToken")
			{
				i++;
				this->token = input.substr(tokens[i].start, tokens[i].end-tokens[i].start);
			}
		}

		if(antwortStatus != "ok" && !antwortCode.empty())
		{
			int aCode;
			istringstream ss(antwortCode);
			ss >> aCode;

			if(antwortStatus == "wrongCredentials") { throw LoginFailedException(antwortStatus, aCode); }

			switch(aCode)
			{
			case INVALID_API_TOKEN:
			case APP_TOKEN_MISSING:
			case APP_TOKEN_UNKNOWN: 
				throw InvalidTokenException(antwortStatus, aCode);
			break;
			case LIMIT_EXCEEDED:
				throw LimitExceededException(antwortStatus, aCode);
			break;
			case APP_IDENTIFIER_MISSING:
			case APP_INVALID:
			case APP_PIRATING:
			case DEVICE_ID_MISSING:
			case DEVICE_NOT_FOUND:
			case INVALID_TYPE:
			case PUSH_INVALID_URL:
				throw PushFailedException(antwortStatus, aCode);
			break;	
			default: 
				throw UnexpectedValueException(antwortStatus, aCode);
			};
		}
	}
}

vector<PushNotifier::device> PushNotifier::getDevices()
{
	vector<device> buffer;

	stringstream data;

	data << "apiToken=" << API_TOKEN;
	data << "&appToken=" << this->token;
	
	string input;
	input = this->myNetwork.httpHandler(URL_GET_DEVICES, data.str());
	
	//JSON stuff
	jsmn_parser p;
	jsmn_init(&p);
	jsmntok_t tokens[256];
	const char* js;
	js = input.c_str();

	jsmn_parse(&p, js, tokens, 256);

	string antwortStatus, antwortCode;

	for(int i = 1; i < p.toknext; i++)
	{
    	if(tokens[i].type == JSMN_STRING)
        {
        	string thisString;
			thisString = input.substr(tokens[i].start, tokens[i].end-tokens[i].start);	
     	
			if(thisString == "status")
			{
				antwortStatus = input.substr(tokens[i+1].start, tokens[i+1].end-tokens[i+1].start);
			}
			else if(thisString == "code")
			{
				antwortCode = input.substr(tokens[i+1].start, tokens[i+1].end-tokens[i+1].start);
			}
		}
		else if(tokens[i].type ==JSMN_OBJECT)
		{
			string small = input.substr(tokens[i].start, tokens[i].end-tokens[i].start);
			jsmn_parser tec;
			jsmn_init(&tec);
			jsmntok_t toki[10];
			const char* jj = small.c_str();
			jsmn_parse(&tec, jj, toki, 10);

			device eins;

			for(int g = 0; g < tec.toknext; g++)
			{
				string kleiner;
				kleiner = small.substr(toki[g].start, toki[g].end - toki[g].start);

				if(kleiner == "model")
				{
					g++;
					eins.model = small.substr(toki[g].start, toki[g].end - toki[g].start);
				}
				else if(kleiner == "title")
				{
					g++;
					eins.title = small.substr(toki[g].start, toki[g].end - toki[g].start);
				}
				else if(kleiner == "id")
				{
					g++;
					istringstream ff(eins.model = small.substr(toki[g].start, toki[g].end - toki[g].start));
					ff >> eins.id;
				}
			}
			buffer.push_back(eins);
		}

		if(antwortStatus != "ok" && !antwortCode.empty())
		{
			int aCode;
			istringstream ss(antwortCode);
			ss >> aCode;

			switch(aCode)
			{
			case INVALID_API_TOKEN:
			case APP_TOKEN_MISSING:
			case APP_TOKEN_UNKNOWN: 
				throw InvalidTokenException(antwortStatus, aCode);
			break;
			case LIMIT_EXCEEDED:
				throw LimitExceededException(antwortStatus, aCode);
			break;
			case APP_IDENTIFIER_MISSING:
			case APP_INVALID:
			case APP_PIRATING:
			case DEVICE_ID_MISSING:
			case DEVICE_NOT_FOUND:
			case INVALID_TYPE:
			case PUSH_INVALID_URL:
				throw PushFailedException(antwortStatus, aCode);
			break;	
			default: 
				throw UnexpectedValueException(antwortStatus, aCode);
			};
		}
	}


	return  buffer;
}

bool PushNotifier::sendToDevice(string content, string type, unsigned int device)
{
	stringstream data;

	data << "apiToken=" << API_TOKEN;
	data << "&appToken=" << this->token;
	data << "&app=" << APP_PACKAGE;
	data << "&deviceID=" << device;
	data << "&type=" << type;
	data << "&content=" << content;

	string input = this->myNetwork.httpHandler(URL_SEND_TO_DEVICE, data.str());

	const char *js = input.c_str();

	jsmn_parser p;
	jsmn_init(&p);
	jsmntok_t tokens[10];

	jsmn_parse(&p, js, tokens, 10);

	string antwortStatus, antwortCode;

	for(int i = 0; i < p.toknext; i++)
	{
		if(tokens[i].type == JSMN_STRING)
		{
			string thisString;
			thisString = input.substr(tokens[i].start, tokens[i].end-tokens[i].start);

			if(thisString == "status")
			{	
				i++;
				antwortStatus = input.substr(tokens[i].start, tokens[i].end-tokens[i].start);
				if(antwortStatus == "ok") { return true; }
			}
			else if(thisString == "code")
			{
				i++;
				antwortCode = input.substr(tokens[i].start, tokens[i].end-tokens[i].start);
			}
		}

		if(antwortStatus != "ok" && !antwortCode.empty())
		{
			int aCode;
			istringstream ss(antwortCode);
			ss >> aCode;

			switch(aCode)
			{
			case INVALID_API_TOKEN:
			case APP_TOKEN_MISSING:
			case APP_TOKEN_UNKNOWN: 
				throw InvalidTokenException(antwortStatus, aCode);
			break;
			case LIMIT_EXCEEDED:
				throw LimitExceededException(antwortStatus, aCode);
			break;
			case APP_IDENTIFIER_MISSING:
			case APP_INVALID:
			case APP_PIRATING:
			case DEVICE_ID_MISSING:
			case DEVICE_NOT_FOUND:
			case INVALID_TYPE:
			case PUSH_INVALID_URL:
				throw PushFailedException(antwortStatus, aCode);
			break;	
			default: 
				throw UnexpectedValueException(antwortStatus, aCode);
			};
		}
	}

	return false;
}

bool PushNotifier::checkToken(string username)
{
	this->username = username;

	stringstream data;
	
	data << "apiToken=" << API_TOKEN;
	data << "&username=" << this->username;
	data << "&appToken=" << this->token;
	
	string input;
	input = this->myNetwork.httpHandler(URL_CHECK_TOKEN, data.str());

	const char *js;
	js = input.c_str();
	jsmn_parser p;
	jsmn_init(&p);
	jsmntok_t tokens[10];

	jsmn_parse(&p, js, tokens, 10);

	string antwortStatus, antwortCode;

	for(int i = 1; i < p.toknext; i++)
	{
		if(tokens[i].type == JSMN_STRING)
		{
			string klein;
			klein = input.substr(tokens[i].start, tokens[i].end-tokens[i].start);
		
			if(klein == "status")
			{
				i++;
				antwortStatus = input.substr(tokens[i].start, tokens[i].end-tokens[i].start);
			
				if(antwortStatus == "ok") { return true; }
			}
			else if(klein == "code")
			{
				i++;
				antwortCode = input.substr(tokens[i].start, tokens[i].end-tokens[i].start);
			}
		}

		if(antwortStatus != "ok" && !antwortCode.empty())
		{
			int aCode;
			istringstream ss(antwortCode);
			ss >> aCode;
			
			switch(aCode)
			{
			case INVALID_API_TOKEN:
			case APP_TOKEN_MISSING:
			case APP_TOKEN_UNKNOWN: 
				throw InvalidTokenException(antwortStatus, aCode);
			break;
			case LIMIT_EXCEEDED:
				throw LimitExceededException(antwortStatus, aCode);
			break;
			case APP_IDENTIFIER_MISSING:
			case APP_INVALID:
			case APP_PIRATING:
			case DEVICE_ID_MISSING:
			case DEVICE_NOT_FOUND:
			case INVALID_TYPE:
			case PUSH_INVALID_URL:
				throw PushFailedException(antwortStatus, aCode);
			break;	
			default: 
				throw UnexpectedValueException(antwortStatus, aCode);
			};
		}
	}


	return true;
}



string PushNotifier::getToken()
{
	return this->token;
}

