#ifndef HEAP_SORT
#define HEAP_SORT

int HI(int i);
int HD(int i);

void swap_(int** ppv,int i,int m);
void heap_fy(int** ppv,int tam,int i);
void make_heap(int** ppv,int tam); // max_heap
void heap_sort(int** ppv,int tam);





#endif //HEAP_SORT
