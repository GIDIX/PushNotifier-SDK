# PushNotifier CPP

## How do I get started?

1. Copy the folder into your project.
2. Modify `API_TOKEN` and `APP_PACKAGE` in `pushnotifier.h`.
3. Compile it using `make`
4. Include `pushnotifier.h` and link `pushnotifier.a`.
5. You're ready to go.

## Notes

- Every call can throw these Exceptions:
	- `InvalidTokenException`
	- `LimitExceededException`


## Logging in

To log in a user simply create an object of `PushNotifier` passing in the username and the apiKey of the user. If you already have the user's appToken you can ignore the apiKey-paramter and use the appToken:

```cpp
PushNotifier yourInstance("username", "password");
```

**Note that this call can throw a ´LoginFailedException` if the login failed**

## Retrieving devices

To send push notifications you need know about the user's devices. You can fetch a list of all available devices this way:

```cpp
std::vector<PushNotifier::device> deviceList yourInstance.getDevices();
```

This will give you a vector of the type device containing all devices.

### Properties of `device`

- `device.id`: ID of the device.
- `device.title`: Title of the device.
- `device.model`: Model of the device. *Note that this can vary between devices of the same generation. For example: HTC One is both `ONE` and `M7`, depending on the carrier of the device.*

## Pushing to devices

Finally the fun part - pushing content to a user's device/s:

```cpp
unsigned int myDevice = 17; // ID of the device
yourInstance.sendToDevice("Example of a push notification.", PushNotifier::TYPE_MESSAGE, myDevice);
```
	
**Note that this call can throw a `PushFailedException` if the push was not successful.**

## Tracing errors

Sometimes errors happen. This can be due to a changed appToken, an invalid API-Token or other things. To get an idea of that was wrong the SDK knows every error code. You can compare an Exception's error code with the ones in `PNErrorCodes` in `pushnotifier.h`.


## Credits
* JSON by [jsmn](https://bitbucket.org/zserge/jsmn)
