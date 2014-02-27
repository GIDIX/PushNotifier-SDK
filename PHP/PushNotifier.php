<?php
	namespace GX\PushNotifier;

	/**
	 *	PushNotifier API class
	 *	@author 	GIDIX
	 *	@version 	1.0
	 *	@since 		January 27, 2014
	 *	@copyright	2014 GIDIX
	 */
	class PushNotifier {
		const TYPE_MESSAGE = "MESSAGE";
		const TYPE_URL = "URL";
		const TYPE_HIDDENURL = "HIDDENURL";

		const API_TOKEN = "YOUR_API_TOKEN";
		const APP_PACKAGE = "YOUR_APP_PACKAGE";
		const USER_AGENT = "PushNotifier-PHP/1.0";

		const URL_LOGIN = "http://a.pushnotifier.de/1/login/";
		const URL_CHECK_TOKEN = "http://a.pushnotifier.de/1/checkToken/";
		const URL_GET_DEVICES = "http://a.pushnotifier.de/1/getDevices/";
		const URL_SEND_TO_DEVICE = "http://a.pushnotifier.de/1/sendToDevice/";

		private $debug = false; // Use this to trace the APIs responses.

		/**
		 *	Username of the user
		 *
		 *	@var 		string
		 */
		private $username;

		/**
		 *	Token of the user
		 *
		 *	@var 		string
		 */
		private $token;

		/**
		 *	cURL handler
		 *
		 *	@var 		resource
		 */
		private $ch;

		/**
		 *	Constructor
		 *
		 *	Construct PushNotifier based on username and apiKey/token.
		 *	If you want to log in a user with its token instead of apiKey just set apiKey to null.
		 *
		 *	@param 		string 	username
		 *	@param 		string 	apiKey
		 */
		public function __construct($username, $apiKey = null, $token = null) {
			$this->ch = curl_init();
			$this->username = $username;

			if (is_null($token)) {
				$json = $this->call(self::URL_LOGIN, array(
					'apiToken'	=>	self::API_TOKEN,
					'username'	=>	$username,
					'password'	=>	$apiKey
				));

				if ($json['status'] != 'ok') {
					throw new LoginFailedException($json['status'], $json['code']);
				}

				$this->token = $json['appToken'];
			} else {
				$this->token = $token;
			}
		}

		public function __destruct() {
			curl_close($this->ch);
		}

		/**
		 *	Get token of user
		 *	
		 *	@return 	string 	token of the user
		 */
		public function getToken() {
			return $this->token;
		}

		/**
	 	 *	Get a user's devices
	 	 *
	 	 *	@return 	array
		 */
		public function getDevices() {
			$json = $this->call(self::URL_GET_DEVICES, array(
				'apiToken'	=>	self::API_TOKEN,
				'appToken'	=>	$this->token
			));

			$devices = array();

			foreach ($json['devices'] as $d) {
				$devices[] = Device::fromAPIresult($d);
			}

			return $devices;
		}

		/**
		 *	Push something to one or more devices.
		 *
		 *	@param 		PushMessage	$m
		 */
		public function sendToDevice(PushMessage $m) {
			foreach ($m->getDevices() as $d) {
				$json = $this->call(self::URL_SEND_TO_DEVICE, array(
					'apiToken'	=>	self::API_TOKEN,
					'appToken'	=>	$this->token,
					'app'		=>	self::APP_PACKAGE,
					'deviceID'	=>	$d instanceof Device ? $d->getID() : (int) $d,
					'type'		=>	$m->getType(),
					'content'	=>	$m->getContent(),
					'hiddenURL'	=>	$m->getHiddenURL()
				));

				if ($json['status'] != 'ok') {
					throw new PushFailedException($json['status'], $json['code']);
				}
			}
		}

		/**
		 *	Call the API
		 *	
		 *	@param 		string 	The URL to call.
		 *	@param 		array 	POST-params
		 *	@param 		string 	Request type, either POST or GET
		 *
		 *	@return 	array 	json response
		 */
		private function call($url, array $params, $method = 'POST') {
			curl_setopt_array($this->ch, array(
				CURLOPT_URL				=>	$url,
				CURLOPT_USERAGENT		=>	self::USER_AGENT,
				CURLOPT_RETURNTRANSFER	=>	true,
				CURLOPT_CUSTOMREQUEST	=>	$method,
				CURLOPT_FOLLOWLOCATION	=>	true,
				CURLOPT_POSTFIELDS		=>	$params
			));

			$response = curl_exec($this->ch);
			$json = @json_decode($response, true);

			if ($this->debug) echo "=== API-result: ===\n" . print_r($json, true) . "\n";

			if (!is_array($json)) {
				throw new UnexpectedValueException('Invalid response: ' . $response, PNErrorCodes::INVALID_API_RESPONSE);
			}

			if (isset($json['code'])) {
				switch ($json['code']) {
					case PNErrorCodes::INVALID_API_TOKEN:
						throw new InvalidTokenException($json['status'], $json['code']);
						break;

					case PNErrorCodes::APP_TOKEN_MISSING:
					case PNErrorCodes::APP_TOKEN_UNKNOWN:
						throw new InvalidTokenException($json['status'], $json['code']);
						break;

					case PNErrorCodes::LIMIT_EXCEEDED:
						throw new LimitExceededException($json['status'], $json['code']);
						break;

				}
			}

			return $json;
		}
	}

	/*
	 *	ERROR CODES & EXCEPTIONS
	 *	========================
	 */

	class LoginFailedException extends \Exception {}
	class InvalidTokenException extends \Exception {}
	class PushFailedException extends \Exception {}
	class LimitExceededException extends \Exception {}

	class PNErrorCodes {
		// General
		const INVALID_API_TOKEN = 1;
		const APP_TOKEN_MISSING = 2;
		const APP_TOKEN_UNKNOWN = 3;
		const LIMIT_EXCEEDED = 9001; // Over 9000!

		// sendToDevice
		const APP_IDENTIFIER_MISSING = 4;
		const APP_INVALID = 5;
		const APP_PIRATING = 6;
		const DEVICE_ID_MISSING = 7;
		const DEVICE_NOT_FOUND = 8;
		const INVALID_TYPE = 9;
		const PUSH_INVALID_URL = 10;
	}
?>