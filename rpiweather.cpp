#include "RCSwitch.h"
#include "RcOok.h"
#include "Sensor.h"
#include "data-sparkfun-post.h"
#include "io-adafruit-post.h"
#include "emoncms-post.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <time.h>

int main(int argc, char *argv[])
{
	int RXPIN = 2;
	int TXPIN = 0;
	time_t now_t;
	struct tm now;
	char message[100];

	float temperature;
	unsigned char humidity;
	int humidity_decimal;

	printf("RPIWeather Version: %s\n", VERSION);

	if (wiringPiSetup() == -1) {
		return 0;
		printf("failed wiring pi\n");
	}

	RCSwitch *rc = new RCSwitch(RXPIN, TXPIN);

	while (1) {
		if (rc->OokAvailable()) {

			rc->getOokCode(message);
// ISO 8601 timestamp
			time(&now_t);
			now = *localtime(&now_t);
			printf("%4d-%02d-%02dT%02d:%02d:%02dZ %s \r\n",
			       now.tm_year + 1900, now.tm_mon + 1, now.tm_mday,
			       now.tm_hour, now.tm_min, now.tm_sec, message);

			if (strstr(message, "CRES2") > 0) {
				//Remove the first 6 bytes CRES2 + space
				char *CRES2 = message + 6;
				//printf ("CRES2 %s\r\n",CRES2);
				if (CRES2[0] == '7' && CRES2[1] == '5') {

					int i;
					unsigned int bytearray[12];
					unsigned int str_len = strlen(CRES2);

					for (i = 0; i < (str_len / 2); i++) {
						sscanf(CRES2 + 2 * i, "%02x",
						       &bytearray[i]);
//                printf("bytearray %d: 0x%02x\n", i, bytearray[i]);
					}

					printf("Device ID: 0x%02x ",
					       bytearray[1] ^ bytearray[1] <<
					       1);
					if (bytearray[2] == 0xCE)
						printf("Battery OK ");
					if (bytearray[2] == 0x0E)
						printf("Battery LOW ");
					temperature =
					    ((bytearray[5] & 0x0F) * 10) +
					    ((bytearray[4] & 0xF0) >> 4) +
					    (bytearray[4] & 0x0F) * 0.1;
					humidity = bytearray[6];
					printf("Temperature: %.2f ",
					       temperature);
					printf("Humidity: %02x\r\n ", humidity);
					humidity_decimal=((humidity & 0xF0)>>4) * 10+(humidity & 0xF);
					io_adafruit_post("rpiweather-temperature",temperature);
					io_adafruit_post("rpiweather-humidity",humidity_decimal);
					emoncms_post("2","temperature",temperature);
					emoncms_post("2","humidity",humidity_decimal);
					data_sparkfun_post(temperature,humidity_decimal);
				}
			}
			if (strstr(message, "OSV3") > 0) {
				//Remove the first 5 bytes OSV3 + space
				char *OSV3 = message + 5;
				//printf("OSV3 %s\r\n", OSV3);
				if (OSV3[0] == '2' && OSV3[1] == 'A') {
					double watts;
					int i;
					unsigned int bytearray[12];
					uint8_t str_len = strlen(OSV3);

					for (i = 0; i < (str_len / 2); i++) {
						sscanf(OSV3 + 2 * i, "%02x",
						       &bytearray[i]);
//              printf("bytearray %d: 0x%02x\n", i, bytearray[i]);
					}

					watts =
					    ((bytearray[4] * 256) +
					     (bytearray[3] & 0xF0)) *
					    1.006196884;
					printf("OWL 119 Watts: %f\r\n ", watts);
					if (watts < 10000) {emoncms_post("1","power",watts);}

				}
			}
		}
		delay(1000);
	}

}
