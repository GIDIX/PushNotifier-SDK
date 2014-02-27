# PushNotifier PHP (v1.1)

## How do I get started?

1. Copy the folder into your project.
2. Include `PushNotifier.php` and `Device.php`.
3. At the top of your project write:
	- `use \GX\PushNotifier\PushNotifier;`
	- `use \GX\PushNotifier\PushMessage;`
4. Modify `API_TOKEN` and `APP_PACKAGE` in `PushNotifier.php`.
5. You're ready to go.

## Notes

- Every call can throw these Exceptions:
	- `InvalidTokenException`
	- `LimitExceededException`
- You can trace API responses by setting `$debug` in `PushNotifier.php`.


## Logging in

To log in a user simply create an object of `PushNotifier` passing in the username and the apiKey of the user:

```php
$pushNotifier = new PushNotifier('username', 'password');
```

If you already have the user's appToken you can ignore the apiKey-paramter and use the appToken:

```php
$pushNotifier = new PushNotifier('username', null, 'appToken');
```

**Note that this call can throw a `LoginFailedException` if the login failed**

## Retrieving devices

To send push notifications you need to know about the user's devices. You can fetch a list of all available devices this way:

```php
$devices = $pushNotifier->getDevices();
```

This will give you an array containing objects of `Device`.

### Properties of `Device`

- `$device->getID()`: ID of the device.
- `$device->getTitle()`: Title of the device.
- `$device->getModel()`: Model of the device. *Note that this can vary between devices of the same generation. For example: HTC One is both `ONE` and `M7`, depending on the carrier of the device.*

## Pushing to devices

Finally the fun part - pushing content to a user's device/s:

```php
$devices = array(...); // Array of devices
$pm = PushMessage::newMessage($devices, 'Example');
$pushNotifier->sendToDevice($pm);
```
	
**Note that this call can throw a `PushFailedException` if the push was not successful (for at least 1 device). When an exception is thrown the execution of further pushes is halted.**

## Tracing errors

Sometimes errors happen. This can be due to a changed appToken, an invalid API-Token or other things. To get an idea of that was wrong the SDK knows every error code. You can compare an Exception's error code with the ones in `PNErrorCodes` in `PushNotifier.php`.
