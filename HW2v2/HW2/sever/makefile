all: sever.o TCP.o
	g++ -std=c++11 -o s sever.o TCP.o -lpthread
sever.o: sever.cpp
	g++ -std=c++11 -I ../TCP/ -c sever.cpp -lpthread
TCP.o: ../TCP/TCP.h ../TCP/TCP.cpp
	g++ -std=c++11 -c ../TCP/TCP.h ../TCP/TCP.cpp
clean:
	rm -f TCP.o sever.o s
