
all: sol

sol: recursion/permutationNums.cpp
	g++ recursion/permutationNums.cpp mystd.cpp -o sol -g

run: sol
	./sol

debug: sol
	gdb ./sol

clean:
	rm sol
