CC = gcc
CFLAGS = -Wall -Wextra -Wpedantic -g

SRC = src
INC = include
OBJ = obj
LIBS = lib
LIB = libds.so
BIN = a.out

CFLAGS += -I$(INC)
CFLAGS += -L$(LIBS)

SRCS = $(wildcard $(SRC)/*.c)
OBJS = $(patsubst $(SRC)/%.c, $(OBJ)/%.o, $(SRCS))

all: $(BIN)

$(BIN): $(OBJS)
	$(CC) $(OBJS) -o $@ $(CFLAGS)

$(OBJ)/%.o: $(SRC)/%.c | $(OBJ)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ):
	mkdir -p $(OBJ)

run: $(BIN)
	./$(BIN)

clean:
	rm -rf $(BIN) $(OBJ)
