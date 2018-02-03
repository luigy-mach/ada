#include "heap_sort.h"

int HI(int i){
	return 2*i+1;
}

int HD(int i){
	return 2*i+2;
}

void swap_(vector<int> &VEC,int i,int m){
	int temp=VEC[i];
	VEC[i]=VEC[m];
	VEC[m]=temp;
	return;
}

void heap_fy(vector<int> &VEC,int tam,int i){
	int m=i;
	if(HI(i)<tam && VEC[i]<VEC[HI(i)])
		m=HI(i);
	if(HD(i)<tam && VEC[m]<VEC[HD(i)])
		m=HD(i);
	if(m==i) 
		return;
	swap_(VEC,i,m);
	heap_fy(VEC,tam,m);
}

void make_heap(vector<int> &VEC){ // max_heap
	for(int i=VEC.size()/2; i>=0; i--)
		heap_fy(VEC,VEC.size(),i);
	return;

}

void heap_sort(vector<int> &VEC){
	int tam=VEC.size();
	int n=tam-1;
	make_heap(VEC);
	for(int i=0;i<tam;i++){
		swap_(VEC,0,n);
		n--;
		heap_fy(VEC,n+1,0);
	}
	return;
}


