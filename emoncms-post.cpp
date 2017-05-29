#include <stdio.h>
#include <string.h>
#include <curl/curl.h>

int emoncms_post(char const *node, char const *key, float nodevalue)
{
	CURL *curl;
	CURLcode res;

	const char *emoncms_api_key = "YOURAPIKEY";
	char emoncms_url[256]="YOURURL";

	char emoncms_postdata[128];
	char header[64];

	char nodevalue_string[16];

	snprintf(nodevalue_string, 6, "%f", nodevalue);

#ifdef DEBUG
	printf("emoncms_post node:key:value: %s:%s:%s\r\n", node,key,nodevalue_string);
#endif

	strcat(emoncms_url, "/input/post.json?node=");
	strcat(emoncms_url, node);
	strcat(emoncms_url, "&json={");
        strcat(emoncms_url, key);
        strcat(emoncms_url, ":");
	strcat(emoncms_url, nodevalue_string);
	strcat(emoncms_url, "}");
	strcat(emoncms_url, "&apikey=");
        strcat(emoncms_url, emoncms_api_key);

//FIXME
//	strcpy(header, "Authorization: Bearer ");
//	strcat(header, emoncms_api_key);

#ifdef DEBUG
	printf("emoncms_post %s%s\r\n", emoncms_url, emoncms_postdata);
#endif

	/* In windows, this will init the winsock stuff */
	curl_global_init(CURL_GLOBAL_ALL);

	/* get a curl handle */
	curl = curl_easy_init();
	if (curl) {
		struct curl_slist *chunk = NULL;

		curl_easy_setopt(curl, CURLOPT_URL, emoncms_url);

		chunk = curl_slist_append(chunk, header);

		curl_easy_setopt(curl, CURLOPT_POSTFIELDS,
				 emoncms_postdata);

		/* set our custom set of headers */
		res = curl_easy_setopt(curl, CURLOPT_HTTPHEADER, chunk);

		/* Perform the request, res will get the return code */
		res = curl_easy_perform(curl);

		/* Check for errors */
		if (res != CURLE_OK)
			fprintf(stderr,
				" emoncms_post curl_easy_perform() failed:%s \n",
				curl_easy_strerror(res));

		/* always cleanup */
		curl_easy_cleanup(curl);
	}
	curl_global_cleanup();
	return 0;
}
