#include <iostream>
#include <csignal>
#include <fstream>
#include "TCP.h"
#include "HTTP.h"
#define bufSize 100
using namespace std;
void httpRe(sTCP_select&);
int main()
{

	char buf[100];
	sTCP_select sock1(AF_INET,SOCK_STREAM,0);
	sock1.addrSet(PF_INET,80,INADDR_ANY);
	sock1.Bind();
	sock1.Listen(5);
	for(;;)
	{
		sock1.Renew();
		if(sock1.Select() < 0) cerr<<"select fail\n";
		sock1.Accepts("read");
		httpRe(sock1);
		sleep(1);
	}
	
	return 0;
}


void httpRe(sTCP_select &sock)
{
	int from;
	string receive;
	char buff[bufSize];
	fstream fs;
	cHTTP handle1(fs);	
	cout<<(receive = sock.Recv(1000));
	from = sock.From();
	handle1.RequestL(receive);
	sock.Send(handle1.Response(),from);
	sock.Send(handle1.ContentType(),from);
	sock.Send(handle1.ContentLen(),from);
	sock.Send(handle1.Connection(),from);
	sock.Send(handle1.HeaderEnd(),from);
	sock.Send(fs,from);
	fs.close();
}
