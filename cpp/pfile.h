#ifndef _PFILE_H_
#define _PFILE_H_

#ifndef _GLIBCXX_FSTREAM
#include <fstream>
#endif

#ifndef _GLIBCXX_VECTOR
#include <vector>
#endif

#ifndef _GLIBCXX_STRING
#include <string>
#endif

namespace __pfile{
using namespace std;

class pfile : public fstream
{
  public:
	void print();
	void print(int line);
	void insert(int line, string& s);
	void insert(int line, int pos, string& s);
	void erase(int line);
	void erase(int line1, int line2);
	void traverse(void (*visit)(string&));
	void save();
	void save(const char *fname);

	void swap(int line1, int line2);
	void wrap(int line, int pos);
	void escape(const char *str);
	void erase_blankline();

	pfile(const char* fname, ios::openmode mode);

  private:
	vector<string> lines;
	string fname;
};

pfile::pfile(const char* fname, ios::openmode mode=ios::in|ios::out) : fstream(fname,mode)
{
	string s;
	this->fname.assign(fname);
	this->fname.append(".pfile");
	while(!eof()){
		std::getline(*this, s);
		lines.push_back(s);
	}
	seekg(0, ios::beg);
	lines.pop_back();
}

inline void pfile::swap(int line1, int line2)
{
	lines[line1].swap(lines[line2]);
}

void pfile::wrap(int line, int pos)
{
	string s;
	lines.insert(lines.begin()+line+1, s);
	lines[line+1]=lines[line].substr(pos);
	lines[line].erase(pos);
}

void pfile::escape(const char *str)
{
	int i;
	vector<string>::iterator iter;
	for(iter=lines.begin(); iter!=lines.end(); iter++)
		for(i=0;;){
			i=iter->find_first_of(str, i);
			if(i!=string::npos){
				iter->insert(i, "\\");
				i+=2;
			}
			else
				break;
		}
}

void pfile::erase_blankline()
{
	int i;
	vector<string>::iterator iter;
	for(iter=lines.begin(); iter!=lines.end(); iter++){
		for(i=0; i<iter->size(); i++)
			if(!isspace(*(iter->begin()+i)))
				break;
		if(i==iter->size())
			lines.erase(iter, iter+1);
	}
}

void pfile::print()
{
	vector<string>::iterator iter=lines.begin();
	while(iter!=lines.end())
		cout<<*iter++<<endl;
}

inline void pfile::print(int line)
{
	cout<<lines[line]<<endl;
}

inline void pfile::insert(int line, string& s)
{
	lines.insert(lines.begin()+line, s);
}
inline void pfile::insert(int line, int pos, string& s)
{
	lines.insert(lines.begin()+line, pos, s);
}
	
inline void pfile::erase(int line)
{
	lines.erase(lines.begin()+line, lines.begin()+line+1);
}

inline void pfile::erase(int line1, int line2)
{
	lines.erase(lines.begin()+line1, lines.begin()+line2);
}

void pfile::traverse(void (*visit)(string&))
{
	vector<string>::iterator iter=lines.begin();
	while(iter!=lines.end())
		visit(*iter++);
}

void pfile::save(const char *fname)
{
	ofstream out(fname, ios::out|ios::trunc);
	vector<string>::iterator iter=lines.begin();
	while(iter!=lines.end())
		out<<*iter++<<endl;
	out.close();
}

inline void pfile::save()
{
	save(fname.c_str());
}

}//namespace __pfile

#endif
