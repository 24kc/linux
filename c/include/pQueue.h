#ifndef _PQUEUE_H_
#define _PQUEUE_H_
// use basic type or pointers

#ifndef _STDLIB_H
#include <stdlib.h>
#endif

#ifndef _MEMORY_H
#include <memory.h>
#endif

#ifndef QElemType
#define QElemType int
#endif

#define QMAXSIZE 0x4
#define QINCSIZE 0x4

typedef struct{
	QElemType *base;
	QElemType *end;
	QElemType *front;
	QElemType *rear;
}Queue;

int InitQueue(Queue *Q)
{
	Q->base=malloc(sizeof(QElemType)*QMAXSIZE);
	if(!Q->base)
		return -1;
	Q->end=Q->base+QMAXSIZE-1;
	Q->front=Q->base;
	Q->rear=Q->base;
	return 0;
}

void DestroyQueue(Queue *Q)
{
	free(Q->base);
	Q->base=NULL;
	Q->end=NULL;
	Q->front=NULL;
	Q->rear=NULL;
}

void ClearQueue(Queue *Q)
{
	Q->rear=Q->front;
}

int EnQueue(Queue *Q, QElemType e)
{
	int size=Q->end-Q->base+1, front=Q->front-Q->base, rear=Q->rear-Q->base;
	QElemType *p;
	if((Q->rear+1)==Q->front || Q->rear==Q->end&&Q->front==Q->base){
		p=realloc(Q->base, (size+QINCSIZE)*sizeof(QElemType));
		if(!p)
			return -1;
		Q->base=p;
		Q->end=p+size+QINCSIZE-1;
		Q->front=p+front;
		Q->rear=p+rear;
		if(rear<front){
			memcpy(Q->base+size, Q->base, rear*sizeof(QElemType));
			Q->rear=Q->base+size+rear;
		}
	}
	*Q->rear++=e;
	if(Q->rear>Q->end)
		Q->rear=Q->base;
	return 0;
}

int DeQueue(Queue *Q, QElemType *e)
{
	if(Q->rear==Q->front)
		return -1;
	*e=*Q->front;
	Q->front = Q->front==Q->end ? Q->base : Q->front+1;
	return 0;
}

int QueueLength(Queue *Q)
{
	if(Q->rear>Q->front)
		return Q->rear-Q->front;
	else
		return Q->end-Q->front+1+Q->rear-Q->base;
}

QElemType* GetHead(Queue *Q)
{
	if(Q->front==Q->rear)
		return NULL;
	return Q->front;
}

int QueueTraverse(Queue *Q, int (*visit)(QElemType*))
{
	int tmp;
	QElemType *e=Q->front;
	while(e!=Q->rear){
		tmp=visit(e);
		if(tmp)
			return tmp;
		if(++e>Q->end)
			e=Q->base;
	}
	return 0;
}











#endif
