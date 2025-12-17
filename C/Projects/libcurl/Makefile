# Define variables
CC = gcc
#CFLAGS = -I"C:\curl-8.11.1_3-win64-mingw\include"
#LDFLAGS = -L"C:\curl-8.11.1_3-win64-mingw\lib" -lcurl
TARGET = a.exe
FOR_JSON = -lcjson
FOR_CURL = -lcurl
WEATHER_SOURCE = Weather.c
CURLTEST_SOURCE = curltest.c
LEARNCURL_SOURCE = Learncurl.c
POSTMAN_SOURCE = postman.c
JOKE_SOURCE = Joke.c
CITY_SOURCE = city_data.c
AI_SOURCE = AI.c
W_SOURCE = Weather_args.c

Weather: $(WEATHER_SOURCE)
	$(CC) $(WEATHER_SOURCE) -o Weather $(FOR_JSON) $(FOR_CURL) && ./Weather

Weathera: $(W_SOURCE)
	$(CC) $(W_SOURCE) -o Weather $(FOR_JSON) $(FOR_CURL) 

curltest: $(CURLTEST_SOURCE)
	$(CC) $(CURLTEST_SOURCE) -o $(TARGET) $(CFLAGS) $(LDFLAGS)

Learncurl: $(LEARNCURL_SOURCE)
	$(CC) $(LEARNCURL_SOURCE) -o $(TARGET) $(CFLAGS) $(LDFLAGS)

postman: $(POSTMAN_SOURCE)
	$(CC) $(POSTMAN_SOURCE) -o $(TARGET) $(CFLAGS) $(LDFLAGS)

Joke: $(JOKE_SOURCE)
	$(CC) $(JOKE_SOURCE) $(FOR_JSON) -o $(TARGET) $(CFLAGS) $(LDFLAGS)

city_data: $(CITY_SOURCE)
	$(CC) $(CITY_SOURCE) -o $(TARGET) $(CFLAGS) $(LDFLAGS)

AI: $(AI_SOURCE)
	$(CC) $(AI_SOURCE) -o ai $(FOR_JSON) $(FOR_CURL)

# Clean up the executable
clean:
	rm -f $(TARGET)
