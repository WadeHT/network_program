#include <iostream>
#include <string> 
#include <pthread.h>
#include <thread>
#include <sstream>
#include "TCP.h"
#define RecvSize 1000
using namespace std;
void tSend(cTCP);
int main()
{
	cTCP sock1(AF_INET,SOCK_STREAM,0);
	sock1.addrSet(PF_INET,8080,inet_addr("127.0.0.1"));
	sock1.Connect();
	string str = "this is client\n",filename;
	sock1.Send(str);
	thread t(tSend,std::ref(sock1));
	cout<<(str = sock1.Recv(1000))<<endl;
	while(!sock1.endNet())
	{
		cout<<(str = sock1.Recv(1000))<<endl;
		stringstream ss;ss.str(str);
		ss>>str>>str>>str>>filename;
		if(str.find("download") != string::npos)
		{
			ofstream fs;fs.open(filename);
			cout<<(str = sock1.Recv(1000))<<endl;
			fs<<str;
			fs.close();
		}
	}
	sock1.Close();
	cout<<"end client test\n";
	return 0;
}
void tSend(cTCP sock)
{
	string str;
	int to;
	while(cin>>to>>str)sock.Send("to: "+to_string(to)+" content: "+str);
	cout<<"child end"<<endl;
}
