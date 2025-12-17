#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>
#include "cJSON.h"

void parsingJSON(char *buffer)
{
    cJSON *json = cJSON_Parse(buffer);
    cJSON *arr = cJSON_GetArrayItem(buffer, "data");
    cJSON *
}

size_t write_callback(char *buffer, size_t itemsize, size_t nitems, char *ignorethis)
{
    size_t bytes = nitems * itemsize;
    void parsingJSON(buffer);
    return bytes;
}

int main(void)
{
    CURL *hnd = curl_easy_init();

    curl_easy_setopt(hnd, CURLOPT_CUSTOMREQUEST, "GET");
    curl_easy_setopt(hnd, CURLOPT_URL, "http://geodb-free-service.wirefreethought.com/v1/geo/cities?countryIds=US&namePrefix=New&minPopulation=100000");

    curl_easy_setopt(hnd, CURLOPT_WRITEFUNCTION, write_callback);

    CURLcode ret = curl_easy_perform(hnd);
    curl_easy_cleanup(hnd);
    return EXIT_SUCCESS;
}