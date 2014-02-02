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
		PushNotifier yourInstanz("your username", "your password");

		//ckeck if token is valid
		if(yourInstanz.checkToken("your username"))
		{
			cout << "token is valid" << endl;
		}

		//vector of device
		vector<PushNotifier::device> devices;
		devices = yourInstanz.getDevices();

		//print all devices on the screen
		for(int i = 0; i < devices.size(); i++)
		{
			cout << "id: " << devices[i].id;
			cout << " title: " << devices[i].title;
			cout << " model: " << devices[i].model;
			cout << endl;
		}

		//send a message to the device with the id 17
		yourInstanz.sendToDevice("Example of a push notification.", TYPE_MESSAGE, 17);
	}
	catch(LoginFailedException& e)
	{
		//handle a LoginFailedException	
	}
	catch(InvalidTokenException& e)
	{
		//handle an InvalidTokenException
	}
	catch(PushFailedException& e)
	{
		//handle a PushFailedException 
	}
	catch(LimitExceededException& e)
	{
		//handle a LimitExceededException
	}
	catch(UnexpectedValueException& e)
	{
		//handle a UnexpectedValueException
	}


	return 0;
}
