#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <curl/curl.h>
#include "cJSON.h"

int fun = 0;
bool loop = false;
int opt = -1;
int imp;

void display_choice()
{
    printf("Select the genre of Joke:\n");
    printf("1. Any\n");
    printf("2. Programming\n");
    printf("3. Pun\n");
    printf("4. Dark\n");
    printf("5. Spooky\n");
}

void display_flags()
{
    printf("Select the sub-categries: \n");
    printf("1. NSFW\n");
    printf("2. Religious\n");
    printf("3. Political\n");
    printf("4. Racist\n");
    printf("5. Sexist\n");
    printf("6. Explicit\n");
}

void print_joke(cJSON *json)
{
    char pause;
    loop = true;
    printf("\nJoke:\n");
    cJSON *type = cJSON_GetObjectItem(json, "type");
    if (strcmp(type->valuestring, "twopart") == 0)
    {
        cJSON *line1 = cJSON_GetObjectItem(json, "setup");
        cJSON *line2 = cJSON_GetObjectItem(json, "delivery");
        printf("%s", line1->valuestring);
        scanf("%c", &pause);
        if (pause == '\n')
            printf("%s\n", line2->valuestring);
    }
    else
    {
        cJSON *line = cJSON_GetObjectItem(json, "joke");
        printf("%s\n", line->valuestring);
    }
}

void joke_extract(char *buffer)
{
    cJSON *json = cJSON_Parse(buffer);
    if (json == NULL)
        printf("Error Parsing JSON\n");

    cJSON *genre = cJSON_GetObjectItem(json, "category");
    cJSON *safety = cJSON_GetObjectItem(json, "safe");
    if (!fun)
    {
        if ((strcmp(genre->valuestring, "Any") == 0) ? cJSON_IsTrue(safety) : 1)
        {
            print_joke(json);
        }
    }
    else
    {
        cJSON *subcategory = cJSON_GetObjectItem(json, "flags");
        bool valid_input = false;
        int selection;
        if (opt == -1)
        {
            printf("\n");
            display_flags();
            printf("Enter the selection: ");
        }
        while (!valid_input)
        {
            valid_input = true;
            if (opt == -1)
            {
                scanf("%d", &selection);
                opt = selection;
                fflush(stdin);
            }
            if (opt == 1)
            {
                cJSON *nsfw = cJSON_GetObjectItem(subcategory, "nsfw");
                if (cJSON_IsTrue(nsfw))
                    print_joke(json);
            }
            else if (opt == 2)
            {
                cJSON *religious = cJSON_GetObjectItem(subcategory, "religious");
                if (cJSON_IsTrue(religious))
                    print_joke(json);
            }
            else if (opt == 3)
            {
                cJSON *political = cJSON_GetObjectItem(subcategory, "political");
                if (cJSON_IsTrue(political))
                    print_joke(json);
            }
            else if (opt == 4)
            {
                cJSON *racist = cJSON_GetObjectItem(subcategory, "racist");
                if (cJSON_IsTrue(racist))
                    print_joke(json);
            }
            else if (opt == 5)
            {
                cJSON *sexist = cJSON_GetObjectItem(subcategory, "sexist");
                if (cJSON_IsTrue(sexist))
                    print_joke(json);
            }
            else if (opt == 6)
            {
                cJSON *explicit = cJSON_GetObjectItem(subcategory, "explicit");
                if (cJSON_IsTrue(explicit))
                    print_joke(json);
            }
            else
            {
                printf("Invalid Input! Enter Again: ");
                valid_input = false;
                opt = -1;
            }
        }
    }
}

size_t write_callback(char *buffer, size_t itemsize, size_t nitems, char *ignorethis)
{
    size_t bytes = itemsize * nitems;
    joke_extract(buffer);
    return bytes;
}

int main(int argc, char *argv[])
{
    system("cls");
    if (!strcmp(argv[1], "friend"))
        imp = 1;
    else if (!strcmp(argv[1], "fun"))
        imp = 2;
    CURL *curl = curl_easy_init();
    if (!curl)
    {
        fprintf(stderr, "init failed\n");
        return EXIT_FAILURE;
    }
    char *base_url = "https://v2.jokeapi.dev/joke/";
    char category[20];
    char *blacklist = "?blacklistFlags=nsfw,religious,racist,sexist,explicit";
    int choice;
    bool valid_selection = false;
    display_choice();
    printf("Make Your selection: ");
    while (!valid_selection)
    {
        valid_selection = true;
        scanf("%d", &choice);
        if (choice == 1)
            strcpy(category, "Any");
        else if (choice == 2)
            strcpy(category, "Programming");
        else if (choice == 3)
            strcpy(category, "Pun");
        else if (choice == 4)
            strcpy(category, "Dark");
        else if (choice == 5)
            strcpy(category, "Spooky");
        else if (choice == 69)
        {
            strcpy(category, "Any");
            fun++;
        }
        else
        {
            printf("Enter a valid selection: ");
            valid_selection = false;
        }
    }
    fflush(stdin);
    size_t url_length = strlen(base_url) + strlen(category) + ((!fun) ? strlen(blacklist) : 0) + 1;
    char *url = (char *)malloc(url_length);
    if (url == NULL)
    {
        fprintf(stderr, "Memory Allocation failed\n");
        curl_easy_cleanup(curl);
        return EXIT_FAILURE;
    }

    if (fun)
        snprintf(url, url_length, "%s%s", base_url, category);
    else
        snprintf(url, url_length, "%s%s%s", base_url, category, blacklist);

    while (!loop)
    {
        curl_easy_setopt(curl, CURLOPT_URL, url);
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L);
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 0L);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);

        CURLcode result = curl_easy_perform(curl);
        if (result != CURLE_OK)
        {
            fprintf(stderr, "Download Problem: %s\n", curl_easy_strerror(result));
            break;
        }
    }
    curl_easy_cleanup(curl);
    free(url);
    return EXIT_SUCCESS;
    return 0;
}
