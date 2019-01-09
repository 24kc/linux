#include <iostream>
#include </home/cpplay/cpp/file/pfile.h>
using namespace std;
using namespace __pfile;

void visit(string& s);

int main()
{
	string s(__TIME__);
	pfile pf("cpplay.tmp", ios::in);
	pf.insert(2, s);
	pf.erase(3, 6);
	s.assign("heheda");
	pf.insert(6, 6, s);
	pf.traverse(&visit);
	pf.print();
	pf.save();
	pf.close();
	return 0;
}

void visit(string& s)
{
	int i=0, ret;
	do{
		ret=s.find('\"', i);
		if(ret>=0){
			s.insert(ret, "\\");
			i=ret+2;
		}
	}while(ret>=0);

	s.insert(0, "\"");
	s.append(1, '\"');
}
