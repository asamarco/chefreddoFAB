# chefreddoFAB
========================

*chefreddoFAB* alternatively known as *checaldoFAB* is an enviromental monitor (temperature, humidity, pressure) originally designed for the [poliFAB](https://polifab.polimi.it) cleanroom. It is based on sensor BME280, arduino, [arduino_exporter](https://github.com/Clivern/arduino_exporter), prometheus and grafana.

![screenshot](https://github.com/asamarco/chefreddoFAB/assets/5273092/21c8a213-51a5-44a8-9ecf-6e0c62afcf45)

====

## Usage

* Arduino code is in the Arduino folder.
* Arduino_exporter runs locally, it has to be installed with `pip install arduino_exporter`
* `arduino_exporter server run -s COM1 -p 8000 -b 115200` (windows)
* `arduino_exporter server run -s /dev/ttyUSB0 -p 8000 -b 115200` (linux)
* Prometheus and grafana run in docker, configuration files are in the relative subfolders.
