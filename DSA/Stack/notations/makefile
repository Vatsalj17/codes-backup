CC = gcc
CFLAGS = -Wall -Wextra -g

TARGET = sol

SRCS = main.c stack.c utils.c prefix.c postfix.c infix.c stack2.c
OBJS = $(SRCS:.c=.o)

DEPS = conversions.h stack.h utils.h stack2.h

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

main.o: conversions.h
postfix.o: conversions.h stack.h utils.h stack2.h
prefix.o: conversions.h stack.h utils.h stack2.h
infix.o: conversions.h stack2.h utils.h
utils.o: utils.h
stack.o: stack.h
stack2.o: stack2.h

%.o: %.c $(DEPS)
	$(CC) $(CFLAGS) -c $< -o $@

run: $(TARGET)
	./$(TARGET)

debug: $(TARGET)
	gdb ./$(TARGET)

clean:
	rm -f $(OBJS) $(TARGET)
