#ifndef BINOMIAL_HEAP
#define BINOMIAL_HEAP

#define NULL 0


class node{

public:
	int key;
	int degree;
	node* parent;
	node* child;
	node* sibling;
	node(int _key=0);
};


class binomial_heap{
	
	node* H;

public:	
	//MAKE-UP... creayt retorna un nuevo heap sin elementos
	node* makeheap();
	//INSERT(H,x) inserta nodo x, cuya clave estara en H
	node* insert(int key);
	//MINIMUM(H) retorna un puntero del nodo en el heap H cuyo valor es minimo
	node* minimum(node* H=0);
	node* minimun(node*& leftH, node*H=0);
	//EXTRACT_MIN(H) borra el nodo del heap H cuyo valor es minimo, retornando un puntero al nodo
	void extracMIN();
	//UNION(H1,H2) crea y retona un nuevo heap que contiene los nodos de los heap H1 H2, H1 y H2 son destruidos por esta operacion
	void merge(node*& H1, node*& H2);
	//DECREASE-KEY(H,x,k) asigna al nodo x un nuevo valor k, donde k es menor q el valor actual del nodo 
	void decrease_key(node* x,int k);
	//DELETE(H,x) borra el nodo x del heap H
	void delete_key(node* x);

	/////////////////////
	node* union_h(node* H, node* H2);
	void link(node* y, node* z);

};




#endif //BINOMIAL_HEAP
