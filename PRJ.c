#include <stdio.h>
#include <curl/curl.h>
#include "./cJSON/cJSON.h"
#include "./cJSON/cJSON.c"

int main(void)
{
    CURL *curl;
    CURLcode response;

    /* In windows, this will init the winsock stuff */
    curl_global_init(CURL_GLOBAL_ALL);

    // The object with data we are sending in.
    cJSON *dataObj;
    // Creating json object
    dataObj = cJSON_CreateObject();
    // Adding 1 number and 3 string to the object
    // Chosing first which object to add it to, keyname, value. Function depending on type
    cJSON_AddItemToObject(dataObj, "analysType", cJSON_CreateNumber(1));
    cJSON_AddItemToObject(dataObj, "data", cJSON_CreateString("AJHDGAHSJDHAS=="));
    cJSON_AddItemToObject(dataObj, "deviceId", cJSON_CreateString("EA:61:59:19:93:9"));
    cJSON_AddItemToObject(dataObj, "startTime", cJSON_CreateString("2020-12-21 13:03:12"));

    /* Get a curl handle */
    curl = curl_easy_init();

    if (curl)
    {
        /* Initialize struct that will hold auth token for request header */
        struct curl_slist *headers = NULL;

        /* Add request headers */
        headers = curl_slist_append(headers, "deviceId: EA:61:59:19:93:9");
        headers = curl_slist_append(headers, "Accept: application/json");
        headers = curl_slist_append(headers, "Content-Type: application/json");
        headers = curl_slist_append(headers, "charset: utf-8");

        /* Set request header */
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);

        // Setting the body with data
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, cJSON_Print(dataObj));

        /* Set URL for POST */
        curl_easy_setopt(curl, CURLOPT_URL, "http://localhost:80/test");

        /* Post the HTTP request, and store response in "response" variable */
        response = curl_easy_perform(curl);
        /* Check for errors */
        if (response != CURLE_OK)
            fprintf(stderr, "curl_easy_perform() failed: %s\n",
                    curl_easy_strerror(response));

        /* Cleanup */
        curl_easy_cleanup(curl);
        cJSON_Delete(dataObj);
    }
    curl_global_cleanup();

    return 0;
}