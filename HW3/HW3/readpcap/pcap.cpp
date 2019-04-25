#include "pcap.h"
bool filepart(pcapFileHeader_t &pcapFileHeader,ifstream  &fileHandler,const string &path)
{
	memset(&pcapFileHeader,0,sizeof(pcapFileHeader));
	fileHandler.open(path.c_str());
	if (!fileHandler)return false;
	fileHandler.read((char8_t*)&pcapFileHeader, sizeof(pcapFileHeader));
	if (pcapFileHeader.magic[0] != PCAP_FILE_MAGIC_1 || pcapFileHeader.magic[1] != PCAP_FILE_MAGIC_2 || pcapFileHeader.magic[2] != PCAP_FILE_MAGIC_3 || pcapFileHeader.magic[3] != PCAP_FILE_MAGIC_4)
        	cout << "The file is not a pcap file" << endl;
	return true;
}
bool packetpart(pcapPkthdr_t  &packetHeader,ifstream  &fileHandler,string &str)
{
	memset(&packetHeader,0,sizeof(packetHeader));
	fileHandler.read((char8_t*)&packetHeader, sizeof(packetHeader));
	char8_t buf[packetHeader.caplen];
	fileHandler.read(buf, packetHeader.caplen);
	string temp(buf, packetHeader.caplen);
        str = temp;
	return true;
}
//----------------------------------//
Pcap::Pcap(const string path):fileName(path)
{
	if(filepart(pcapFileHeader,fileHandler,path)== false) cerr<<"error"<<endl;	
}
bool Pcap::Read()
{
	return packetpart(packetHeader,fileHandler,str);
}
string Pcap::Content()
{
	return str;
}
unsigned long long int Pcap::getLength()
{
	return packetHeader.caplen;
}
string Pcap::getIP()
{
	stringstream ss;
	ss<<"source IP: "
	<<(unsigned int)(unsigned char)str[26]<<"."
	<<(unsigned int)(unsigned char)str[27]<<"."
	<<(unsigned int)(unsigned char)str[28]<<"."
	<<(unsigned int)(unsigned char)str[29]
	<<" destination IP: "
	<<(unsigned int)(unsigned char)str[30]<<"."
	<<(unsigned int)(unsigned char)str[31]<<"."
	<<(unsigned int)(unsigned char)str[32]<<"."
	<<(unsigned int)(unsigned char)str[33]<<"";
	return ss.str();
}
string Pcap::getPort()
{
	stringstream ss;
	ss<<"source Port: "<<((unsigned int)(unsigned char)str[34]<<8)+(unsigned int)(unsigned char)str[35]
	<<" destination Port: "<<((unsigned int)(unsigned char)str[36]<<8)+(unsigned int)(unsigned char)str[37];
	return ss.str();
}
string Pcap::getTime()
{
	time_t time = packetHeader.seconds;
	return (string)asctime(localtime(&time));
}
Pcap::~Pcap()
{
    fileHandler.close();
}
