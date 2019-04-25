#include <iostream>
#include <string> 
#include "TCP.h"
using namespace std;
int main()
{
	cTCP sock1(AF_INET,SOCK_STREAM,0);
	sock1.addrSet(PF_INET,80,inet_addr("127.0.0.1"));
	sock1.Connect();
	cout<<sock1.Recv(100)<<endl;
	string str = "this is client:" + to_string(getpid()) + "\n";
	while(cin>>str)
	{
		sock1.Send(str);
		do cout<<sock1.Recv(1000);
		while(sock1.endNet());
	}
		
	sock1.Close();
	cout<<"end client test\n";
	return 0;
}
