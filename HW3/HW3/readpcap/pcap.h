#ifndef  PCAP_H
#define  PCAP_H

#include "base_type.h"
#include <queue>
#include <fstream>
#include <iostream>
#include <cstring>
#include <sstream>
#include <ctime>
#include <string> 
#include <ctime>
using namespace std;

#define  PCAP_FILE_MAGIC_1   0Xd4
#define  PCAP_FILE_MAGIC_2   0Xc3
#define  PCAP_FILE_MAGIC_3   0Xb2
#define  PCAP_FILE_MAGIC_4   0Xa1


/*pcap file header*/
typedef struct pcapFileHeader
{
    	uchar8_t   magic[4];
    	uint16_t   version_major;
    	uint16_t   version_minor;
    	int32_t    thiszone;      
    	uint32_t   sigfigs;      
    	uint32_t   snaplen;      
    	uint32_t   linktype;     
} pcapFileHeader_t;



/*pcap packet header*/
typedef struct pcapPkthdr
{
    	uint32_t   seconds;     
    	uint32_t   u_seconds;  
    	uint32_t   caplen;     
    	uint32_t   len;         
} pcapPkthdr_t;



class Pcap
{
	ifstream  fileHandler;
    	const string fileName;
    	pcapFileHeader_t  pcapFileHeader;
    	pcapPkthdr_t  packetHeader;
    	string str;
public:
    	Pcap(const string fileName);
    	~Pcap();
    	string getIP();
    	string getPort();
    	unsigned long long int getLength();
    	string getTime();
    	bool Read();
    	string Content();
    
};

#endif

