<?php
	namespace GX\PushNotifier;

	class PushMessage {
		private $devices = array();
		private $type;
		private $content;
		private $hiddenURL;

		private function __construct(array $devices, $type, $content, $hiddenURL) {
			$this->devices = $devices;
			$this->type = $type;
			$this->content = $content;
			$this->hiddenURL = $hiddenURL;
		}

		/**
		 * Create a new PushMessage of type MESSAGE.
		 * 
		 * @param 	array 	$devices
		 * @param 	string 	$content
		 * 
		 * @return 	PushMessage
		 */
		public static function newMessage(array $devices, $content) {
			return new self($devices, PushNotifier::TYPE_MESSAGE, $content, null);
		}

		/**
		 * Create a new PushMessage of type URL.
		 * 
		 * @param 	array 	$devices
		 * @param 	string 	$URL
		 * 
		 * @return 	PushMessage
		 */
		public static function newURL(array $devices, $URL) {
			return new self($devices, PushNotifier::TYPE_URL, $URL, null);
		}

		/**
		 * Create a new PushMessage of type HIDDENURL.
		 * 
		 * @param 	array 	$devices
		 * @param 	string 	$content
		 * @param 	string 	$URL
		 * 
		 * @return 	PushMessage
		 */
		public static function newHiddenURL(array $devices, $content, $URL) {
			return new self($devices, PushNotifier::TYPE_HIDDENURL, $content, $URL);
		}

		/**
		 * Get type of message.
		 * Use this to match against one of the PushNotifier.TYPE_* constants.
		 * 
		 * @return 	string
		 */
		public function getType() {
			return $this->type;
		}

		/**
		 * Get content of message.
		 * In case of type MESSAGE or HIDDENURL, this is the message.
		 * In case of type URL, this is the URL.
		 * 
		 * @return 	string
		 */
		public function getContent() {
			return $this->content;
		}

		/**
		 * Get hiddenURL of message.
		 * Only used when type is HIDDENURL.
		 * 
		 * @return 	string
		 */
		public function getHiddenURL() {
			return $this->hiddenURL;
		}

		/**
		 * Add a device for this message to be sent to.
		 * 
		 * @param 	Device 	$d
		 */
		public function addDevice(Device $d) {
			$this->devices[$d->getID()] = $d;
		}

		/**
		 * Remove a device based on its device ID.
		 * 
		 * @param 	int 	$deviceID
		 */
		public function removeDevice($deviceID) {
			if (isset($this->devices[$deviceID])) unset($this->devices[$deviceID]);
		}

		/**
		 * Get all devices this message should be pushed to.
		 * 
		 * @return 	array
		 */
		public function getDevices() {
			return $this->devices;
		}
	}
?>