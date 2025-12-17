#include <stdio.h>
#include <curl/curl.h>

int main()
{
    CURL *curl;
    CURLcode res;
    curl = curl_easy_init();

    if (curl)
    {
        curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "GET");
        curl_easy_setopt(curl, CURLOPT_URL, "https://library-api.postmanlabs.com/books/29cd820f-82f9-4b45-a7f4-0924111b5b89");
        curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
        curl_easy_setopt(curl, CURLOPT_DEFAULT_PROTOCOL, "https");
        struct curl_slist *headers = NULL;
        headers = curl_slist_append(headers, "api-key: postmanrulz");
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
        res = curl_easy_perform(curl);
        curl_slist_free_all(headers);
    }

    curl_easy_cleanup(curl);
    return 0;
}