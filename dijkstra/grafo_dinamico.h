#ifndef GRAFO_DINAMICO
#define GRAFO_DINAMICO


#include<set>
#include<vector>
#include<queue>
#include<map>
#define INF 10000

#include<iostream>
#include<fstream>

using namespace std;


template<class V, class E>
class edge;

template<class V,class E>
class vertex{
	public:
		V m_data_vertex;
		set< edge<V,E> > m_edge_ady;	
		
		int index;
	public:
		vertex(V _d):m_data_vertex(_d),index(-1){}
		set< edge<V,E> > get_edges_ady()const {
			return	m_edge_ady;
		}
		bool operator==(const vertex<V,E> & _v) const {return m_data_vertex == _v.m_data_vertex  ;}
		bool operator>(const vertex<V,E> & _v) const {return  m_data_vertex > _v.m_data_vertex  ;}
		bool operator<(const vertex<V,E> & _v) const {return  m_data_vertex < _v.m_data_vertex  ;}
		bool operator>=(const vertex<V,E> & _v) const {return  m_data_vertex >= _v.m_data_vertex  ;}
		bool operator<=(const vertex<V,E> & _v) const {return  m_data_vertex <= _v.m_data_vertex  ;}
		bool operator!=(const vertex<V,E> & _v) const {return  m_data_vertex != _v.m_data_vertex  ;}
};

template<class V, class E>
class edge{
	public:
		E m_data_weight;
		vertex<V,E>* m_pVertex;
	public:	
		edge(E _e, vertex<V,E>* _pV=0){
			m_data_weight=_e;
			m_pVertex=_pV;
		}
	
		bool operator==(const edge<V,E> & _v) const {return m_pVertex->m_data_vertex == _v.m_pVertex->m_data_vertex  ;}
		bool operator> (const edge<V,E> & _v) const {return m_pVertex->m_data_vertex > _v.m_pVertex->m_data_vertex  ;}
		bool operator< (const edge<V,E> & _v) const {return m_pVertex->m_data_vertex < _v.m_pVertex->m_data_vertex  ;}
		bool operator>=(const edge<V,E> & _v) const {return m_pVertex->m_data_vertex >= _v.m_pVertex->m_data_vertex  ;}
		bool operator<=(const edge<V,E> & _v) const {return m_pVertex->m_data_vertex <= _v.m_pVertex->m_data_vertex  ;}
		bool operator!=(const edge<V,E> & _v) const {return m_pVertex->m_data_vertex != _v.m_pVertex->m_data_vertex  ;}
		
};


//-----------------------------------------------------------------------------------
//------------------------------------------GRAFO------------------------------------
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
			if(!c1) return c1;
			_pcVertex = const_cast< vertex<V,E>* >(&(*it));
			return c1;	
		}

		void insert_edge(V _vi,V _vf, E _weight){
			vertex<V,E> * p; 
			vertex<V,E> * q; 
			bool c1 = find_vertex(vertex<V,E>(_vi),p);
			bool c2 = find_vertex(vertex<V,E>(_vf),q);
			if( c1 && c2 ){
				p->m_edge_ady.insert( edge<V,E>(_weight, q) );
			}
		}
	
		void print(){
			typename set< vertex<V,E> >::iterator it1;	
			typename set< edge<V,E> >::iterator it2;
			for(it1=m_grafo.begin();it1!=m_grafo.end();it1++){			
				for(it2=it1->m_edge_ady.begin();it2!=it1->m_edge_ady.end();it2++){
					cout<< it1->m_data_vertex <<"---"<< it2->m_data_weight 
					    <<"---"<< it2->m_pVertex->m_data_vertex <<endl;
				}
			}
		}

		//----------------------------------------------------
		//-----------------------------------------------
		//-----------------------------------------------
		//----------------------------------------------------
		
		void indexer(){
			typename set< vertex<V,E> >::iterator it;
			int i=0;
			for(it=m_grafo.begin() ; it!=m_grafo.end() ; it++){
				const_cast< vertex<V,E>& >(*it).index=i;
				//cout<<" "<< it->index << endl;
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
								&& it->m_pVertex!=vertex_temp ;it++)
				vpedge.push_back(const_cast< edge<V,E>* >(&(*it)));
			return vpedge;
		}
		
		map< int, vertex<V,E>* > get_pVertex(){
			indexer();
			map< int, vertex<V,E>* > map;
			typename set< vertex<V,E> >::iterator it;	
			for(it=m_grafo.begin();it!=m_grafo.end();it++){
				map.insert( pair< int,vertex<V,E>* >(it->index ,const_cast< vertex<V,E>* >(&(*it))) );
			}
			return map;
		}
			
		vertex<V,E>* find_pVertex(V _v){
			typename set< vertex<V,E> >::iterator it;
			it=m_grafo.find(vertex<V,E>(_v));	
			return const_cast< vertex<V,E>* >(&(*it));
		} 		

		int get_size(){
			return m_grafo.size();
		}

		//-----------------------------------------------
		//-----------------------------------------------
		//-----------------------------------------------
		//-----------------------------------------------
		class label{
			public:
			int parent;
			int accumulate;
			int index;
			label(){
				parent=-1;
				accumulate=INF;
				index=-1;
			}
			label(int _index, int _parent,int _accumulate){
				parent=_parent;
				accumulate=_accumulate,
				index=_index;
			}
			bool operator<(const label& b) {return accumulate < b.accumulate;}
			bool operator>(const label& b) {return accumulate > b.accumulate;}
			bool operator<=(const label& b) {return accumulate <= b.accumulate;}
			bool operator>=(const label& b) {return accumulate >= b.accumulate;}
			bool operator==(const label& b) {return accumulate == b.accumulate;}
			bool operator!=(const label& b) {return accumulate != b.accumulate;}
			label& operator=(const label& b) {index=b.index;parent=b.parent;accumulate=b.accumulate;}
		};
			

		void init(){
		


		};

		int extract_min( map< int,vertex<V,E>* > & _v ,label _label[])
		{
			typename map<int, vertex<V,E>* >::iterator it;
			label temp;//empieza con infinito
			for(it=_v.begin();it!=_v.end();it++){
				int current=it->first;
				if(temp.accumulate>_label[current].accumulate)
					temp=_label[current];
			}
			
			return temp.index;
		}


		map<int,label> dijkstra(int _v_princ)
		{
	//		cout<<"		entrando a dijkstra"<<endl;
			map<int, label> map_distances;
			//get_pVertex----->>>> indexa;
			map<int, vertex<V,E>* > vertexs = get_pVertex();
			typename map<int, vertex<V,E>* >::iterator it_vertexs;
			if(vertexs.empty())
				return map_distances;
			//----------------------------------------------------------
			
			int tam=vertexs.size();
			
			label labels[tam];			
		//	cout<<"---------------------------------"<<endl;

			/*r(int i=0;i<tam;i++){
				label temp;// parent=-1,index=-1,accu=INF;
				temp.index=it_vertexs->first;
				labels[i]=temp;
			}*/
			//------------------------------------------------------------
		//	for(int i=0;i<tam;i++)	cout<<" 	 "<<labels[i].index;	cout<<endl;
		//	for(int i=0;i<tam;i++)	cout<<" 	 "<<labels[i].parent; cout<<endl;
		//	for(int i=0;i<tam;i++)	cout<<" 	 "<<labels[i].accumulate; cout<<endl;

			//-------------------------------------------------
			label _new;
			      _new.index=0;
			      _new.parent=0;
			      _new.accumulate=0;

	//			cout<<"		>"<<_new.index<<endl;
	//			cout<<"		>"<<_new.parent<<endl;
	//			cout<<"		>"<<_new.accumulate<<endl;

			labels[_new.index]=_new;
			//---------------------------------------

			while(!vertexs.empty())
			{
		//		cout<<"		while_dijkstra"<<endl;
				
		//	for(int i=0;i<tam;i++) 	cout<<" 	 "<<labels[i].index;	cout<<endl;
		//	for(int i=0;i<tam;i++)	cout<<" 	 "<<labels[i].parent; cout<<endl;
		//	for(int i=0;i<tam;i++)	cout<<" 	 "<<labels[i].accumulate; cout<<endl;

				//---------------------
				int minimum=extract_min(vertexs,labels);
		//		cout<<" "<<minimum<<endl;
				//---------------------
				label l_marked =labels[minimum];
		//		cout<<"		>"<<l_marked.index<<endl;
		//		cout<<"		>"<<l_marked.parent<<endl;
		//		cout<<"		>"<<l_marked.accumulate<<endl;
				//----------------------
				map_distances.insert(make_pair(l_marked.index,l_marked));
				//----------------------
				set< edge<V,E> > ady;
						 ady = vertexs.find(l_marked.index)->second->get_edges_ady();
				typename set< edge<V,E> >::iterator it_ady;
				//-----------------------

				vertexs.erase(vertexs.find(l_marked.index));

		//			cout<<"		###"<<ady.size()<<"<<<<<<"<<endl;	
		//		for(it_ady=ady.begin();it_ady!=ady.end();it_ady++){
		//			cout<<" 	@@@>>"<<it_ady->m_pVertex->index;
		//		}
		//		ut<<endl;
				//-----------------------	
				for(it_ady=ady.begin();it_ady!=ady.end();it_ady++){
		//			cout<<"			_____________________"<<endl;
		//			cout<<"			for 1"<<endl;
					//----------------------------------------------
					if( vertexs.find(it_ady->m_pVertex->index)!=vertexs.end() )
					{
						vertex<V,E>* pNext = vertexs.find(it_ady->m_pVertex->index)->second;
						//----------------------------------------------
						int index_ady=it_ady->m_pVertex->index;
						E   ady_weight =it_ady->m_data_weight;	
						int marked_accumulate=l_marked.accumulate;
						int index_marked=l_marked.index;	
		//				cout<<"				"<<"__"<<endl;
		//				cout<<"				"<<index_ady<<endl;
		//				cout<<"				"<<index_marked<<endl;
		//				cout<<"				"<<ady_weight<<endl;
		//				cout<<"				"<<"__"<<endl;
		//				cout<<"				"<<marked_accumulate<<endl;

		//			cout<<"			for 2"<<endl;
		//				cout<<"				*****"<<labels[index_ady].accumulate<<endl;

						if( labels [index_ady].accumulate >
					 	    (marked_accumulate + ady_weight ) )
						{
							//---------------------------------------
		//			cout<<"			for 3"<<endl;
							label _new;
							      _new.index=index_ady;
							      _new.parent=index_marked;
							      _new.accumulate=marked_accumulate + ady_weight;
		//					cout<<"				>"<<_new.index<<endl;
		//					cout<<"				>"<<_new.parent<<endl;
		//					cout<<"				>"<<_new.accumulate<<endl;
							//---------------------------------------
							labels[index_ady]=_new;
						}

					}
				}
				ady.clear();
				
			}	
			
		//	cout<<"		saliendo a dijkstra"<<endl;
			return map_distances;
		}	
		
	
							
		void print_dijkstra(int _v_princ)
		{
			
			cout<<"entrando_imprimir_dijkstra"<<endl;
			cout<<"*****************************************"<<endl;
			cout<<"*****************************************"<<endl;
			typename set< vertex<V,E> >::iterator it_grafo=m_grafo.begin();;
			//---------------------------------------------
			map<int, label> short_path;
			short_path=dijkstra(_v_princ);
			//---------------------------------------------
			ofstream dot_file("camino_corto.dot");
			dot_file << "digraph D {\n"
			<< "  rankdir=LR\n"
			<< "  size=\"120,50\"\n"
			<< "  ratio=\"fill\"\n"
			<< "  edge[style=\"bold\"]\n" 
			<< "  node[shape=\"circle\"]\n";
			//---------------------------------------------
		
			int tam=short_path.size();	
			for(int i=0;i<tam;i++)cout<<" 	 "<<short_path.find(i)->first;	cout<<endl;
			for(int i=0;i<tam;i++) 	cout<<" 	 "<<short_path.find(i)->second.index;	cout<<endl;
			for(int i=0;i<tam;i++) 	cout<<" 	 "<<short_path.find(i)->second.parent;	cout<<endl;
			for(int i=0;i<tam;i++) 	cout<<" 	 "<<short_path.find(i)->second.accumulate;	cout<<endl;


			cout<<"			while"<<endl;

			
			while (!short_path.empty())
			{	
				
		cout<<"				1"<<endl;
				set< edge<V,E> > ady;
						ady = (*it_grafo).get_edges_ady();	
				typename set< edge<V,E> >::iterator it_ady=ady.begin();
				while( it_ady != ady.end() )
				{
	
		cout<<"				2"<<endl;
					dot_file << it_grafo->index << " -> "<< it_ady->m_pVertex->index 
						 << "[label=\"" << it_ady->m_data_weight << "\"";
	
					if (short_path.find(it_ady->m_pVertex->index)->second.parent==it_grafo->index)
						dot_file << ", color=\"red\"";
					else
						dot_file << ", color=\"grey\"";
						dot_file << "]\n";
			
					it_ady++;

		cout<<"				3"<<endl;
				}
				it_grafo++;
				short_path.erase(short_path.find(it_grafo->index));
			}
			dot_file << "}";
		
			cout<<"saliendo_imprimir_dijkstra"<<endl;
		}

//---------------------------------------------------------------------------
};


#endif //GRAFO_DINAMICO
