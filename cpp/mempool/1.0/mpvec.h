#ifndef _MPVEC_H_
#define _MPVEC_H_

#ifndef _GLIBCXX_VECTOR
#include <vector>
#endif

#define __tt(T)	template <typename T>

__tt(T)
class mp_size_t{
	T t;
};

__tt(T)
class mempool{
  public:
	void* alloc(){return alloc(1);}
	void* alloc(size_t size);
	void free(void*);

	size_t remain(){return blocks-block_used;}
	mempool(size_t count):blocks(count), block_used(0){memory.reserve(count);}

  private:
	size_t blocks;
	size_t block_used;
	mp_size_t<T> t_null;
	std::vector<mp_size_t<T>> memory;
	std::vector<int> index;
};

__tt(T)
void*
mempool<T>::alloc(size_t size)
{
	int i;

	if (size>sizeof(mp_size_t<T>) || block_used==blocks)
		return NULL;
	block_used++;
	if (!index.empty()) {
		i = index.back();
		index.pop_back();
		return (void*)(&memory.front()+i);
	}
	memory.push_back(t_null);
	return (void*)&memory.back();
}

__tt(T)
inline void
mempool<T>::free(void *p)
{
	block_used--;
	index.push_back((mp_size_t<T>*)p-&memory.front());
}

#undef __tt

#endif
