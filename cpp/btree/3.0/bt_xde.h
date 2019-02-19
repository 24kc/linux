#include "btree.h"

class XDE_BTC{
  public:
	unsigned int uid;
	unsigned int utype;
	void *p;

	XDE_BTC& operator=(const XDE_BTC& xde)
	{
		uid = xde.uid;
		utype = xde.utype;
		p = xde.p;
		return *this;
	}

	int operator<(const XDE_BTC& xde)const{return uid<xde.uid;}
	int operator>(const XDE_BTC& xde)const{return uid>xde.uid;}
	int operator<=(const XDE_BTC& xde)const{return uid<=xde.uid;}
	int operator>=(const XDE_BTC& xde)const{return uid>=xde.uid;}
	int operator==(const XDE_BTC& xde)const{return uid==xde.uid;}
};

class XDEngine{
  public:
	XDE_BTC* find(unsigned int uid);
	XDE_BTC* insert(unsigned int uid, void *p, unsigned int utype);
	int erase(unsigned int uid);

	XDEngine(){tree.set_unique();}
  private:
	XDE_BTC _xde;
	__tree::btree<XDE_BTC> tree;
};

inline XDE_BTC*
XDEngine::find(unsigned int uid)
{
	_xde.uid = uid;
	return tree.find(_xde);
}

inline XDE_BTC*
XDEngine::insert(unsigned int uid, void *p=NULL, unsigned int utype=0)
{
	_xde.uid = uid;
	_xde.utype = utype;
	_xde.p = p;
	return tree.insert(_xde);
}

inline int
XDEngine::erase(unsigned int uid)
{
	_xde.uid = uid;
	return tree.erase(_xde);
}


