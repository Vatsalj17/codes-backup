CC=gcc
CFLAGS=-g -Wall
OBJS=shared_memory.o
TARGET=writeshmem.out readshmem.out destroyshmem.out

all: $(TARGET)

%.out: %.o $(OBJS)
	$(CC) $(CFLAGS) $< $(OBJS) -o $@

%.o: %.c %.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)
