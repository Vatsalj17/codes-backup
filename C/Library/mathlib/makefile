CC := gcc
CFLAGS := -Wall -Wextra -g

# --- Main Targets ---
# "all" is the default target. It will build both versions.
all: static_program dynamic_program

# --- Dynamic Version ---
dynamic_program: main.o libmath.so
	@echo "Linking dynamic program..."
	$(CC) $(CFLAGS) main.o -o dynamic_program -L. -lmath

libmath.so: math_lib_pic.o
	@echo "Creating shared object libmath.so..."
	$(CC) -shared $^ -o $@

# This special target builds our "Position Independent Code" object
math_lib_pic.o: math_lib.c math_lib.h
	@echo "Compiling PIC object for .so..."
	$(CC) $(CFLAGS) -fPIC -c math_lib.c -o math_lib_pic.o

# --- Static Version ---
static_program: main.o libmath.a
	@echo "Linking static program..."
	# We can just list the .a file directly
	$(CC) $(CFLAGS) -static main.o libmath.a -o static_program

libmath.a: math_lib.o
	@echo "Creating static archive libmath.a..."
	ar rcs $@ $^

# --- Common Object Files ---
# These are the standard, non-PIC objects
main.o: main.c math_lib.h
	@echo "Compiling main.o..."
	$(CC) $(CFLAGS) -c main.c -o main.o

math_lib.o: math_lib.c math_lib.h
	@echo "Compiling math_lib.o..."
	$(CC) $(CFLAGS) -c math_lib.c -o math_lib.o

# --- Clean Up ---
clean:
	@echo "Cleaning up..."
	rm -f *.o *.a *.so static_program dynamic_program
