#include "binary_heap.h"

int binary_heap::HD(int i){
	return 2*i+1;
}

int binary_heap::HI(int i){
	return 2*i+2;
}

void binary_heap::show(){
	for(int i=0;i<VEC.size();i++)
		cout<<" "<<VEC[i];
	cout<<endl;

}
void binary_heap::swap(int a, int b){
	int temp=VEC[a];
	VEC[a]=VEC[b];
	VEC[b]=temp;
}

void binary_heap::heap_fy(int i){
	int m=i;
	int tam=VEC.size();
	if(tam>HI(i) && VEC[i]>VEC[HI(i)])
		m=HI(i);
	if(tam>HD(i) && VEC[m]>VEC[HD(i)])
		m=HD(i);
	if(m==i) 
		return;
	swap(i,m);
	heap_fy(m);
}

void binary_heap::insert(int x){
	VEC.push_back(x);
	for(int i=VEC.size()/2;i>=0;i--)
		heap_fy(i);		
}

void binary_heap::make_heap(int i){
	for(int i=i/2;i>=0;i--)
		heap_fy(i);
}

void binary_heap::decrease_key(int pos_i,int new_key){
	if(pos_i>VEC.size())
		return;
	VEC[pos_i]=new_key;
	make_heap(pos_i);
}


void binary_heap::delete_min(){
	swap(0,VEC.size()-1);	
	VEC.pop_back();
	make_heap(VEC.size()-1);
}



