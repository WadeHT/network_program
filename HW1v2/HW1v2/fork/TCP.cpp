#include "TCP.h"
sTCP::sTCP(int family,int type,int protocol):sockfd(socket(family,type,protocol)),clen(sizeof(caddr)),on(1),buf(new char[buffSize0])
{
	if(sockfd < 0)cerr<<"socket fail"<<endl;
	if((setsockopt(sockfd,SOL_SOCKET,SO_REUSEADDR,&on,sizeof(on)))<0)cerr<<"setsockop failed"<<endl;
}
sTCP::~sTCP()
{
	delete[]buf;
}
void sTCP::addrSet(short family,unsigned short port,unsigned int saddr)
{
	memset(&myaddr,0,sizeof(myaddr));
	myaddr.sin_family = family;
    	myaddr.sin_addr.s_addr = saddr;
   	myaddr.sin_port = htons(port);
}
void sTCP::Bind()
{
	if(bind(sockfd,(struct sockaddr*)&myaddr,sizeof(myaddr)) < 0)cerr<<"bind fail"<<endl;
}
void sTCP::Listen(int backlog)
{
	if(listen(sockfd,backlog) < 0)cerr<<"listen fail"<<endl;
}
int sTCP::Accept()
{
	if((csock = accept(sockfd,(struct sockaddr*)&caddr,&clen)) < 0)cerr<<"accept fail"<<endl;
	return csock;
}
int sTCP::Send(string str)
{
	return send(csock,(char*)str.c_str(),(int)str.length(),0);
}
int sTCP::Send(fstream &fs,int buffSize)
{
	int result = 0,each;
	if(buffSize != buffSize0)
	{
		delete[]buf;
		buf = new char[buffSize];
	}
	while(!fs.eof()  && fs.is_open())
	{
		memset(buf,0,buffSize);
		fs.read(buf,buffSize);
		if((each = send(csock,buf,buffSize,0)) < 0)return each;
		result += each;
	}
	return result;
}
string sTCP::Recv(unsigned int mesgSize)
{
	char temp[mesgSize] = {};
	if((offnet = recv(csock,temp,mesgSize,0)) < 0)return "recv fail";
	else if(offnet == 0)return "recv end";
	return (string)temp;
}
int sTCP::Close()
{
	return close(sockfd);
}
int sTCP::endNet()
{
	return offnet;
}

/*================================sTCP_select=============================*/

sTCP_select::sTCP_select(int family,int type,int protocol):sTCP(family,type,protocol)
{
	FD_ZERO(&master);
	FD_ZERO(&rfds);
	FD_ZERO(&wfds);
}
void sTCP_select::Bind()
{
	if(bind(sockfd,(struct sockaddr*)&myaddr,sizeof(myaddr)) < 0)cerr<<"bind fail"<<endl;
}
void sTCP_select::Renew()
{
	wfds = rfds = master;
}
int sTCP_select::Select()
{
	return select(fdmax+1, &rfds, &wfds, NULL, NULL);
}
fd_set& sTCP_select::whichOpt(string str)
{
	if(str == "read")return rfds;
}
int sTCP_select::Accepts(string str)
{
	fd_set &act = whichOpt(str);
	if (FD_ISSET(sockfd, &act)) 
	{
		clen = sizeof caddrs;
		if((newfd = accept(sockfd,(struct sockaddr *)&caddrs,&clen)) >=0)
		{
			FD_SET(newfd, &master); 
			if (newfd > fdmax)fdmax = newfd;
		}
	}
	return newfd;
}
int sTCP_select::Send(string str,int no)
{
	return send(no,(char*)str.c_str(),(int)str.length(),0);
}
int sTCP_select::Send(fstream &fs,int no,int buffSize)
{
	int result = 0,each;
	if(buffSize != buffSize0)
	{
		delete[]buf;
		buf = new char[buffSize];
	}
	while(!fs.eof()  && fs.is_open())
	{
		memset(buf,0,buffSize);
		fs.read(buf,buffSize);
		if((each = send(no,buf,buffSize,0)) < 0)return each;
		result += each;
	}
	return result;
}
string sTCP_select::Recv(int mesgSize)
{
	string out = "";
	char temp[mesgSize] = {};
	for(int i = 0; i <= fdmax; i++)
		if (FD_ISSET(i, &rfds) && i != sockfd)
			if (recv(i, temp, sizeof temp, 0) <= 0)
			{
				close(i);
           			FD_CLR(i, &master);
			}
			else
			{
				from = i;
				out = out + temp;
				memset(temp,0,sizeof temp);
			}
	return out;
}
int sTCP_select::From()
{
	return from;
}

int sTCP_select::Listen(int backlog)
{
	listen(sockfd,backlog);
	FD_SET(sockfd, &master);	
	fdmax = sockfd;
}

void sTCP_select::addrSet(short family,unsigned short port,unsigned int saddr)
{
	memset(&myaddr,0,sizeof(myaddr));
	myaddr.sin_family = family;
    	myaddr.sin_addr.s_addr = saddr;
   	myaddr.sin_port = htons(port);
}

/*================================cTCP=============================*/

cTCP::cTCP(int family,int type,int protocol):sockfd(socket(family,type,protocol))
{
	if(sockfd < 0)cerr<<"socket fail"<<endl;
}
void cTCP::addrSet(short family,unsigned short port,unsigned int iaddr)
{
	memset(&saddr,0,sizeof(saddr));
	saddr.sin_family = family;
    	saddr.sin_addr.s_addr = iaddr;
   	saddr.sin_port = htons(port);
}
void cTCP::Connect()
{
	if(connect(sockfd,(struct sockaddr*)&saddr,sizeof(saddr)) < 0)
		cerr<<"connect fail"<<endl;
}
int cTCP::Send(string str)
{
	return send(sockfd,(char*)str.c_str(),(int)str.length(),0);
}

string cTCP::Recv(unsigned int mesgSize)
{
	char temp[mesgSize] = {};
	if((offnet = recv(sockfd,temp,mesgSize,0)) < 0)return "recv fail";
	else if(offnet == 0)return "recv end";
	return (string)temp;
}
int cTCP::Close()
{
	return close(sockfd);
}
int cTCP::endNet()
{
	return offnet;
}


