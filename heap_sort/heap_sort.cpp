#include "heap_sort.h"

#define VEC (*ppv)
int HI(int i){
	return 2*i+1;
}

int HD(int i){
	return 2*i+2;
}

void swap_(int **ppv,int i,int m){
	int temp=VEC[i];
	VEC[i]=VEC[m];
	VEC[m]=temp;
	return;
}

void heap_fy(int **ppv,int tam,int i){
	int m=i;
	if(HI(i)<tam && VEC[i]<VEC[HI(i)])
		m=HI(i);
	if(HD(i)<tam && VEC[m]<VEC[HD(i)])
		m=HD(i);
	if( m==i) 
		return;
	swap_(ppv,i,m);
	heap_fy(ppv,tam,m);
}

void make_heap(int** ppv,int tam){ // max_heap
	for(int i=tam/2;i>=0;i--)
		heap_fy(ppv,tam,i);
	return;

}

void heap_sort(int** ppv,int tam){
	int n=tam-1;
	make_heap(ppv,tam);
	for(int i=0;i<tam;i++){
		swap_(ppv,0,n);
		n--;
		heap_fy(ppv,n+1,0);
	}
	return;
}


#undef VEC
