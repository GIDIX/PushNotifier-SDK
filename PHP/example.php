<?php
	error_reporting(E_ALL);

	require 'PushNotifier.php';
	require 'PushMessage.php';
	require 'Device.php';

	use \GX\PushNotifier\PushNotifier;
	use \GX\PushNotifier\PushMessage;

	$pushNotifier = new PushNotifier('username', 'apiKey');
	$devices = $pushNotifier->getDevices();
	$pm = PushMessage::newMessage($devices, 'Example');
	$pushNotifier->sendToDevice($pm);
?>