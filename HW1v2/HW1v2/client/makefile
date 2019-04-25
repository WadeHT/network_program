all: clean client.o TCP.o
	g++ -std=c++11 -o c TCP.o client.o
client.o: client.cpp
	g++ -std=c++11 -c client.cpp
	
TCP.o: TCP.h TCP.cpp
	g++ -std=c++11 -c TCP.cpp TCP.h
	
clean:
	rm -f client.o c TCP.o
