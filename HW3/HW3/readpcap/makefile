all: pcap.o base_type.h
	g++ -std=c++11 -o a main.cpp pcap.o 
pcap.o: pcap.cpp pcap.h base_type.h
	g++ -std=c++11 -c pcap.cpp pcap.h base_type.h
clean:
	rm -f a pcap.o
