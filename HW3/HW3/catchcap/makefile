all: catchPacket
	g++ -std=c++11 -o a catchPacket.o main.cpp -lpcap
catchPacket: catchPacket.h catchPacket.cpp
	g++ -std=c++11 -c catchPacket.cpp -lpcap
clean:
	rm -f a catchPacket.o
