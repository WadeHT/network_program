#include <iostream>
#include <unistd.h>
#include <csignal>
#include <fstream>
#include <cstring>
#include "TCP.h"
#include "HTTP.h"
#define bufSize 100
using namespace std;
void httpRe(sTCP&);
int main()
{
	sTCP sock1(AF_INET,SOCK_STREAM,0);
	sock1.addrSet(PF_INET,80,INADDR_ANY);
	sock1.Bind();
	sock1.Listen(5);
	pid_t cPid;
	signal (SIGCHLD,SIG_IGN);
	for(;;)
	{
		sock1.Accept();
		if((cPid = fork())<0)cerr<<"fork fail"<<endl;
		else if(cPid == 0)
		{
			httpRe(sock1);
			sock1.Close();
			cerr<<"fork end\n\n";
			exit(0);
		}		
	}
	cout<<"end sever test\n";
	return 0;
}

void httpRe(sTCP& sock)
{
	string receive;
	char buff[bufSize];
	fstream fs;
	cHTTP handle1(fs);
	cout<<(receive = sock.Recv(1000))<<endl<<endl;
	handle1.RequestL(receive);
	sock.Send(handle1.Response());
	sock.Send(handle1.ContentType());
	sock.Send(handle1.ContentLen());
	sock.Send(handle1.Connection());
	sock.Send(handle1.HeaderEnd());
	sock.Send(fs);
	fs.close();
}
