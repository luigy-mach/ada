


#include <iostream>
#include "grafo_dinamico.h"
#include<set>
#include<map>


using namespace std;






int main(){

	grafo<int,int> g;	
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
	g.insert_edge(6,4,1);

	g.print();
	//---------------------------
	
	g.print_dijkstra(0);
	
	return 0;
}
