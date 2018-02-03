#include "heap_sort.h"

#include<iostream>
#include<stdlib.h>
#include<vector>

using namespace std;

void mostrar_vector(vector<int>& VEC2){
	for(int i=0;i<VEC2.size();i++)	
		cout<<" "<<VEC2[i];
	cout<<endl;
}

int main(){
	
	vector <int> v;
	int tam=16;
	
	for (int i=0;i<tam;i++)
		v.push_back(rand()%tam);

	mostrar_vector(v);
	heap_sort(v);
	mostrar_vector(v);

	return 0;
}
