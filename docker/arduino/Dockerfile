FROM debian:buster

# https://arduino.github.io/arduino-cli/0.19/getting-started/#add-libraries

ARG arduino_cli_version
RUN apt-get update
RUN apt-get install -y curl make
RUN curl -fsSL https://raw.githubusercontent.com/arduino/arduino-cli/master/install.sh | sh -s $arduino_cli_version
