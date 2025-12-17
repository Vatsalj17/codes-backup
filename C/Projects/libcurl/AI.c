#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>
#include <cjson/cJSON.h>

size_t write_callback(void *ptr, size_t size, size_t nmemb, void *userdata)
{
    size_t total_size = size * nmemb;
    strncat((char *)userdata, (char *)ptr, total_size);
    return total_size;
}

int main()
{
    CURL *curl;
    CURLcode res;

    const char *base_url = "https://api.aimlapi.com/v1";
    const char *api_key = "f5294a1162324d4ba8514846c3978b80"; 
    const char *system_prompt = "You are a travel agent. Be descriptive and helpful.";
    const char *user_prompt = "Tell me about San Francisco";

    cJSON *root = cJSON_CreateObject();
    cJSON_AddStringToObject(root, "model", "mistralai/Mistral-7B-Instruct-v0.2");
    cJSON *messages = cJSON_CreateArray();
    cJSON *system_message = cJSON_CreateObject();
    cJSON_AddStringToObject(system_message, "role", "system");
    cJSON_AddStringToObject(system_message, "content", system_prompt);
    cJSON_AddItemToArray(messages, system_message);

    cJSON *user_message = cJSON_CreateObject();
    cJSON_AddStringToObject(user_message, "role", "user");
    cJSON_AddStringToObject(user_message, "content", user_prompt);
    cJSON_AddItemToArray(messages, user_message);

    cJSON_AddItemToObject(root, "messages", messages);
    cJSON_AddNumberToObject(root, "temperature", 0.7);
    cJSON_AddNumberToObject(root, "max_tokens", 256);

    char *post_data = cJSON_Print(root);

    curl_global_init(CURL_GLOBAL_DEFAULT);
    curl = curl_easy_init();

    if (curl)
    {
        char response[4096] = {0}; 

        char url[256];
        snprintf(url, sizeof(url), "%s/chat/completions", base_url);

        curl_easy_setopt(curl, CURLOPT_URL, url);
        curl_easy_setopt(curl, CURLOPT_POST, 1L);
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, post_data);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L);
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 0L);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, response);

        struct curl_slist *headers = NULL;
        headers = curl_slist_append(headers, "Content-Type: application/json");
        char auth_header[128];
        snprintf(auth_header, sizeof(auth_header), "Authorization: Bearer %s", api_key);
        headers = curl_slist_append(headers, auth_header);
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);

        res = curl_easy_perform(curl);
        if (res != CURLE_OK)
        {
            fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
        }
        else
        {
            printf("Raw JSON Response:\n%s\n", response);
        }

        curl_slist_free_all(headers);
        curl_easy_cleanup(curl);
    }

    curl_global_cleanup();

    return 0;
}
