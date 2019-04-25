#include <cstdio>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <cstdlib>
#include <iostream>
#include <cstring>
#include <fstream>
#define buffSize0 1000
using namespace std;
class sTCP
{
//public:
	friend class sTCP_select;
	int sockfd,csock,offnet,on,bufSize;
	char *buf;
	struct sockaddr_in myaddr,caddr;
	socklen_t clen;
	string mesg;
public:
	sTCP(int=AF_INET,int=SOCK_STREAM,int=0);
	~sTCP();
	void addrSet(short,unsigned short,unsigned int);
	void Bind();
	void Listen(int);
	int Accept();
	int Send(string,int=-1);
	int Send(fstream&,int=buffSize0);
	string Recv(unsigned int=buffSize0);
	int Close();
	int endNet();
	sTCP& operator=(const sTCP&);
	
};

class sTCP_select:public sTCP
{
//public:
	 fd_set master,rfds,wfds;
	 int fdmax,newfd,from;
	 struct sockaddr_storage caddrs;
public:
	sTCP_select(int,int,int);
	void addrSet(short,unsigned short,unsigned int);
	void Bind();
	int Listen(int);
	void Renew();
	int Select();
	int Accepts(string);
	int Send(string,int=-1);
	int Send(fstream&,int,int=buffSize0);
	int From();
	fd_set &whichOpt(string);
	string Recv(int=buffSize0);
	
};

class cTCP
{
//public:
	int sockfd,offnet;
	struct sockaddr_in saddr;
	string mesg;
public:
	cTCP(int,int,int);
	void addrSet(short,unsigned short,unsigned int);
	void Connect();
	int Send(string,int=-1);
	string Recv(unsigned int=buffSize0);
	int Close();
	int endNet();
};
int Send(string,int=0);
int Send(fstream&,int=0,int=buffSize0);
string Recv(int=0,int=buffSize0);

