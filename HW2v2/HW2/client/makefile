all: client.o TCP.o
	g++ -std=c++11 -o c client.o TCP.o -lpthread
client.o: client.cpp
	g++ -std=c++11 -I ../TCP/ -c client.cpp -lpthread
TCP.o: ../TCP/TCP.h ../TCP/TCP.cpp
	g++ -std=c++11 -c ../TCP/TCP.h ../TCP/TCP.cpp
clean:
	rm -f TCP.o client.o c
