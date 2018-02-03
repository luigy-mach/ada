#include "binary_heap.h"

#include<stdlib.h>
using namespace std;


int main(){
	
	binary_heap min;
	int tam=9;
	for(int i=0;i<tam;i++)
		min.insert(rand()%tam);	
	min.show();
	min.delete_min();
	min.delete_min();
	min.delete_min();
	min.show();


	return 0;
}
