all: 	clean sever.o TCP.o HTTP.o
	g++ -std=c++11 -o s TCP.o HTTP.o sever.o

sever.o: sever.cpp
	g++ -std=c++11 -c sever.cpp

TCP.o: TCP.h TCP.cpp
	g++ -std=c++11 -c TCP.cpp TCP.h
	
HTTP.o:HTTP.h HTTP.cpp
	g++ -std=c++11 -c HTTP.cpp HTTP.h
	
clean:
	rm -f sever.o TCP.h.gch s TCP.o
