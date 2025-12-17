CC=gcc
CFLAGS=-Wall -Wextra -std=c11 -g

all: heap

heap: main.c
	$(CC) $(CFLAGS) main.c -o heap

run: heap
	./heap

clean:
	rm -f heap
