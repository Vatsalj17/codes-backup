CC=gcc
CFLAGS=-Wall -g
BINS = test runtime_test static_test

all: $(BINS)


# create object files for the shared library.
# it's required because the shared library needs to be built from object files.
libmycode.o: libmycode.c mycode.h
	$(CC) $(CFLAGS) -c libmycode.c


# This command creates a shared library
# -fPIC -> Position Independent Code (It enables the code to be loaded at any memory address)
# -shared -> create a shared library (If not included, the program will be linked as a static library.)
# -o $@ -> output file name is the target name
# -lc (i.e. libc.so) -> link with the C library (it is needed because mycode.h is included in test.c)
# other and better way to write this command -> $(CC) $(CFLAGS) -fPIC -shared -o $@ libmycode.o -lc
libmycode.so: libmycode.o mycode.h
	$(CC) $(CFLAGS) -fPIC -shared -o $@ libmycode.o -lc


# This command creates a static library
# ar -> archiver
# r -> replace or add files to the archive
# c -> create the archive if it doesn't exist
# s -> create an index for the archive
libmystaticcode.a: libmycode.o
	ar rcs libmystaticcode.a libmycode.o


test: test.c libmycode.o
	$(CC) $(CFLAGS) -o $@ $^


# This command runs the test executable with the shared library
# -L. -> search for libraries in the current directory
# -lmycode -> link with the library named libmycode (which is libmycode.so)
runtime_test: test.c libmycode.so
	$(CC) $(CFLAGS) -o $@ $^ -L. -lmycode


# This command runs the test executable with the static library
# -L. -> search for libraries in the current directory
# -lmystaticcode -> link with the library named libmystaticcode (which is libmystaticcode.a)
static_test: test.c libmystaticcode.a
	$(CC) $(CFLAGS) -o $@ $^ -L. -lmystaticcode


clean:
	rm $(BINS) *.o *.so *.a
