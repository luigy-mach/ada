#ifndef GRAFO_DINAMICO
#define GRAFO_DINAMICO


#include<set>
#include<vector>
#include<map>
#include<iostream>
#include<string>

#include"fibonacciHeap.h"

using namespace std;

typedef long int size_index;



template<class V, class E>
class edge;

template<class V,class E>
class vertex{
	public:
		V m_data_vertex;
		set< edge<V,E> > m_edge_ady;	
		
		size_index index;

	public:
		vertex(V _d):m_data_vertex(_d),index(-1){}
		set< edge<V,E> > get_edges_ady()const {	return	m_edge_ady;}

		bool operator==(const vertex<V,E> & _v) const { return m_data_vertex == _v.m_data_vertex; }
		bool operator> (const vertex<V,E> & _v) const { return m_data_vertex >  _v.m_data_vertex; }
		bool operator< (const vertex<V,E> & _v) const { return m_data_vertex <  _v.m_data_vertex; }
		bool operator>=(const vertex<V,E> & _v) const { return m_data_vertex >= _v.m_data_vertex; }
		bool operator<=(const vertex<V,E> & _v) const { return m_data_vertex <= _v.m_data_vertex; }
		bool operator!=(const vertex<V,E> & _v) const { return m_data_vertex != _v.m_data_vertex; }
};

template<class V, class E>
class edge{
	public:
		E m_data_weight;
		vertex<V,E>* m_pVertex_i;
		vertex<V,E>* m_pVertex_f;
	public:	
		edge(E _e, vertex<V,E>* _pV_f=0, vertex<V,E>* _pV_ini=0){
			m_data_weight=_e;
			m_pVertex_f=_pV_f;
			m_pVertex_i=_pV_ini;;
		}
	
		bool operator==(const edge<V,E> & _e) const { return m_data_weight == _e.m_data_weight; }
		bool operator> (const edge<V,E> & _e) const { return m_data_weight >  _e.m_data_weight; }
		bool operator< (const edge<V,E> & _e) const { return m_data_weight <  _e.m_data_weight; }
		bool operator>=(const edge<V,E> & _e) const { return m_data_weight >= _e.m_data_weight; }
		bool operator<=(const edge<V,E> & _e) const { return m_data_weight <= _e.m_data_weight; }
		bool operator!=(const edge<V,E> & _e) const { return m_data_weight != _e.m_data_weight; }
		
};


//-----------------------------------------------------------------------------------
//------------------------------------------GRAFO NO DIRIGIDO------------------------------------
//-----------------------------------------------------------------------------------
template<class V, class E>
class grafo{
	public:
		set< vertex<V,E> > m_grafo;
	public:
		grafo(){};

		void insert_vertex(V _v){
			m_grafo.insert(vertex<V,E>(_v));
		}	

		bool find_vertex(vertex<V,E> _v, vertex<V,E> *& _pcVertex){
			typename set< vertex<V,E> >::iterator it;
			it=m_grafo.find(_v);
			bool c1 = (it != m_grafo.end());
			if(!c1) return false;
			_pcVertex = const_cast< vertex<V,E>* >(&(*it));
			return c1;	
		}


		void insert_edge(V _vi,V _vf, E _weight){
			vertex<V,E> * p; 
			vertex<V,E> * q; 
			bool c1 = find_vertex(vertex<V,E>(_vi),p);
			bool c2 = find_vertex(vertex<V,E>(_vf),q);
			if( c1 && c2 ){
				//por ser no dirigido - aristas no repetidas
				if(!p->m_edge_ady.find(_weight)){
					p->m_edge_ady.insert( edge<V,E>(_weight, q, p) );
				}
			}
		}
		
		void insert(){
			//insertar defrente
		}
	
		//----------------------------------------------------
		//-----------------------------------------------
		//-----------------------------------------------
		//----------------------------------------------------
		
		void tagger(){
			typename set< vertex<V,E> >::iterator it;
			size_index i=0;
			for(it=m_grafo.begin() ; it!=m_grafo.end() ; it++){
				const_cast< vertex<V,E>& >(*it).index=i;
				i++;	
			}
			return;
		}

		vector< edge<V,E>* > get_pEdge_ady(V _v){
			vertex<V,E>* vertex_temp = const_cast< vertex<V,E>* >(&(*m_grafo.find(_v)));
			vector< edge<V,E>* > vpedge;
			typename set< edge<V,E> >::iterator it;
			//aristas adyacentes sin bucles;	
			for(it=vertex_temp->m_edge_ady.begin();it!=vertex_temp->m_edge_ady.end() 
								&& it->m_pVertex_f!=vertex_temp ;it++)
				vpedge.push_back(const_cast< edge<V,E>* >(&(*it)));
			return vpedge;
		}
		/*
		set< edge<V,E>* > get_pEdge_ady(V _v){
			set<V,E>* vertex_temp = const_cast< vertex<V,E>* >(&(*m_grafo.find(_v)));
			set< edge<V,E>* > edges;
			typename set< edge<V,E> >::iterator it;
			//aristas adyacentes sin bucles;	
			for(it=vertex_temp->m_edge_ady.begin();it!=vertex_temp->m_edge_ady.end() 
								&& it->m_pVertex_f!=vertex_temp ;it++)
				edges.insert(const_cast< edge<V,E>* >(&(*it)));
			return edges;
		}
		*/
		map< size_index, vertex<V,E>* > get_pVertex(){
			tagger();
			map< size_index, vertex<V,E>* > map;
			typename set< vertex<V,E> >::iterator it;	
			for(it=m_grafo.begin();it!=m_grafo.end();it++){
				map.insert( pair< size_index,vertex<V,E>* >(it->index ,const_cast< vertex<V,E>* >(&(*it))) );
			}
			return map;
		}
			
		vertex<V,E>* find_pVertex(V _v){
			typename set< vertex<V,E> >::iterator it;
			it=m_grafo.find(vertex<V,E>(_v));	
			return const_cast< vertex<V,E>* >(&(*it));
		} 		

		size_index get_size(){
			return const_cast<size_index> (m_grafo.size());
		}
		

		//-----------------------------------------------
		//-----------------------------------------------
		//-----------------------------------------------
		//-----------------------------------------------

		void get_all_edges(FibonacciHeap< edge<V,E>* > & heap){
			map< size_index, vertex<V,E>* > vertex = get_pVertex();
			set< size_index > visited;
			size_index tam=get_size;
			for(size_index i=0 ; i<tam ; i++){
				visited.insert(i);
				vector< edge<V,E>* > ady = get_pEdge_ady(vertex.find(i)->second->m_data_pVertex);

				typedef typename vector< edge<V,E>* >::iterator it;
				it it_ady;
				for(it_ady=ady.begin() ; it_ady!=ady.end() ; it_ady++){
					if( visited.find(it_ady->m_pVertex_f->index)==visited.end() ){
						heap._insert(*it_ady);
					}
				}
				ady.clear();
			}
		}
		
		void mark_visited(set< size_index >& _visited, edge<V,E>& _e)const {
			vertex<V,E>* pi=_e.m_pVertex_i;
			vertex<V,E>* pf=_e.m_pVertex_f;
			if( _visited.find(pi->index)==_visited.end() ){
				_visited.insert(pi->index);
			}

			if( _visited.find(pf->index)==_visited.end() ){
				_visited.insert(pf->index);
			}
			
		}
			
		//revisar hay_ciclo_incompleto!!!!!
		bool has_a_cycle(set< size_index >& _visited, edge<V,E>& _e){
			vertex<V,E>* pi = _e.m_pVertex_i;
			vertex<V,E>* pf = _e.m_pVertex_f;
			if(_visited.find(pi->index)!=_visited.end() &&
			   _visited.find(pf->index)!=_visited.end()  ){
				return true;
			}
			else 
				return false;
		}

		void kruskal(){
			set< edge<V,E>* > _mst;
			set< size_index > _visited;
			FibonacciHeap< edge<V,E>* > min_heap;
			get_all_edges(min_heap);
	
			while(_visited.size==){
				edge<V,E> * edge_min = extract_min()->data;
				if(!has_a_cycle(_visited,edge_min)){
					_mst.insert(edge_min);
				}
			}
			
			return;
		}

};


#endif //GRAFO_DINAMICO
