#include <iostream>
#include <string>
#include <vector>

#include "pushnotifier.h"

using namespace std;

int main(int argc, char **argv)
{
	try
	{
		//create a new PushNotifier object
		PushNotifier yourInstance("your username", "your password");

		//ckeck if token is valid
		if(yourInstance.checkToken("your username"))
		{
			cout << "token is valid" << endl;
		}

		//vector of device
		vector<PushNotifier::device> devices;
		devices = yourInstance.getDevices();

		//print all devices on the screen
		for(int i = 0; i < devices.size(); i++)
		{
			cout << "id: " << devices[i].id;
			cout << " title: " << devices[i].title;
			cout << " model: " << devices[i].model;
			cout << endl;
		}

		//send a message to all devices
		for (int i = 0; i < devices.size(); i++)
		{
			yourInstance.sendToDevice("Example of a push notification.", TYPE_MESSAGE, devices[i].id);
		}
	}
	catch(LoginFailedException& e)
	{
		//handle a LoginFailedException	
		cout << "Exception: Login failed" << endl;
	}
	catch(InvalidTokenException& e)
	{
		//handle an InvalidTokenException
		cout << "Exception: Invalid token" << endl;
	}
	catch(PushFailedException& e)
	{
		//handle a PushFailedException 
		cout << "Exception: Push to device(s) failed" << endl;
	}
	catch(LimitExceededException& e)
	{
		//handle a LimitExceededException
		cout << "Exception: Limit exceeded" << endl;
	}
	catch(UnexpectedValueException& e)
	{
		//handle a UnexpectedValueException
		cout << "Exception: Unexpected value" << endl;
	}


	return 0;


}
