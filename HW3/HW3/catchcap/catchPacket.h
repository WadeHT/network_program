#include <pcap.h>
#include <iostream>
#include <sstream>
#include <string> 
#include <netinet/if_ether.h>
#include <iomanip> 
#define bufSize 1024
using namespace std;
class catchPacket
{
	char errbuf[PCAP_ERRBUF_SIZE],*content,*dev;
	int ret;
	bpf_u_int32 netp, maskp;
	pcap_t *handle;	
	struct pcap_pkthdr header;	
	struct ether_header *ethernet_protocol;
public:
	catchPacket(char*Dev=NULL,int=1,int=0);
	void Catch();
	string Dev();
	string Header();
	string Mac();
};
