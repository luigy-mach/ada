


#include <iostream>
#include "grafo_dinamico.h"
#include<set>
#include<map>
#include<stdlib.h>
#include<time.h>

#include<cmath>


using namespace std;

#include<time.h>


typedef long int my_size;



double ejecutar(){

/*	grafo<int,int> g;	
	g.insert_vertex(0);
	g.insert_vertex(1);
	g.insert_vertex(2);
	g.insert_vertex(3);
	g.insert_vertex(4);
	g.insert_vertex(5);
	g.insert_vertex(6);
	g.insert_edge(0,1,1);
	g.insert_edge(0,2,2);
	g.insert_edge(1,0,1);
	g.insert_edge(1,4,2);
	g.insert_edge(1,3,3);
	g.insert_edge(2,0,2);
	g.insert_edge(2,4,2);
	g.insert_edge(2,6,1);
	g.insert_edge(3,1,3);
	g.insert_edge(3,5,1);
	g.insert_edge(4,1,2);
	g.insert_edge(4,2,2);
	g.insert_edge(4,5,1);
	g.insert_edge(4,6,1);
	g.insert_edge(5,3,1);
	g.insert_edge(5,4,1);
	g.insert_edge(6,2,1);
	g.insert_edge(6,4,1);/
	g.print();
*/
	
	my_size num_vertex=10000000;
	int tam_max_aristas=50;

	grafo<my_size,my_size> g;	

	//-----------------------------------
	srand(time(NULL));

	my_size tam=sqrt(num_vertex);
	
	my_size tam_matriz=tam*tam;
	for(my_size i=0;i<tam_matriz;i++)
		g.insert_vertex(i);

		//--------------------------------	
		/*
				
			1  - 2  - 3  - 4  - 5
			|    |    |    |    |	
			6  - 7  - 8  - 9  - 10
			|    |    |    |    |	
			11 - 12 - 13 - 14 - 15
			|    |    |    |    |	
			16 - 17 - 18 - 19 - 20
			|    |    |    |    |	
			21 - 22 - 23 - 24 - 25
		*/
	my_size id=0;
	for(my_size i=0;i<tam;i++){
		for(my_size j=0;j<tam;j++){
			if(id-1>=0 && (id-1)%tam!=(tam-1) )
				g.insert_edge(id,id-1,rand()%tam_max_aristas+1);
			if(id+1<=num_vertex && (id+1)%tam!=0)
				g.insert_edge(id,id+1,rand()%tam_max_aristas+1);
			if(id-tam>=0)
				g.insert_edge(id,id-tam,rand()%tam_max_aristas+1);
			if(id+tam<=num_vertex)
				g.insert_edge(id,id+tam,rand()%tam_max_aristas+1);
			
			id++;
		}
	}
	
	//---------------------------



	clock_t start, finish;
	start = clock();
	//---------------------------
		g.dijkstra(0);
	//---------------------------
	finish = clock();
	double tiempo_total=((double)(finish-start))/CLOCKS_PER_SEC;
	cout<< tiempo_total<<endl;
	
	
	return tiempo_total;
}


int main(int argc, char *argv[]){


	int num_rep=1;
	double promedio=0;
	for(int i=0;i<num_rep;i++){
		promedio=promedio+ejecutar();
	}
	cout<<"-------------------------------"<<endl;
	cout<<promedio/num_rep<<endl;
	
	

	return 0;
}

