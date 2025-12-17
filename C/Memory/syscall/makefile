CC=gcc
CFLAGS=-Wall -Wextra -g -lpthread
SRC=test.c heap.c
TARGET=test

all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) $(SRC) -o $(TARGET)

clean:
	rm $(TARGET)
