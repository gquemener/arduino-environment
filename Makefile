compile: core vendor
	docker-compose run --rm arduino arduino-cli compile --fqbn arduino:samd:nano_33_iot environment

core:
	docker-compose run --rm arduino arduino-cli core update-index
	docker-compose run --rm arduino arduino-cli core install arduino:samd

vendor:
	docker-compose run --rm arduino arduino-cli lib install "Adafruit GFX Library"@1.10.2
	docker-compose run --rm arduino arduino-cli lib install "Adafruit RA8875"@1.4.0
	docker-compose run --rm arduino arduino-cli lib install "Adafruit Unified Sensor"@1.1.4
	docker-compose run --rm arduino arduino-cli lib install "Adafruit BMP3XX Library"@1.1.0
