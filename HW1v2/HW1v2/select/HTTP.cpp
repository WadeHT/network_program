#include "HTTP.h"
unsigned int fileLen(fstream &);
cHTTP::cHTTP(fstream& fd):fs(fd){}
cHTTP::~cHTTP(){fs.close();}
int cHTTP::RequestL(string str)
{
	ss.str(str);
	ss>>option>>filepath>>protocol;
	if(option == "GET")return opt = 1;
}

string cHTTP::Response()
{
	FileHandler();
	if(fs.is_open())return protocol+" 201 OK\r\n";
	return protocol+" 401 Bad Request\r\n";
}
string cHTTP::FileType()
{
	if(filepath.find(".html") < string::npos)filetype = "text/html";
	else if(filepath.find(".png") < string::npos)filetype = "image/png";
	else if(filepath.find(".ico") < string::npos) filetype = "image/x-icon";
	else filetype = "";
	return filetype;
}
string cHTTP::ContentType()
{
	return "Content-Type: "+filetype+"\r\n";
}
string cHTTP::ContentLen()
{
	return "Content-Length: "+to_string(filelen)+"\r\n";
}
string cHTTP::Connection(string str)
{
	return "Connection: "+str+"\r\n";
}
string cHTTP::HeaderEnd()
{
	return "\r\n";
}
void cHTTP::FileHandler()
{
	FileType();

	if(filetype == "text/html")fs.open("."+filepath,ios::in);
	else if(filetype == "image/png")fs.open("."+filepath,ios::in|ios_base::binary);

	filelen = fileLen(fs);	
}
unsigned int fileLen(fstream &fs)
{
	fs.seekg(0,ios::end);
	unsigned int len = fs.tellg();
	fs.seekg(0,ios::beg);
	return len;
}
//string cHTTP::
//string cHTTP::
