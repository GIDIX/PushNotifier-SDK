<?php
	namespace GX\PushNotifier;

	class Device {
		private $id;
		private $title;
		private $model;

		public static function fromAPIresult(array $result) {
			return new self(
				$result['id'],
				$result['title'],
				$result['model']
			);
		}

		public function __construct($id, $title, $model) {
			$this->id = $id;
			$this->title = $title;
			$this->model = $model;
		}

		public function getID() {
			return $this->id;
		}

		public function getTitle() {
			return $this->title;
		}

		public function getModel() {
			return $this->model;
		}
	}
?>