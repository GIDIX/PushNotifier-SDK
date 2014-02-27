# PushNotifier Java (v1.1)

## How do I get started?

1. Download PushNotifier-SDK.jar
2. Copy the jar-File into your project's `lib`-folder (create it if it doesn't exist).
3. Add the jar-File to your Build Path.
4. Import these packages:
	- com.gidix.pushNotifier.*
	- com.gidix.pushNotifier.exceptions.*
5. Add to your project these lines:
	- `PushNotifier.setAPIToken("your_api_token_here");`
	- `PushNotifier.setAppPackage("com.example.app");`

## Notes

- For use in Android apps you will need to create an `AsyncTask` because Android does not allow network operations in its main thread.

## Javadoc

You can either clone this repository and view the docs locally or you can [view them online](http://a.pushnotifier.de/1/Java/).

## Logging in

To log in a user simply create an object of `PushNotifier` via one of these methods:

```java
PushNotifier pn = PushNotifier.instanceByCredentials("username", "apiKey/password");
```

or

```java
PushNotifier pn = PushNotifier.instanceByToken("username", "token");
```	

## Retrieving devices

To send push notifications you need know about the user's devices. You can fetch a list of all available devices this way:

```java
Device[] devices = pn.getDevices();
```
	
### Properties of `Device`

[View all properties of `Device` ›](http://a.pushnotifier.de/1/Java/com/gidix/pushNotifier/Device.html)

## Pushing to devices

Finally the fun part - pushing content to a user's device/s:

```java
Device[] devices = new Device[] { ... };
PushMessage pm = PushMessage.newMessage(devices, "Example");
pn.sendToDevice(pm);
```
	
## Tracing errors

Sometimes errors happen. This can be due to a changed appToken, an invalid API-Token or other things. To get an idea of that was wrong the SDK knows every error code. You can compare an Exception's error code with the ones on `PushNotifier.ErrorCodes`:

```java
if (e.getErrorCode() == PushNotifier.ErrorCodes.DEVICE_NOT_FOUND) {
	// ...
}
```
	
[View all error codes ›](http://a.pushnotifier.de/1/Java/com/gidix/pushNotifier/PushNotifier.ErrorCodes.html#field_summary)

You can also call this method to get the output of every API call:

```java
pn.setDebugging(true);
```

## Credits
* JSON by [Google Gson](https://code.google.com/p/google-gson/)