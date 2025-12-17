# Compiler and Linker
CC = gcc

# SDL Libraries
LIBS = -lmingw32 -lSDL2main -lSDL2

# Build Flags
CFLAGS = -I"C:/Users/vatsa/C/SDL/include"
LDFLAGS = -L"C:/Users/vatsa/C/SDL/lib"

# Target executable
TARGET = a.exe

# Sources
GAME_SOURCE = Game.c
COLOUR_SOURCE = Colours.c
SETUP_SOURCE = Setup.c
SCROLLING_SOURCE = Scrolling.c
ANIMATION_SOURCE = ScreenSaver.c
KEYBOARD_SOURCE = Keyboard.c
MUSIC_SOURCE = Audio.c

# Targets and their corresponding source files
Game: $(GAME_SOURCE)
	$(CC) $(CFLAGS) $(LDFLAGS) $(GAME_SOURCE) -o $(TARGET) $(LIBS) -lSDL2_image 

Keyboard: $(KEYBOARD_SOURCE)
	$(CC) $(CFLAGS) $(LDFLAGS) $(KEYBOARD_SOURCE) -o $(TARGET) $(LIBS) -lSDL2_image 

ScreenSaver: $(ANIMATION_SOURCE)
	$(CC) $(CFLAGS) $(LDFLAGS) $(ANIMATION_SOURCE) -o $(TARGET) $(LIBS) -lSDL2_image -lSDL2_mixer

Scrolling: $(SCROLLING_SOURCE)
	$(CC) $(CFLAGS) $(LDFLAGS) $(SCROLLING_SOURCE) -o $(TARGET) $(LIBS) -lSDL2_image 

Colours: $(COLOUR_SOURCE)
	$(CC) $(CFLAGS) $(LDFLAGS) $(COLOUR_SOURCE) -o $(TARGET) $(LIBS)

Audio: $(MUSIC_SOURCE)
	$(CC) $(CFLAGS) $(LDFLAGS) $(MUSIC_SOURCE) -o $(TARGET) $(LIBS) -lSDL2_mixer

Setup: $(SETUP_SOURCE)
	$(CC) $(CFLAGS) $(LDFLAGS) $(SETUP_SOURCE) -o $(TARGET) $(LIBS)

# Clean up
clean:
	del /f $(TARGET)
