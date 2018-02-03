#ifndef HEAP_SORT
#define HEAP_SORT

#include<vector>
using namespace std;

//----------------------------------------------
int HI(int i);
int HD(int i);

void swap_(vector<int> &VEC,int i,int m);
void heap_fy(vector<int> &VEC,int tam,int i);
void make_heap(vector<int> &VEC); // max_heap
void heap_sort(vector<int> &VEC);





#endif //HEAP_SORT
