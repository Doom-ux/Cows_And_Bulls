all: bin/bulls_and_cows bin/test

clean:
	rm -rf bin/bulls_and_cows *.o

build/src/main.o: src/main.cpp
	g++ -std=c++17 -Wall -Werror -c -o build/src/main.o src/main.cpp

build/src/bulls_and_cows.o: src/bulls_and_cows.cpp
	g++ -std=c++17 -Wall -Werror -c -o build/src/bulls_and_cows.o src/build_and_cows.cpp

bin/bulls_and_cows: build/src/main.o build/src/bulls_and_cows.o
	g++ -o bin/bulls_and_cows build/src/main.o build/src/bulls_and_cows.o