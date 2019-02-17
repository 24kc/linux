#include <iostream>
#define MAX_T 6
#include "btree_v.h"
using namespace std;
using namespace __tree;

static const char *reserve_word[32] = {
    "auto", "break", "case", "char", "const", "continue",
    "default", "do", "double", "else", "enum", "extern",
    "float", "for", "goto", "if", "int", "long",
    "register", "return", "short", "signed", "sizeof", "static",
    "struct", "switch", "typedef", "union", "unsigned", "void",
    "volatile", "while"
};

int
main()
{
	int i;
	string s, *ps;
	btree<string> T;
cout<<"MAX_T="<<MAX_T<<" MIN_T="<<MIN_T<<endl;

	for (i=0;i<32;i++) {
		s.assign(reserve_word[i]);
		T.insert(s);
		T.print();
		cout<<endl<<endl;
	}
/*	for (i=0;i<32;i++) {
		s.assign(reserve_word[i]);
		T.erase(s);
		T.print();
		cout<<endl<<endl;
	}
*/	s.assign("union");
	ps = T.find(s);
	if (ps)
		cout<<*T.find(s)<<endl;
	else
		cout<<"NULL"<<endl;
}
