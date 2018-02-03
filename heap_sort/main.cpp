#include "heap_sort.h"

#include<iostream>
#include<stdlib.h>

using namespace std;

void mostrar_vector(int** ppv,int tam){
	#define VEC2 (*ppv) 
	for(int i=0;i<tam;i++)	
		cout<<" "<<VEC2[i];
	cout<<endl;
	#undef VEC2
}

int main(){
	
	int tam=16;

	int *pv= new int[tam];
	
	for (int i=0;i<tam;i++)
		//pv[i]=tam-i;
		pv[i]=rand()%tam;
	mostrar_vector(&pv,tam);
	heap_sort(&pv,tam);
	mostrar_vector(&pv,tam);

	return 0;
}
