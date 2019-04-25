#include <sstream>
#include <fstream>
#include <iostream>
using namespace std;
class cHTTP
{
public:
	string option,filepath,protocol,filetype;
	stringstream ss;
	int opt,filelen;
	fstream &fs;
public:
	cHTTP(fstream&);
	~cHTTP();
	int RequestL(string);
	string Response();
	string FileType();
	string ContentType();
	string ContentLen();
	string Connection(string="close");
	string HeaderEnd();
	void FileHandler();
};


