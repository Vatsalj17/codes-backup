# FILE = reverseListInK
FILE = addTwoNumber

USE_CPP ?= 0

ifneq ($(strip $(cpp)),)
USE_CPP := $(cpp)
endif

ifeq ($(USE_CPP),1)
CC := g++
SRC := $(FILE).cpp list.cpp
$(info Into the cpp mode)
else
CC := gcc
SRC := $(FILE).c list.c
$(info In c mode)
endif

OBJ := list
CFLAGS ?= -g

all: $(OBJ)

$(OBJ): $(SRC)
	$(CC) $(CFLAGS) $(SRC) -o $(OBJ)

run: $(OBJ)
	./$(OBJ)

debug: $(OBJ)
	gdb ./$(OBJ)

clean:
	rm -f $(OBJ)
