<?php
	error_reporting(E_ALL);

	require 'PushNotifier.php';
	require 'Device.php';

	use \GX\PushNotifier\PushNotifier;

	$pushNotifier = new PushNotifier('username', 'apiKey');
	$devices = $pushNotifier->getDevices();

	$pushNotifier->sendToDevice('This is an example of how to use PushNotifier.', PushNotifier::TYPE_MESSAGE, $devices);
?>