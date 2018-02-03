#ifndef BINARY_HEAP
#define BINARY_HEAP

#include<vector>
#include<iostream>
using namespace std;

class binary_heap{

	vector<int> VEC;
	
public:
	binary_heap(){}
	int HD(int i);
	int HI(int i);
	void show();
	void swap(int a,int b);
	void heap_fy(int i);
	void insert(int x);
	void make_heap(int i);
	void decrease_key(int pos_i,int new_key);
	void delete_min();
};




#endif //BINARY_HEAP
