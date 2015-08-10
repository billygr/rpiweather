#include <stdio.h>
#include <string.h>
#include <curl/curl.h>

int data_sparkfun_post(float temperature, float humidity)
{
	CURL *curl;
	CURLcode res;

	const char *publicKey = "YOURPUBLICKEY";
	const char *privateKey= "YOURPRIVATEKEY";

	char data_sparkfun_url[128];
	char data_sparkfun_postdata[128];
	char header[64];

	char temperature_string[16];
	char humidity_string[16];

	snprintf(temperature_string, 6, "%f", temperature);
	printf("Temperature: %s\r\n", temperature_string);
	
	snprintf(humidity_string, 6, "%f", humidity);
	printf("Humidity: %s\r\n", humidity_string);

	strcpy(data_sparkfun_url, "http://data.sparkfun.com/input/");
	strcat(data_sparkfun_url, publicKey);

	strcpy(header, "Phant-Private-Key: ");
	strcat(header, privateKey);

	strcpy(data_sparkfun_postdata, "temperature=");
	strcat(data_sparkfun_postdata, temperature_string);
	strcat(data_sparkfun_postdata, "&humidity=");
	strcat(data_sparkfun_postdata, humidity_string);

	/* In windows, this will init the winsock stuff */
	curl_global_init(CURL_GLOBAL_ALL);

	/* get a curl handle */
	curl = curl_easy_init();
	if (curl) {
		struct curl_slist *chunk = NULL;

		curl_easy_setopt(curl, CURLOPT_URL, data_sparkfun_url);
		chunk = curl_slist_append(chunk, header);
		curl_easy_setopt(curl, CURLOPT_POSTFIELDS,
				 data_sparkfun_postdata);

		/* set our custom set of headers */
		res = curl_easy_setopt(curl, CURLOPT_HTTPHEADER, chunk);

		/* Perform the request, res will get the return code */
		res = curl_easy_perform(curl);

		/* Check for errors */
		if (res != CURLE_OK)
			fprintf(stderr, " curl_easy_perform()failed:%s \n",
				curl_easy_strerror(res));

		/* always cleanup */
		curl_easy_cleanup(curl);
	}
	curl_global_cleanup();
	return 0;
}
