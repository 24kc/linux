#ifndef _PSORT_H_
#define _PSORT_H_

#ifndef _PRAND_H_
#include </home/lxll/c/git/include/prand.h>
#endif

#ifndef _PMACRO_H_
#include </home/lxll/c/git/include/pMacro.h>
#endif

void pranda(int *arr, int n, int max)
{
	int i;
	if(max<0)
		max=PRAND_MAX;
	else
		max++;
	for(i=0;i<n;i++)
		arr[i]=prand()%max;
}

void PrintArray(int *arr, int n)
{
	int i;
	for(i=0;i<n;i++)
		printf("%d ", arr[i]);
	putchar('\b');
}
#define PrintArray_ln(a,n) (PrintArray(a,n), ln())

void CopyArray(int *a, int *b, int n)
{
	int i;
	for(i=0;i<n;i++)
		a[i]=b[i];
}

void BubbleSort_O(int *a, int n, int *cmp, int *mov)
{
	int _cmp=0, _mov=0;
	int i, j, tmp;
	n--, _mov++;
	for(i=0,_mov++;(_cmp++,i<n);i++,_mov++)
		for(j=0,_mov++;(_cmp++,j<n-i);j++,_mov++)
			if((_cmp++, a[j]>a[j+1]))
				tmp=a[j], a[j]=a[j+1], a[j+1]=tmp, _mov+=3;
	if(cmp)
		*cmp=_cmp;
	if(mov)
		*mov=_mov;
}
#define BubbleSort(a,n) BubbleSort_O(a,n,NULL,NULL)

void InsertSort_O(int *a, int n, int *cmp, int *mov)
{
	int _cmp=0, _mov=0;
	int i, j, k, tmp;
	for(i=1,_mov++;(_cmp++,i<n);i++,_mov++){
		for(j=0,_mov++;(_cmp++,j<i);j++,_mov++)
			if((_cmp++,a[i]<a[j]))
				break;
		tmp=a[i], _mov++;
		for(k=i,_mov++;(_cmp++,k>j);k--,_mov++)
			a[k]=a[k-1], _mov++;
		a[j]=tmp, _mov++;
	}
	if(cmp)
		*cmp=_cmp;
	if(mov)
		*mov=_mov;
}
#define InsertSort(a,n) InsertSort_O(a,n,NULL,NULL)

void SelectSort_O(int *a, int n, int *cmp, int *mov)
{
	int _cmp=0, _mov=0;
	int i, j, k, tmp;
	n--, _mov++;
	for(i=0,_mov++;(_cmp++,i<n);i++,_mov++){
		for(j=i,k=i,_mov+=2;(_cmp++,j<=n);j++,_mov++)
			if((_cmp++,a[j]<a[k]))
				k=j, _mov++;
		tmp=a[i], a[i]=a[k], a[k]=tmp, _mov+=3;
	}
	if(cmp)
		*cmp=_cmp;
	if(mov)
		*mov=_mov;
}
#define SelectSort(a,n) SelectSort_O(a,n,NULL,NULL)

void QuickSort_O(int *a, int n, int *cmp, int *mov)
{
	int _cmp=0, _mov=0;
	int pivot, tmp, *tail;
	int* Partition(int* left, int* right)
	{
		_mov+=(4+2);
		pivot=*right, _mov++;
		for(tail=left,_mov++;(_cmp++,left<right);left++,_mov++)
			if((_cmp++,*left<=pivot)){
				tmp=*left;
				*left=*tail;
				*tail++=tmp;
				_mov+=4;
			}
		tmp=*right, *right=*tail, *tail=tmp, _mov+=3;
		return tail;
	}
	void QuickSort(int* left, int*right)
	{
		_mov+=(4+2);
		if((_cmp++,left>=right))
			return;
		int *_pivot=Partition(left, right);
		_mov++;
		QuickSort(left, _pivot-1);
		QuickSort(_pivot+1, right);
	}
	QuickSort(a, a+n-1);
	if(cmp)
		*cmp=_cmp;
	if(mov)
		*mov=_mov;
}
#define QuickSort(a,n) QuickSort_O(a,n,NULL,NULL)

void ShellSort_O(int *a, int n, int *cmp, int *mov)
{
	



















#endif
