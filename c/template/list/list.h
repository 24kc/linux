#ifndef _24k_list_t
#error: No define "_24k_list_t"
#endif

#ifndef _STDLIB_H // malloc(), exit()
#include <stdlib.h>
#ifndef _STDLIB_H
#define _STDLIB_H
#endif
#endif

#ifndef _STRING_H // memcpy()
#include <string.h>
#ifndef _STRING_H
#define _STRING_H
#endif
#endif

#ifndef _STDARG_H // va_list
#include <stdarg.h>
#ifndef _STDARG_H
#define _STDARG_H
#endif
#endif

#define _24k_list_lk__(T)	T##_##list
#define _24k_list_lk(T)	_24k_list_lk__(T)
#define _24k_list	_24k_list_lk(_24k_list_t)

#define _24k__(x, T)	T##_##list##_##x
#define _24k_(x, T)	_24k__(x, T)
#define _24k(x)		_24k_(x, _24k_list_t)

#define _24k_error__(fmt, ...)	_24k(fatal_error)(fmt, __VA_ARGS__)
#define _24k_error(fmt, ...)	_24k_error__(fmt, __VA_ARGS__)

#define _24k_strmac__(x)	#x
#define _24k_strmac(x)		_24k_strmac__(x)

void
_24k(fatal_error) (const char *fmt, ...) {
#ifndef _24k_list_not_print_error
	va_list ap;
	va_start(ap, fmt);
	fprintf(stderr, "_24k: error: ");
	vfprintf(stderr, fmt, ap);
	va_end(ap);
#endif
#ifndef _24k_list_not_exit
	exit(24);
#endif
}

typedef struct _24k(node){
	_24k_list_t data;
	struct _24k(node) *prev;
	struct _24k(node) *next;
}_24k(node);

typedef struct{
	_24k(node) *head;
	_24k(node) *tail;
	size_t size;
}_24k_list;

int
_24k(init) (_24k_list *list) {
	list->head = (_24k(node)*) malloc ( sizeof(_24k(node)) );
	list->tail = (_24k(node)*) malloc ( sizeof(_24k(node)) );
	if ( ! list->head || ! list->tail ) {
		_24k_error("%s: Memory allocation failed\n", _24k_strmac(_24k(init)));
		return 0;
	}
	list->head->prev = NULL;
	list->head->next = list->tail;
	list->tail->prev = list->head;
	list->tail->next = NULL;
	list->size = 0;
	return 1;
}

void
_24k(destroy) (_24k_list *list) {
	_24k(node) *p = list->head;

	while (p) {
		list->head = list->head->next;
		free(p);
		p = list->head;
	}
	list->head = NULL;
	list->tail = NULL;
	list->size = 0;
}

_24k_list_t*
_24k(front) (_24k_list *list) {
	if ( ! list->size ) {
		_24k_error("%s: list is empty\n", _24k_strmac(_24k(front)));
		return 0;
	}
	return &list->head->next->data;
}

_24k_list_t*
_24k(back) (_24k_list *list) {
	if ( ! list->size ) {
		_24k_error("%s: list is empty\n", _24k_strmac(_24k(back)));
		return 0;
	}
	return &list->tail->prev->data;
}

int
_24k(empty) (_24k_list *list) {
	if ( list->size )
		return 0;
	return 1;
}

size_t
_24k(size) (_24k_list *list) {
	return list->size;
}

void
_24k(clear) (_24k_list *list) {
	_24k(destroy)(list);
	_24k(init)(list);
}

int
_24k(insert) (_24k_list *list, _24k(node) *p, _24k_list_t *t) {
	_24k(node) *p1 = (_24k(node)*) malloc ( sizeof(_24k(node)) );
	if ( ! p1 ) {
		_24k_error("%s: Memory allocation failed\n", _24k_strmac(_24k(insert)));
		return 0;
	}
	memcpy(&p1->data, t, sizeof(_24k_list_t));
	p1->next = p;
	p1->prev = p->prev;
	p->prev = p1;
	p1->prev->next = p1;
	++list->size;
	return 1;
}

void
_24k(erase) (_24k_list *list, _24k(node) *p) {
	p->next->prev = p->prev;
	p->prev->next = p->next;
	free(p);
	--list->size;
}


int
_24k(push_back) (_24k_list *list, _24k_list_t *t) {
	_24k(node) *p = (_24k(node)*) malloc ( sizeof(_24k(node)) );
	if ( ! p ) {
		_24k_error("%s: Memory allocation failed\n", _24k_strmac(_24k(push_back)));
		return 0;
	}
	memcpy(&p->data, t, sizeof(_24k_list_t));
	p->prev = list->tail->prev;
	p->next = list->tail;
	list->tail->prev = p;
	p->prev->next = p;
	++list->size;
	return 1;
}

int
_24k(push_front) (_24k_list *list, _24k_list_t *t) {
	_24k(node) *p = (_24k(node)*) malloc ( sizeof(_24k(node)) );
	if ( ! p ) {
		_24k_error("%s: Memory allocation failed\n", _24k_strmac(_24k(push_front)));
		return 0;
	}
	memcpy(&p->data, t, sizeof(_24k_list_t));
	p->next = list->head->next;
	p->prev = list->head;
	list->head->next = p;
	p->next->prev = p;
	++list->size;
	return 1;
}

int
_24k(pop_back) (_24k_list *list) {
	_24k(node) *p;

	if ( ! list->size ) {
		_24k_error("%s: list is empty\n", _24k_strmac(_24k(pop_back)));
		return 0;
	}
	p = list->tail->prev;
	list->tail->prev = p->prev;
	p->prev->next = list->tail;
	free(p);
	--list->size;
	return 1;
}

int
_24k(pop_front) (_24k_list *list) {
	_24k(node) *p;

	if ( ! list->size ) {
		_24k_error("%s: list is empty\n", _24k_strmac(_24k(pop_front)));
		return 0;
	}
	p = list->head->next;
	list->head->next = p->next;
	p->next->prev = list->head;
	free(p);
	--list->size;
	return 1;
}

int
_24k(traverse) (_24k_list *list, int (*visit)(_24k_list_t*)) {
	int r;
	_24k(node) *p = list->head->next;

	while ( p != list->tail ) {
		r = visit( &p->data );
		if ( r )
			return r;
		p = p->next;
	}
	return 0;
}

#undef _24k_list_lk__
#undef _24k_list_lk
#undef _24k_list

#undef _24k__
#undef _24k_
#undef _24k

#undef _24k_error__
#undef _24k_error

#undef _24k_strmac__
#undef _24k_strmac

#undef _24k_list_t

