#ifndef FIBONACCI_HEAP
#define FIBONACCI_HEAP

#include<map>
#include<iostream>
using namespace std;

template<typename T>
class FibNode{
public:

    T data;
    bool marked;
    int degree;
    //-----------------
    int index;
    //-----------------
    FibNode<T>* parent;
    FibNode<T>* prev;
    FibNode<T>* next;
    FibNode<T>* children;
    FibNode(T d):data(d),marked(false),degree(0),parent(0),prev(0),next(0),children(0){};
};

template<typename T>
class FibonacciHeap{
public:
    
    //------------------------------	
    map< int,FibNode<T>* > heap_index;
    int index;
    int get_size(){return heap_index.size();}
    //------------------------------	


    FibNode<T>* head;
    FibNode<T>* _min;

    void inner_insert(FibNode<T>*);
    FibNode<T>* union_heap(FibNode<T>*,FibNode<T>*);
    void insert_sort(FibNode<T>* &,FibNode<T>*);
    void find_node(FibNode<T>*,bool&,T,FibNode<T>* &);
    void start_sort();
    void moveUp(FibNode<T>*);
    void fix_decrease(FibNode<T>*);
public:
    //----------------------------
    void decrease_key2(int,T);
    T* buscar2(int _index);
    void set_index();
    FibNode<T>* minimum();
    //----------------------------

    FibonacciHeap():head(0),_min(0),index(0){};
    void _insert(T d);
    FibNode<T>* get_min();
    FibNode<T>* extract_min();
    bool decrease_key(T d,T _new);
    bool delete_key(T d);

    void head_list();
};


template<typename T>
bool FibonacciHeap<T>::delete_key(T d)
{
    if(decrease_key(d,-10000))
    {
        extract_min();
        return true;
    }
    return false;

}


template<typename T>
FibNode<T>* FibonacciHeap<T>::get_min()
{
    return _min;
}

template<typename T>
FibNode<T>* FibonacciHeap<T>::extract_min()
{
    if(!_min)
    {
        return NULL;
    }
    else{
        FibNode<T> *tmp,*prev,*next,*children,*child;
        tmp=_min;

        prev=tmp->prev;
        next=tmp->next;
        children=tmp->children;

        tmp->prev=NULL;
        tmp->next=NULL;
        tmp->children=NULL;
        tmp->degree=0;

        if(!prev)
        {
            head=next;
            if(next){next->prev=head;}
        }
        else{
            prev->next=next;
            if(next) {next->prev=prev;}
        }

        _min=NULL;
        start_sort();

        while(children)
        {
            child=children->next;
            children->next=NULL;
            children->prev=NULL;
            children->parent=NULL;
            insert_sort(head,children);
            children=child;
        }
        return tmp;
    }
}

template<typename T>
void FibonacciHeap<T>::_insert(T d)
{
    FibNode<T>* tmp=new FibNode<T>(d);
    inner_insert(tmp);
    
   //--------------------------------
    heap_index.insert(pair< int,FibNode<T>* >(index,tmp) );
    index++;
	
    //--------------------------------


}

template<typename T>
void FibonacciHeap<T>::insert_sort(FibNode<T>* &p,FibNode<T>* q)
{
    if(!p)
    {
        p=q;
        _min=p;
    }
    else if(p->degree>q->degree)
    {
        q->next=p;
        p->prev=q;
        p=q;
        if(q->data<_min->data)
        {
            _min=q;
        }
    }
    else if(p->degree==q->degree)
    {
        FibNode<T>* tmp=p;
        p=p->next;
        tmp->next=NULL;
        tmp->prev=NULL;
        tmp=union_heap(tmp,q);
        insert_sort(p,tmp);

    }
    else{
        insert_sort(p->next,q);
    }

}

template<typename T>
void FibonacciHeap<T>::start_sort()
{
    if(head)
    {
        FibNode<T>* tmp,*tmp2;
        tmp=head;
        head=NULL;
        _min=NULL;

        while(tmp)
        {
            tmp2=tmp->next;
            tmp->next=NULL;
            tmp->prev=NULL;
            insert_sort(head,tmp);
            tmp=tmp2;
        }
    }
}

template<typename T>
FibNode<T>* FibonacciHeap<T>::union_heap(FibNode<T>* p,FibNode<T>* q)
{
    FibNode<T>* tmp_children;
    if(p->data<q->data)
    {
        tmp_children=p->children;
        p->children=q;
        q->parent=p;
        q->next=tmp_children;
        ++(p->degree);
        if(tmp_children){
            tmp_children->prev=q;
        }
        return p;
    }
    else{

        tmp_children=q->children;
        q->children=p;
        p->parent=q;
        p->next=tmp_children;
        ++(q->degree);
        if(tmp_children){
            tmp_children->prev=p;
        }
        return q;

    }
}

template<typename T>
void FibonacciHeap<T>::inner_insert(FibNode<T>* p)
{
    if(p){
        if(!head){
            head=p;
            _min=head;
        }
        else{
            if(p->data<_min->data)
            {
                _min=p;
            }
            p->next=head;
            head->prev=p;
            head=p;
        }
    }

}

template<typename T>
void FibonacciHeap<T>::head_list()
{
    FibNode<T>* tmp=head;
    while(tmp)
    {
        cout<<"Key: "<<tmp->data<<" Degree: "<<tmp->degree<<" ||";
        tmp=tmp->next;
    }
    cout<<endl;
}

template<typename T>
void FibonacciHeap<T>::find_node(FibNode<T>* p,bool& found,T d,FibNode<T>* &node)
{
    if(!found && p)
    {
        if(d>=p->data)
        {
            if(p->data==d){found=true; node=p;}
            else {find_node(p->children,found,d,node);}
        }
        find_node(p->next,found,d,node);
    }

}



template<typename T>
void FibonacciHeap<T>::moveUp(FibNode<T>* p)
{
    if(p)
    {
        FibNode<T>* prev,*next,*parent;
        prev=p->prev;
        next=p->next;
        parent=p->parent;

        p->prev=NULL;
        p->next=NULL;
        p->parent=NULL;
        p->marked=false;

        if(!prev)
        {
            parent->children=next;
        }
        else{
            prev->next=next;
        }

        if(next) {next->prev=prev;}
        --(parent->degree);
        inner_insert(p);
    }

}

template<typename T>
void FibonacciHeap<T>::fix_decrease(FibNode<T>* p)
{
    if(p)
    {
        FibNode<T>* parent=p->parent;
        if(parent)
        {
            moveUp(p);
            if(!(parent->marked) && parent->parent)
            {
                parent->marked=true;
            }
            else{
                fix_decrease(parent);
            }
        }
    }

}


template<typename T>
bool FibonacciHeap<T>::decrease_key(T d,T _new)
{
    FibNode<T>* p=NULL;
    bool f=false;
    find_node(head,f,d,p);
    if(p)
    {
        FibNode<T>* par=p->parent;
        if(p->data>_new)
        {
            p->data=_new;
            if(!par)
            {
                if(p->data<_min->data){
                    _min=p;
                }
            }
            else if(par->data>p->data)
            {
                fix_decrease(p);

            }
            return true;
        }
        else{
            return false;
        }
    }
    return false;
}


//-------------------------------------------------------
//-------------------------------------------------------


template<typename T>
void FibonacciHeap<T>::decrease_key2(int _index,T _new) 
{
  	typename map< int,FibNode<T>* >::iterator it_1 = heap_index.find(_index);
    	FibNode<T>* p = it_1->second;	
	//cout<<"++++"<< p->data.index <<" "<<p->data.accumulate<<endl;	

	    if(it_1!=heap_index.end())
	    {
		FibNode<T>* par=p->parent;
		if(p->data>_new)
		{
		    p->data=_new;
		    if(!par)
		    {
		        if(p->data<_min->data){
		            _min=p;
		        }
		    }
		    else if(par->data > p->data)
		    {
		        fix_decrease(p);

		    }
		    return;
		}
		else{
		    return;
		}
	    }
	    return ;


	return ;
}


template<typename T>
T* FibonacciHeap<T>::buscar2(int _index)
{
    return &(heap_index.find(_index)->second->data);
}


template<typename T>  //<-<<<<<<<<<< N cuadrado... demasciado costoso
void FibonacciHeap<T>::set_index(){	
	
	map<int, FibNode<T>* > my_map;
	typename map<int, FibNode<T>* >::iterator it;
	for(it=heap_index.begin();it!=heap_index.end();it++){
		my_map.insert(pair< int, FibNode<T>* >(it->second->index,it->second));
	}
	
	
}

template<typename T>
FibNode<T>* FibonacciHeap<T>::minimum(){
	return get_min();		
}

//-------------------------------------------------------
//-------------------------------------------------------



#endif //FIBONACCI_HEAP
