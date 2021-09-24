compile: core vendor
	arduino-cli compile --fqbn arduino:samd:nano_33_iot environment

core:
	arduino-cli core update-index
	arduino-cli core install arduino:samd

vendor:
	arduino-cli lib install "Adafruit GFX Library"@1.10.2
	arduino-cli lib install "Adafruit RA8875"@1.4.0
	arduino-cli lib install "Adafruit Unified Sensor"@1.1.4
	arduino-cli lib install "Adafruit BMP3XX Library"@1.1.0
