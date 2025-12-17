/*
    Program to Check the Weather Data of Any City
    Author: Vatsal Jaiswal
    Description:A command-line program that retrieves and displays current weather details for a specified city.
                This program fetches temperature, humidity, wind speed, weather conditions, and sunrise/sunset times
                using data from the OpenWeatherMap API.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <time.h>
#include <curl/curl.h>
#include <cjson/cJSON.h>

// Function to print the intro
void print_intro()
{
    // system("clear");
    printf("             Welcome to the Weather Checker! \n");
    printf("------------------------------------------------------------\n");
    printf("This program shows you the current weather in any city.\n\n");
}

// Function to convert UNIX timestamp to Readable format
void convertUnixTimestamp(time_t timestamp, int timezone_offset)
{
    timestamp += timezone_offset;
    struct tm *time_info = gmtime(&timestamp);
    printf("%02d:%02d:%02d\n", time_info->tm_hour, time_info->tm_min, time_info->tm_sec);
}

// Function to parse and handle JSON data received from the weather API
void handle_data(char *buffer) // buffer - JSON data in string format
{
    cJSON *json = cJSON_Parse(buffer); // Parse JSON string to JSON

    if (json == NULL)
        printf("Error parsing JSON\n");

    // Access main weather details (temperature, pressure, humidity, etc.)
    cJSON *data = cJSON_GetObjectItem(json, "main");
    if (cJSON_IsObject(data))
    {
        setlocale(LC_ALL, ""); // Set locale for degree symbol display

        cJSON *temperature = cJSON_GetObjectItem(data, "temp");
        cJSON *feel = cJSON_GetObjectItem(data, "feels_like");
        cJSON *min_temp = cJSON_GetObjectItem(data, "temp_min");
        cJSON *max_temp = cJSON_GetObjectItem(data, "temp_max");
        cJSON *pressure = cJSON_GetObjectItem(data, "pressure");
        cJSON *humid = cJSON_GetObjectItem(data, "humidity");

        printf("Temperature: %.2f \260C\n", temperature->valuedouble);
        printf("It feels like: %.2f \260C\n", feel->valuedouble);
        printf("Minimum Tempreature: %.2f \260C\n", min_temp->valuedouble);
        printf("Maximum Tempreature: %.2f \260C\n", max_temp->valuedouble);
        printf("\nPressure: %d mBar\n", pressure->valueint);
        printf("Humidity: %d %%\n", humid->valueint);
    }

    // Access weather condition
    cJSON *data2 = cJSON_GetObjectItem(json, "weather");
    if (cJSON_IsArray(data2))
    {
        cJSON *weather_item = cJSON_GetArrayItem(data2, 0);
        cJSON *condition = cJSON_GetObjectItem(weather_item, "description");
        if (cJSON_IsString(condition))
            printf("Weather Condition: %s\n", condition->valuestring);
    }

    // Access wind speed data
    cJSON *data4 = cJSON_GetObjectItem(json, "wind");
    if (cJSON_IsObject(data4))
    {
        cJSON *wind_speed = cJSON_GetObjectItem(data4, "speed");
        printf("Wind Speed: %.2f kph\n", wind_speed->valuedouble);
    }

    // Access timezone and sun event data
    cJSON *timezone = cJSON_GetObjectItem(json, "timezone");
    cJSON *data3 = cJSON_GetObjectItem(json, "sys");
    if (cJSON_IsObject(data3))
    {
        cJSON *countrycode = cJSON_GetObjectItem(data3, "country");
        cJSON *sunrise = cJSON_GetObjectItem(data3, "sunrise");
        cJSON *sunset = cJSON_GetObjectItem(data3, "sunset");
        printf("\nSunrise: ");
        convertUnixTimestamp(sunrise->valueint, timezone->valueint);
        printf("Sunset: ");
        convertUnixTimestamp(sunset->valueint, timezone->valueint);
        if (cJSON_IsString(countrycode))
            printf("\nCountry Code: %s\n", countrycode->valuestring);
    }

    cJSON_Delete(json); // Clean up JSON object after use
}

// Callback function to handle data received from the server
size_t write_callback(char *buffer, size_t itemsize, size_t nitems, void *ignorethis)
{
    size_t bytes = itemsize * nitems; // Calculate total bytes in buffer

    // To check if user enters a valid city name
    if (bytes < 50)
        printf("City Not Found :( \nTry Again!");
    else
        handle_data(buffer);

    return bytes;
}

int main(void)
{
    print_intro(); // Display program intro

    // Initialize curl
    CURL *curl = curl_easy_init();

    if (!curl)
    {
        fprintf(stderr, "init failed\n");
        return EXIT_FAILURE;
    }

    // API endpoint and authentication key (replace `api_key` with your own key)
    char *link = "http://api.openweathermap.org/data/2.5/weather?q=";
    char *api_key = "&appid=e6d43eafcf69f246c6180b997c652ea7&units=metric";

    char city_name[50];
    printf("Enter the city name: ");
    scanf("%49s", city_name);

    printf("\n");

    // Generate full URL with city name and API key
    size_t url_length = strlen(link) + strlen(city_name) + strlen(api_key) + 1;
    char *url = (char *)malloc(url_length);
    if (url == NULL)
    {
        fprintf(stderr, "Memory allocation failed\n");
        curl_easy_cleanup(curl);
        return EXIT_FAILURE;
    }

    // Construct URL
    snprintf(url, url_length, "%s%s%s", link, city_name, api_key);

    curl_easy_setopt(curl, CURLOPT_URL, url);                      // Set URL for curl
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback); // Set Callback to handle recieved data

    // Perform HTTP GET request
    CURLcode result = curl_easy_perform(curl);
    if (result != CURLE_OK)
        fprintf(stderr, "download problem: %s\n", curl_easy_strerror(result));

    // Clean up resources
    curl_easy_cleanup(curl);
    free(url);
    return EXIT_SUCCESS;
}
