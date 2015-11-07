# Raspberry Pi Weather Station

Gets data from a 433 MHz Temperature/Humidity Sensor and uploads them to data.sparkfun.com and io.adafruit.com

Google Chart library creates the graphs

Project Web Site: http://www.billy.gr/raspberry-pi-weather-station

## Dependencies
* WiringPi
* libcurl
* Create a free data stream at data.sparkfun.com (fields:temperature,humidity,heatindex,dewpoint) and add your private and public keys to data-sparkfun-post.cpp

http://wiringpi.com/download-and-install/

sudo apt-get update && apt-get install libcurl4-openssl-dev 

## Compile
run make (or make debug for more debugging output)

## Run
sudo ./rpiweather

#Credits
http://www.disk91.com/2013/technology/hardware/oregon-scientific-sensors-with-raspberry-pi/

Clone of https://github.com/billygr/RPI_Oregon
