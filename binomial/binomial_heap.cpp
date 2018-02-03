#include "binomial_heap.h"



//--------------------------------------------------------
//----------------NODE
//--------------------------------------------------------

node::node(int _key){
	key=_key;
	parent=NULL;
	child=NULL;
	sibling=NULL;
	degree=0;
}


//--------------------------------------------------------
//----------------BINOMIAL
//--------------------------------------------------------


	//MAKE-UP... creayt retorna un nuevo heap sin elementos
	node* binomial_heap::makeheap(){}
	//INSERT(H,x) inserta nodo x, cuya clave estara en H
	node* binomial_heap::insert(int key){}
	//MINIMUM(H) retorna un puntero del nodo en el heap H cuyo valor es minimo
	node* binomial_heap::minimum(node* H){}
	node* binomial_heap::minimun(node*& leftH, node*H){}
	//EXTRACT_MIN(H) borra el nodo del heap H cuyo valor es minimo, retornando un puntero al nodo
	void binomial_heap::extracMIN(){}
	//UNION(H1,H2) crea y retona un nuevo heap que contiene los nodos de los heap H1 H2, H1 y H2 son destruidos por esta operacion
	void binomial_heap::merge(node*& H1, node*& H2){}
	//DECREASE-KEY(H,x,k) asigna al nodo x un nuevo valor k, donde k es menor q el valor actual del nodo 
	void binomial_heap::decrease_key(node* x,int k){}
	//DELETE(H,x) borra el nodo x del heap H
	void binomial_heap::delete_key(node* x){}

	/////////////////////
	node* binomial_heap::union_h(node* H, node* H2){}
	void binomial_heap::link(node* y, node* z){}


