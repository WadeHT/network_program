#include <iostream>
#include "pcap.h"
using namespace std;
int main()
{
	pcap_t *handle;
	pcap_dump_open(handle,"unknown.pcap");
	return 0;
}

