#include <stdio.h>
#include <string.h>
#include <curl/curl.h>

int io_adafruit_post(char const *feedname, float feedvalue)
{
	CURL *curl;
	CURLcode res;

	const char *x_aio_key = "X-AIO-KEY";

	char io_adafruit_url[256];
	char io_adafruit_postdata[128];
	char header[64];

	char feedvalue_string[16];

	snprintf(feedvalue_string, 6, "%f", feedvalue);

#ifdef DEBUG
	printf("io_adafruit_post feedvalue: %s\r\n", feedvalue_string);
#endif

	strcpy(io_adafruit_url, "http://io.adafruit.com/api/feeds/");

	strcat(io_adafruit_url, feedname);
	strcat(io_adafruit_url, "/data/send/?");

	strcpy(header, "x-aio-key: ");
	strcat(header, x_aio_key);

	strcpy(io_adafruit_postdata, "value=");
	strcat(io_adafruit_postdata, feedvalue_string);

#ifdef DEBUG
	printf("io_adafruit_post %s%s", io_adafruit_url, io_adafruit_postdata);
#endif

	/* In windows, this will init the winsock stuff */
	curl_global_init(CURL_GLOBAL_ALL);

	/* get a curl handle */
	curl = curl_easy_init();
	if (curl) {
		struct curl_slist *chunk = NULL;

		curl_easy_setopt(curl, CURLOPT_URL, io_adafruit_url);

		chunk = curl_slist_append(chunk, header);

		curl_easy_setopt(curl, CURLOPT_POSTFIELDS,
				 io_adafruit_postdata);

		/* set our custom set of headers */
		res = curl_easy_setopt(curl, CURLOPT_HTTPHEADER, chunk);

		/* Perform the request, res will get the return code */
		res = curl_easy_perform(curl);

		/* Check for errors */
		if (res != CURLE_OK)
			fprintf(stderr,
				" io_adafruit_post curl_easy_perform() failed:%s \n",
				curl_easy_strerror(res));

		/* always cleanup */
		curl_easy_cleanup(curl);
	}
	curl_global_cleanup();
	return 0;
}
