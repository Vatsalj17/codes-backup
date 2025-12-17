CC=gcc
CFLAGS=-Wall -g
BINS=randtest.out shim.so fireshim.so

all: $(BINS)

%.so: %.c
	$(CC) $(CFLAGS) -shared -fPIC -o $@ $^ -ldl

%.out: %.c
	$(CC) $(CFLAGS) -o $@ $^

clean:
	rm $(BINS)
