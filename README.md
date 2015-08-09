# Raspberry Pi Weather Station

Gets data from a Temperature/Humidity Sensor and uploads them to data.sparkfun.com

## Dependencies
* WiringPi
* libcurl
* Create a free data stream at data.spark.fun.com and add your private and public keys to data-sparkfun-post.cpp

http://wiringpi.com/download-and-install/

sudo apt-get update && apt-get install libcurl4-openssl-dev 

## Compile
run make

## Run
sudo ./rpiweather

Credits to:
http://www.disk91.com/2013/technology/hardware/oregon-scientific-sensors-with-raspberry-pi/

Clone of https://github.com/billygr/RPI_Oregon
