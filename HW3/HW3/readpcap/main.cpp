#include "pcap.h"
#include <queue>
#include <iomanip>
using namespace std;
void outContent(Pcap&);
int main(int argc,char*argv[])
{
	string path = argv[1],req = (string)argv[2];
	Pcap packet(path);
	packet.Read();
	cout<<endl;
	while(packet.getLength())
	{
		if((packet.getIP().find(req) != -1) || (packet.getPort().find(req) != -1) || (packet.getPort().find(req) != -1) || (packet.getTime().find(req) != -1) || req == "")
		{
			cout<<"packet size: "<<packet.getLength()<<endl;
			cout<<packet.getIP()<<endl;
			cout<<packet.getPort()<<endl;
			cout<<packet.getTime()<<endl;
			outContent(packet);
			cout<<endl<<setw(80)<<setfill('-')<<"--"<<endl;
		}
		packet.Read();
	}
	return 0;
}
void outContent(Pcap &packet)
{
	const char *str = packet.Content().c_str();	
	for(int i=0;i<packet.Content().length();i++)
	{
		cout<<hex<<setw(2)<<setfill('0')<<(unsigned int)(unsigned char)str[i]<<" ";
		if(i%4 == 3)cout<<"  ";
		if(i%8 == 7)cout<<"\n";
	}
}
