CXX = g++
CXXFLAGS = -std=c++11 -Wall

all: game test

game: main.o cards.o
	$(CXX)	$(CXXFLAGS) -o game main.o cards.o

test: test.o cards.o
	$(CXX)	$(CXXFLAGS) -o test test.o cards.o

main.o: main.cpp cards.h
	$(CXX)	$(CXXFLAGS) -c main.cpp

cards.o: cards.cpp cards.h
	$(CXX)	$(CXXFLAGS) -c cards.cpp

test.o: test.cpp cards.h
	$(CXX)	$(CXXFLAGS) -c test.cpp

clean:
	rm -f game test *.o
