#include <cjson/cJSON.h>
#include <ctype.h>
#include <curl/curl.h>
#include <locale.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

char city_name[50];

void convertUnixTimestamp(time_t timestamp, int timezone_offset) {
	timestamp += timezone_offset;
	struct tm *time_info = gmtime(&timestamp);
	printf("%02d:%02d:%02d\n", time_info->tm_hour, time_info->tm_min,
		   time_info->tm_sec);
}

void handle_data(char *buffer)
{
	cJSON *json = cJSON_Parse(buffer);

	if (json == NULL) printf("Error parsing JSON\n");

	cJSON *data = cJSON_GetObjectItem(json, "main");
	if (cJSON_IsObject(data)) {
		setlocale(LC_ALL, "");

		cJSON *temperature = cJSON_GetObjectItem(data, "temp");
		cJSON *feel = cJSON_GetObjectItem(data, "feels_like");
		cJSON *min_temp = cJSON_GetObjectItem(data, "temp_min");
		cJSON *max_temp = cJSON_GetObjectItem(data, "temp_max");
		cJSON *pressure = cJSON_GetObjectItem(data, "pressure");
		cJSON *humid = cJSON_GetObjectItem(data, "humidity");

		printf("\nTemperature: %.2f \u00B0C\n", temperature->valuedouble);
		printf("It feels like: %.2f \u00B0C\n", feel->valuedouble);
		printf("Minimum Tempreature: %.2f \u00B0C\n", min_temp->valuedouble);
		printf("Maximum Tempreature: %.2f \u00B0C\n", max_temp->valuedouble);
		printf("\nPressure: %d mBar\n", pressure->valueint);
		printf("Humidity: %d %%\n", humid->valueint);
	}

	cJSON *data2 = cJSON_GetObjectItem(json, "weather");
	if (cJSON_IsArray(data2)) {
		cJSON *weather_item = cJSON_GetArrayItem(data2, 0);
		cJSON *condition = cJSON_GetObjectItem(weather_item, "description");
		if (cJSON_IsString(condition))
			printf("Weather Condition: %s\n", condition->valuestring);
	}

	cJSON *data4 = cJSON_GetObjectItem(json, "wind");
	if (cJSON_IsObject(data4)) {
		cJSON *wind_speed = cJSON_GetObjectItem(data4, "speed");
		printf("Wind Speed: %.2f kph\n", wind_speed->valuedouble);
	}

	cJSON *timezone = cJSON_GetObjectItem(json, "timezone");
	cJSON *data3 = cJSON_GetObjectItem(json, "sys");
	if (cJSON_IsObject(data3)) {
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

	cJSON_Delete(json);
}

size_t write_callback(char *buffer, size_t itemsize, size_t nitems, void *ignorethis) {
	size_t bytes = itemsize * nitems;

	if (bytes < 50)
		printf("%s: City not found!\n", city_name);
	else {
		printf("Weather Details of %s:-\n", city_name);
		handle_data(buffer);
	}

	return bytes;
}

int main(int argc, char *argv[]) {
	if (argc == 1) {
		printf("No City Name Entered\n");
		return 0;
	}

	if (strcmp(argv[1], "--help") == 0) {
		printf("Weather CLI - Get current weather information\n\n");
		printf("Usage:\n");
		printf("  weather [CITY1] [CITY2]...\n");
		printf("  weather --help\n\n");
		printf("Description:\n");
		printf(
			"  Fetches current weather data for specified cities using "
			"OpenWeatherMap API.\n");
		printf(
			"  Supports multiple cities in one command. Data includes "
			"temperature, humidity,\n");
		printf("  pressure, wind speed, and sunrise/sunset times.\n\n");
		printf("Arguments:\n");
		printf(
			"  CITY\t\tName of city to query (supports multiple "
			"space-separated "
			"cities)\n\n");
		printf("Options:\n");
		printf("  --help\tShow this help message and exit\n\n");
		printf("Examples:\n");
		printf("  weather London\n");
		printf("  weather \"New York\" Tokyo Paris\n");
		printf("  weather Mumbai --help\n\n");
		printf("Notes:\n");
		printf("  - Requires internet connection\n");
		printf("  - City names with spaces should be quoted\n");
		printf("  - Temperature values are shown in Celsius\n");
		return 0;
	}
	for (int i = 1; i < argc; i++) {
		if (i != 1)
			printf("\n-----------------------------------------------------\n");
		CURL *curl = curl_easy_init();

		if (!curl) {
			fprintf(stderr, "init failed\n");
			return EXIT_FAILURE;
		}
		char *link = "http://api.openweathermap.org/data/2.5/weather?q=";
		char *api_key = "&appid=e6d43eafcf69f246c6180b997c652ea7&units=metric";

		strcpy(city_name, argv[i]);
		city_name[0] = toupper(city_name[0]);

		size_t url_length =
			strlen(link) + strlen(city_name) + strlen(api_key) + 1;
		char *url = (char *)malloc(url_length);
		if (url == NULL) {
			fprintf(stderr, "Memory allocation failed\n");
			curl_easy_cleanup(curl);
			return EXIT_FAILURE;
		}
		snprintf(url, url_length, "%s%s%s", link, city_name, api_key);

		curl_easy_setopt(curl, CURLOPT_URL, url);
		curl_easy_setopt( curl, CURLOPT_WRITEFUNCTION, write_callback);

		CURLcode result = curl_easy_perform(curl);
		if (result != CURLE_OK)
			fprintf(stderr, "download problem: %s\n", curl_easy_strerror(result));

		curl_easy_cleanup(curl);
		free(url);
	}
	return EXIT_SUCCESS;
	return 0;
}
