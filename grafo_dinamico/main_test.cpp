#include "heap_binomial.h"

#include<iostream>
using namespace std;


//-----------------------------------------------------
struct a{
	int acumulado;
	int index;
	bool operator<(a& _x){
		return acumulado < _x.acumulado;
	}
	
	bool operator>(a& _x){
		return acumulado > _x.acumulado;
	}

	bool operator==(a& _x){
		return acumulado == _x.acumulado;
	}
	
	bool operator!=(a& _x){
		return acumulado != _x.acumulado;
	}

	bool operator>=(a& _x){
		return acumulado >= _x.acumulado;
	}

	bool operator<=(a& _x){
		return acumulado <= _x.acumulado;
	}
};

int main()
{

	a a1;
	a a2;
	a a3;
	a a4;
	a a5;
	a a6;
	a a7;
	a a8;
	a a9;

	a1.acumulado=10;
	a2.acumulado=16;
	a3.acumulado=1;
	a4.acumulado=-3;

	a5.acumulado=-2;
	a5.index=10;

	a6.acumulado=-2;
	a6.index=11;

	a7.acumulado=5;
	a8.acumulado=2;
	a9.acumulado=1;

	BinomialHeap<a> heap;
	heap._insert(a1);
	heap._insert(a2);
	heap._insert(a3);
	heap._insert(a4);
	heap._insert(a5);
	heap._insert(a6);
	heap._insert(a7);
	heap._insert(a8);
	heap._insert(a9);
	

	
	cout<<heap.buscar2(0)->acumulado<<endl;
	//cout<<heap.buscar2(18)->acumulado<<endl;
	cout<<heap.buscar2(2)->acumulado<<endl;
	cout<<heap.buscar2(3)->acumulado<<endl;
	cout<<"tamano : "<<heap.index<<endl;	


	cout<<"-------------->>"<<endl;
	BinomNode<a>* p=heap.minimum(); 
	cout<<" "<<p->data.acumulado<<endl;
	heap.extract_min();
	/*
	cout<<"--------------->>"<<endl;
	p=heap.minimum(); 
	cout<<" "<<p->data.acumulado<<endl;
	cout<<" 	"<<p->data.index<<endl;
	heap.extract_min();

	cout<<"--------------->>"<<endl;
	p=heap.minimum(); 
	cout<<" "<<p->data.acumulado<<endl;
	cout<<"		"<<p->data.index<<endl;
	heap.extract_min();

	cout<<"--->>"<<endl;
	heap.extract_min();
	p=heap.minimum(); 
	cout<<" "<<p->data.acumulado<<endl;
	*/

	cout<<"*********************>"<<endl;
	BinomNode<a>* pp;
	a _old;
	  _old.acumulado=10;

	a _new;
          _new.acumulado=-1;
		

	if(heap.buscar(_old)){
		heap.decrease_key(_old,_new);
		p=heap.minimum(); 
		cout<<" "<<p->data.index<<endl;
		cout<<" "<<p->data.acumulado<<endl;
	}
		
	if(!heap.buscar(_old))
		cout<<"no esta"<<endl;
	
	cout<<"*********************>"<<endl;
	//-------------------------------------------
	//-------------------------------------------
	//-------------------------------------------
	  BinomialHeap<int> heap2;

    for(int i=10;i<=120;i+=10)
    {
        heap2._insert(i);
    }

    BinomNode<int>* m;
    heap2.print_head_list();
    m=heap2.minimum();
    cout<<"Now min: "<<m->data<<endl;

    cout<<endl;
    heap2.decrease_key(100,0);	
    heap2.decrease_key(80,-1);	
    //heap.extract_min();
    heap2.print_head_list();
    m=heap2.minimum();
    cout<<"Later min: "<<m->data<<endl;

    return 0;
}
