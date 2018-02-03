#ifndef HEAP_BINOMIAL
#define HEAP_BINOMIAL

#include <iostream>
#include <map>
using namespace std;

template<typename T>
class BinomNode
{
public:
    T data;
    int degree;
    //-----------------
    int index;
    //-----------------
    BinomNode<T>* parent;
    BinomNode<T>* left_child;
    BinomNode<T>* right_sibling;
    BinomNode(T d):data(d),degree(0),parent(NULL),left_child(NULL),right_sibling(NULL),index(0) {};

};

template<typename T>
class BinomialHeap{
public:
    BinomNode<T>* head;
    BinomNode<T>* _min;
    //------------------------------	
    map< int,BinomNode<T>* > heap_index;
    int index;
    int get_size(){return heap_index.size();}
    //------------------------------	
     	
    void sort_degree(BinomNode<T>*&,BinomNode<T>*);
    void inner_insert(BinomNode<T>*);
    bool findMin(BinomNode<T>** &);
    void del_insert(BinomNode<T>*);
    void find_node(BinomNode<T>*,bool&,T,BinomNode<T>* &);
    void relocate(BinomNode<T>*);
    void updateMin();
    BinomNode<T>* union_heap(BinomNode<T>*,BinomNode<T>*);

public:

    BinomialHeap():head(NULL),_min(NULL),index(0){};
    void _insert(T);
    BinomNode<T>* minimum();
    BinomNode<T>* get_head();
    BinomNode<T>* extract_min();
    bool decrease_key(T,T);
    bool delete_key(T);
    bool buscar(T);
    //----------------------------
    void decrease_key(int,T);
    T* buscar2(int _index);
    void set_index();
    //----------------------------
    void print_head_list();
};

template<typename T>
void BinomialHeap<T>::sort_degree(BinomNode<T>* &p,BinomNode<T>*q)
{
    if(!p){p=q;}
    else if(p->degree>q->degree)
    {
        q->right_sibling=p, p=q;
    }
    else if(p->degree==q->degree)
    {
        BinomNode<T>* tmp=p;
        p=p->right_sibling;
        tmp=union_heap(tmp,q);
        inner_insert(tmp);
    }
    else{
        sort_degree(p->right_sibling,q);
    }
}

template<typename T>
BinomNode<T>* BinomialHeap<T>::union_heap(BinomNode<T>* p,BinomNode<T>* q)
{
        //p=tmp q=_new
        BinomNode<T>* tmp_left;
        if(p->data<q->data){
                tmp_left=p->left_child;
                p->left_child=q;
                q->right_sibling=tmp_left;
                q->parent=p;
                ++(p->degree);
                p->right_sibling=NULL;
                return p;
        }
        else{
                tmp_left=q->left_child;
                q->left_child=p;
                p->right_sibling=tmp_left;
                p->parent=q;
                ++(q->degree);
                q->right_sibling=NULL;
                return q;
        }
}


template<typename T>
void BinomialHeap<T>::inner_insert(BinomNode<T>* _new)
{
    if(_new)
    {
        if(!head){
            head=_new;
            _min=head;
        }

        else if(head->degree==_new->degree){
            BinomNode<T>* tmp=head;
            head=head->right_sibling;
            tmp=union_heap(tmp,_new);
            inner_insert(tmp);
        }
        else if(_new->degree>head->degree){
            sort_degree(head,_new);
        }
        else{
            _new->right_sibling=head;
            head=_new;
            if(_new->data<_min->data){
                _min=_new;
            }
        }
    }
}

template<typename T>
void BinomialHeap<T>::_insert(T d)
{
    BinomNode<T>* tmp=new BinomNode<T>(d);
    tmp->index=index;
    //--------------------------------
    heap_index.insert(pair< int,BinomNode<T>* >(index,tmp) );
    index++;
	
    //--------------------------------
    inner_insert(tmp);

}

template<typename T>
BinomNode<T>* BinomialHeap<T>::minimum()
{
    updateMin();
    return _min;
}

template<typename T>
BinomNode<T>* BinomialHeap<T>::get_head()
{
    return head;
}

template<typename T>
void BinomialHeap<T>::del_insert(BinomNode<T>* p)
{
    if(p)
    {
        BinomNode<T>* next=p->right_sibling;
        p->parent=NULL;
        p->right_sibling=NULL;
        if(next)
        {
            del_insert(next);
        }

        inner_insert(p);
    }
}

template<typename T>
bool BinomialHeap<T>::findMin(BinomNode<T>** &m)
{
    if(_min)
    {
        m=&head;
        while(*m){
                if((*m)->data==_min->data){
                    return true;
                }
                m=&((*m)->right_sibling);

        }
        return false;
    }
    return false;
}

template<typename T>
BinomNode<T>* BinomialHeap<T>::extract_min()
{
    BinomNode<T>** p;
    if(findMin(p)){
            BinomNode<T>* minn,*children;
            minn=*p;
            *p=(*p)->right_sibling;
            children=minn->left_child;
            minn->left_child=NULL;
            minn->right_sibling=NULL;

            if(children)
            {  del_insert(children);}
            //else{   updateMin();}

    	    //heap_index.erase(heap_index.find());
            return minn;
    }
    return NULL;
}

template<typename T>
void BinomialHeap<T>::find_node(BinomNode<T>* p,bool& found,T d,BinomNode<T>* &node)
{
    if(!found && p)
    {
        if(d>=p->data)
        {
            if(p->data==d){found=true; node=p;}
            else {find_node(p->left_child,found,d,node);}
        }
        find_node(p->right_sibling,found,d,node);
    }

}

template<typename T>
bool BinomialHeap<T>::buscar(T d)
{
    bool f=false;
    BinomNode<T>* prueba;
    find_node(head,f,d,prueba);
    return f;
}
//-------------------------------------------------------
//-------------------------------------------------------
template<typename T>
T* BinomialHeap<T>::buscar2(int _index)
{
    return &(heap_index.find(_index)->second->data);
}


template<typename T>
void BinomialHeap<T>::decrease_key(int _index,T _new)
{
    	BinomNode<T>* p=heap_index.find(_index)->second;	
		

    	typename map< int,BinomNode<T>* >::iterator it_1;
	typename map< int,BinomNode<T>* >::iterator it_2;
	BinomNode<T>* temp_b;
	
	if(_new<p->data)
	{
		p->data=_new;
       		 while(p->parent && (p->data < p->parent->data) )
       		 {
		        T temp=p->data;
			p->data=p->parent->data;
			p->parent->data=temp;

			int t=p->index;
			p->index=p->parent->index;
			p->parent->index=t;	

			//-----------------------------
			it_1=heap_index.find(p->index);
			p=p->parent;
			it_2=heap_index.find(p->index);
			temp_b=it_1->second;	
			it_1->second=it_2->second;
			it_2->second=temp_b;

			
        	}
	}	
	
	return ;
}


template<typename T>  //<-<<<<<<<<<< N cuadrado... demasciado costoso
void BinomialHeap<T>::set_index(){	
	
	map<int, BinomNode<T>* > my_map;
	typename map<int, BinomNode<T>* >::iterator it;
	for(it=heap_index.begin();it!=heap_index.end();it++){
		my_map.insert(pair< int, BinomNode<T>* >(it->second->index,it->second));
	}
	
	
}

//-------------------------------------------------------
//-------------------------------------------------------
template<typename T>
bool BinomialHeap<T>::decrease_key(T current,T _new)
{
    if(head)
    {
        bool f=false;
        BinomNode<T>* p=NULL;
        find_node(head,f,current,p);
        if(p)
        {
            if(_new<current)
            {
                p->data=_new;
                relocate(p);
                return true;
            }

        }
        return false;

    }
    return false;
}

template<typename T>
bool BinomialHeap<T>::delete_key(T key)
{
    if(decrease_key(key,-10000))
    {
        extract_min();
	
        return true;
    }
    return false;
}

template<typename T>
void BinomialHeap<T>::updateMin()
{
    if(head)
    {
        BinomNode<T>* tmp;
        _min=head;
        tmp=head->right_sibling;
        while(tmp)
        {
            if(_min->data>tmp->data)
            {
                _min=tmp;
            }
            tmp=tmp->right_sibling;
        }
    }
    else{
        _min=NULL;
    }
}

template<typename T>
void BinomialHeap<T>::print_head_list()
{
    if(head)
    {
        BinomNode<T>* tmp=head;
        //cout<<tmp->data<<" "<<"Grado: "<<tmp->degree<<" | ";
        while(tmp)
        {
            cout<<tmp->data<<" "<<"Grado: "<<tmp->degree<<" | ";
            tmp=tmp->right_sibling;
        }
        cout<<endl;
    }
}

template<typename T>
void BinomialHeap<T>::relocate(BinomNode<T>* p)
{
    if(p)
    {
        BinomNode<T>* par=p->parent;
        T tmp;
        while(par && p->data<par->data)
        {
            tmp=p->data;
            p->data=par->data;
            par->data=tmp;

            p=par;
            par=par->parent;
        }
        if(_min->data>p->data){_min=p;}
    }

}




#endif //HEAP_BINOMIAL
