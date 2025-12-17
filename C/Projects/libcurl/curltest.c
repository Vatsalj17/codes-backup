#include <stdio.h>
#include <curl/curl.h>

int main()
{
    CURL *curl;
    CURLcode res;

    printf("Initializing libcurl...\n");
    // Initialize libcurl
    curl_global_init(CURL_GLOBAL_DEFAULT);

    // Attempt to initialize a CURL handle
    curl = curl_easy_init();
    if (!curl)
    {
        fprintf(stderr, "Error: Failed to initialize CURL.\n");
        return 1;
    }

    // Setting up the URL
    const char *url = "https://www.example.com";
    printf("Setting URL: %s\n", url);

    // Set the URL for the HTTP request
    curl_easy_setopt(curl, CURLOPT_URL, url);
    curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L); // Enable verbose output for debugging

    // Perform the HTTP request
    printf("Performing the request...\n");
    res = curl_easy_perform(curl);

    // Check for errors
    if (res != CURLE_OK)
    {
        fprintf(stderr, "Error during request: %s\n", curl_easy_strerror(res));
    }
    else
    {
        printf("Request successful!\n");
    }

    // Cleanup the curl object
    curl_easy_cleanup(curl);

    // Cleanup the global libcurl environment
    curl_global_cleanup();

    return 0;
}
