all:
	clang++ -std=c++14 -g -O2 -Wall -Wextra -Wpedantic main.cpp -o main

run:
	./main

clean:
	rm main
