CC= gcc
CFLAGS = -Wall -g
TARGET = graph.out
OBJS = main.o graph.o
FILE = graph.pdf

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $(OBJS)

main.o: main.c graph.h
	$(CC) $(CFLAGS) -c main.c

graph.o: graph.c graph.h
	$(CC) $(CFLAGS) -c graph.c

run: $(TARGET)
	./$(TARGET)

$(FILE): $(TARGET)
	./$(TARGET) | dot -Tpdf > $(FILE)

open: $(FILE)
	zathura $(FILE)

clean:
	rm -f $(OBJS) $(TARGET) $(FILE)
