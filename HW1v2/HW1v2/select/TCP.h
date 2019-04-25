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
#define buffSize0 100
using namespace std;
class sTCP
{
public:
	friend class sTCP_select;
	int sockfd,csock,offnet,on;
	char *buf;
	struct sockaddr_in myaddr,caddr;
	socklen_t clen;
	string mesg;
public:
	sTCP(int,int,int);
	~sTCP();
	void addrSet(short,unsigned short,unsigned int);
	void Bind();
	void Listen(int);
	int Accept();
	int Send(string);
	int Send(fstream&,int=buffSize0);
	string Recv(unsigned int);
	int Close();
	int endNet();
};

class sTCP_select:public sTCP
{
public:
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
	int Send(string,int);
	int Send(fstream&,int,int=buffSize0);
	int From();
	fd_set &whichOpt(string);
	string Recv(int);
	
};

class cTCP
{
	int sockfd,offnet;
	struct sockaddr_in saddr;
	string mesg;
public:
	cTCP(int,int,int);
	void addrSet(short,unsigned short,unsigned int);
	void Connect();
	int Send(string);
	string Recv(unsigned int);
	int Close();
	int endNet();
};
