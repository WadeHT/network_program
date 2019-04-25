#include "catchPacket.h"
catchPacket::catchPacket(char* Dev,int promisc,int ms):errbuf(),dev(pcap_lookupdev(errbuf)),netp(0),maskp(0),ret(pcap_lookupnet(dev, &netp, &maskp, errbuf)),handle(pcap_open_live(dev, bufSize, promisc, ms, errbuf))
{
	if(dev == NULL)
	{
		std::cerr<<errbuf;
		exit(-1);
	}
	if(ret == -1)
	{
		std::cerr<<errbuf;
		exit(-1);
	}
	if(handle == NULL)
	{
		std::cerr<<errbuf;
		exit(-1);
	}
	if(Dev != NULL)dev = Dev;
}

void catchPacket::Catch()
{
	if((content = (char*)pcap_next(handle,&header)) == NULL)std::cerr<<("pcap fault");
	ethernet_protocol = (struct ether_header *)content;
}
string catchPacket::Dev()
{
	return dev;
}
string catchPacket::Header()
{
	return (string)ctime((const time_t *)&header.ts.tv_sec)+to_string(header.caplen)+" "+to_string(header.len);
}
string catchPacket::Mac()
{
	stringstream ss;
	ss<<setw(2)<<setfill('0')<<hex<<(unsigned int)ethernet_protocol->ether_dhost[0]
	<<setw(2)<<setfill('0')<<hex<<(unsigned int)ethernet_protocol->ether_dhost[1]
	<<setw(2)<<setfill('0')<<hex<<(unsigned int)ethernet_protocol->ether_dhost[2]
	<<setw(2)<<setfill('0')<<hex<<(unsigned int)ethernet_protocol->ether_dhost[3]
	<<setw(2)<<setfill('0')<<hex<<(unsigned int)ethernet_protocol->ether_dhost[4]
	<<setw(2)<<setfill('0')<<hex<<(unsigned int)ethernet_protocol->ether_dhost[5]
	<<" "
	<<setw(2)<<setfill('0')<<hex<<(unsigned int)ethernet_protocol->ether_shost[0]
	<<setw(2)<<setfill('0')<<hex<<(unsigned int)ethernet_protocol->ether_shost[1]
	<<setw(2)<<setfill('0')<<hex<<(unsigned int)ethernet_protocol->ether_shost[2]
	<<setw(2)<<setfill('0')<<hex<<(unsigned int)ethernet_protocol->ether_shost[3]
	<<setw(2)<<setfill('0')<<hex<<(unsigned int)ethernet_protocol->ether_shost[4]
	<<setw(2)<<setfill('0')<<hex<<(unsigned int)ethernet_protocol->ether_shost[5];
	return ss.str();
}


