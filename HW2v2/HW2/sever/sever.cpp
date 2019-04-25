#include <iostream>
#include <pthread.h>
#include <thread>
#include <sstream>
#include <fstream>
#include "TCP.h"
#define RecvSize 1000
#define clientNum 5
#define sockBase 4
using namespace std;

void tRecv(int,bool[]);
void tSend(bool []);
void checkOnline(bool []);
string filename;
int main()
{
	bool online[clientNum] = {0};
	int csockNum;
	sTCP sock1(AF_INET,SOCK_STREAM,0);
	sock1.addrSet(PF_INET,8080,INADDR_ANY);
	sock1.Bind();
	sock1.Listen(clientNum);
	thread t[clientNum+1];
	t[clientNum] = std::thread(tSend,online);
	for(int i=0;;i++)
	{
		if(i < clientNum)t[i] = std::thread(tRecv,csockNum = sock1.Accept(),online);
		online[csockNum-sockBase] = true;
		sock1.Send("ID: "+to_string(i)+"\n");
	}
	return 0;
}
void tSend(bool online[])
{
	string str;
	int ID;
	while(getline(cin,str))
	{
		stringstream ss; ss.str(str);
		ID = -1;
		ss>>str;
		if(str == "check:")checkOnline(online);
		else if(str == "to:")
		{
			ss>>ID>>str;
			if(online[ID])Send(str,ID+sockBase);		
		}
		else for(int i=0;i<=clientNum;i++)if(online[i])Send(str,i+sockBase);
		
	}
	cout<<"child end"<<endl;
}

void tRecv(int csock,bool online[])
{
	string str;
	int ID = -1,pos;
	while((str = Recv(csock)) != "")
	{
		cout<<str<<endl;
		stringstream ss; ss.str(str);
		ss>>str;
		if(str == "to:")ss>>ID>>str>>str;
		if(ID != -1)
		{
			if((pos = str.find("file:")) != string::npos)
			{
				filename = str.erase (pos,sizeof("file:") - 1);
				if(online[ID])Send("from: "+to_string(csock-sockBase)+" download(y/n): "+filename,ID+sockBase);
			}
			else if(online[ID])Send("from: "+to_string(csock-sockBase)+" content: "+str,ID+sockBase);
		}
		else if(str == "y")
		{
			fstream fs;fs.open(filename,fstream::in);
			cout<<"trans to: "<<(csock-sockBase)<<endl;
			Send(fs,csock);
			fs.close();
			filename = "";
		}
		ID = -1;
	}
	online[csock-sockBase] = false;
}
void checkOnline(bool online[])
{
	for(int i=0;i<clientNum;i++)
		if(online[i])cout<<"ID: "<<i<<" online\n";
		else cout<<"ID: "<<i<<" offline\n";
}
