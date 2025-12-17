#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>

// Callback function to handle the response body
size_t write_callback(void *ptr, size_t size, size_t nmemb, char *data)
{
    size_t total_size = size * nmemb;
    strncat(data, ptr, total_size); // Append the response to the data buffer
    return total_size;
}

int main(void)
{
    CURL *curl;
    CURLcode res;
    char response[4096] = ""; // Buffer to store the response

    curl = curl_easy_init();
    if (curl)
    {
        curl_easy_setopt(curl, CURLOPT_URL, "https://api.quotable.io/random");
        curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);

        // Enable verbose output to see what libcurl is doing
        curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L);

        // Force IPv4 only
        curl_easy_setopt(curl, CURLOPT_IPRESOLVE, CURL_IPRESOLVE_V4);

        // Set the write callback function to handle the response
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, response);

        // Perform the request
        res = curl_easy_perform(curl);

        // Check for errors and print the response
        if (res == CURLE_OK)
        {
            printf("Response: %s\n", response);
        }
        else
        {
            fprintf(stderr, "Error: %s\n", curl_easy_strerror(res));
        }

        // Clean up
        curl_easy_cleanup(curl);
    }
    else
    {
        fprintf(stderr, "Error: Failed to initialize curl\n");
    }

    return EXIT_SUCCESS;
}
