#ifndef GRAFO_H_
#define GRAFO_H_
#include <list>
#include <iostream>
#define INFINITO 9999
//-----------------------------------------------------------------------------------------------
using namespace std;
//--------------------------------------  CLASE GRAFO  ------------------------------------------
template <typename C> class Grafo
{
    public:
	class Arco;

        struct NGrafo{
            NGrafo(int v):vertice(v){}
            int vertice;
            list<Arco> adyacentes;
        };
        list<NGrafo> grafo;


    public:

    //--------------------------------------  CLASE GRAFO  ------------------------------------------
        class Arco
        {
            public:
                Arco(){};
                Arco(const Arco & otroArco);
                Arco(int adyacente, const C & costo)
                {   vertice = adyacente;
                    this->costo = costo;
                }
                ~Arco(){};
                int devolverAdyacente() const{return this->vertice;}
                const C & devolverCosto() const{return costo;}
            //----------
                int vertice;
                C costo;
        };
    public:
        Grafo(){};
        Grafo(const Grafo & otroGrafo);
        //Grafo & operator = (const Grafo & otroGrafo);//agregar luego
        ~Grafo(){}

        void agregarVertice(int vertice){grafo.push_back(NGrafo(vertice));}
        bool estaVacio() const{return grafo.size();}   
        int devolverLongitud() const{return grafo.size();}  

        bool existeVertice(int vertice) const;
        bool existeArco(int origen, int destino) const;
        const C & costoArco(int origen, int destino) const; 
        void devolverVertices(list<int> & vertices) const;
        void devolverAdyacentes(int origen, list<Arco> & adyacentes) const;
        void agregarArco(int origen, int destino, const C & costo);   

   
};
//-----------------------------------------------------------------------------------------------
//------------------------------- Implementacion clase ARCO -------------------------------------
template <typename C>
Grafo<C>::Arco::Arco(const Arco & otroArco)
{
    this->costo = otroArco.devolverCosto();
    this->vertice = otroArco.devolverAdyacente();
}

//-----------------------------------------------------------------------------------------------
//------------------------------- Implementacion clase GRAFO ------------------------------------
//-----------------------------------------------------------------------------------------------

template <typename C>
ostream & operator << (ostream & salida, const Grafo<C> & grafo)
{
	list<int> vertices;   
	grafo.devolverVertices(vertices);
	list<int>::iterator v =vertices.begin();

	cout << endl << "//------------------------------- GRAFO ------------------------------------" << endl << endl;
	while (v != vertices.end())
	{
		salida << "Vertice: " << *v << endl;  
		list<typename Grafo<C>::Arco> adyacentes;
		typename list<typename Grafo<C>::Arco>::iterator ady;
		grafo.devolverAdyacentes(*v, adyacentes);
		ady = adyacentes.begin();
		while (ady != adyacentes.end())
		{
			salida << "            " << "-> " << ady->devolverAdyacente() << " con costo: (" << ady->costo << ")" << endl;
			ady++;
		}
		v++;
		cout << endl;
	}
	cout << "//-------------------------------------------------------------------------" << endl << endl;
	return salida;
}

//-----------------------------------------------------------------------------------------------
template <typename C>
Grafo<C>::Grafo(const Grafo & otroGrafo)
{
    list<int> otroGrafo_vertices;
    list<Arco> otroGrafo_adyacentes;
//    vaciar();
    typename list<int>::const_iterator vertices;
    otroGrafo.devolverVertices(otroGrafo_vertices);
    for(vertices = otroGrafo_vertices.begin(); vertices != otroGrafo_vertices.end(); vertices++)
        this->agregarVertice(*vertices);
    typename list<Arco>::const_iterator otroGrafo_adyacentes_iterador;
    for(vertices = otroGrafo_vertices.begin(); vertices != otroGrafo_vertices.end(); vertices++, otroGrafo_adyacentes_iterador++)
    {
        otroGrafo.devolverAdyacentes(*vertices,otroGrafo_adyacentes);
        for(otroGrafo_adyacentes_iterador = otroGrafo_adyacentes.begin(); otroGrafo_adyacentes_iterador != otroGrafo_adyacentes.end(); otroGrafo_adyacentes_iterador++)
            agregarArco(*vertices, otroGrafo_adyacentes_iterador->devolverAdyacente(), otroGrafo_adyacentes_iterador->devolverCosto());
    }
}

//-----------------------------------------------------------------------------------------------
template <typename C>
bool Grafo<C>::existeVertice(int vertice) const
{
    typename list<NGrafo>::const_iterator it=grafo.begin();
    while ( (it!=grafo.end()) && (it->vertice != vertice) )
        it++;
    if ( it != grafo.end() )
        return true;
    else
        return false;
}
//-----------------------------------------------------------------------------------------------
template <typename C>
bool Grafo<C>::existeArco(int origen, int destino) const
{
    list<Arco> adyacentes;
    devolverAdyacentes(origen,adyacentes);
    if(adyacentes.size())
    {
        typename list<Arco>::const_iterator it=adyacentes.begin();
        while( (it!=adyacentes.end()) && (it->devolverAdyacente()!=destino) )
            it++;
        if (it != adyacentes.end())
            return true;
        else
            return false;
    }
    else
        return false;
}
//-----------------------------------------------------------------------------------------------
template <typename C>
const C & Grafo<C>::costoArco(int origen, int destino) const
{
    list<Arco> adyacentes;
    devolverAdyacentes(origen,adyacentes);
    if (adyacentes.size())
    {
        typename list<Arco>::const_iterator it=adyacentes.begin();
        while ((it != adyacentes.end())&&(it->devolverAdyacente() != destino))
            it++;
        if (it != adyacentes.end())
            return it->devolverCosto();
    }
    return INFINITO;
}
//-----------------------------------------------------------------------------------------------
template <typename C>
void Grafo<C>::devolverVertices(list<int> & vertices) const
{
    typename list<NGrafo>::const_iterator it=grafo.begin();
    while (it != grafo.end())
    {
        vertices.push_back(it->vertice);
        it++;
    }
}
//-----------------------------------------------------------------------------------------------
template <typename C>
void Grafo<C>::devolverAdyacentes(int origen, list<Arco> & adyacentes) const
{
    if(existeVertice(origen))
    {
        typename list<NGrafo>::const_iterator it=grafo.begin();
        while( (it!=grafo.end()) && (it->vertice!=origen) )
            it++;
        adyacentes = it->adyacentes;
    }
}

//-----------------------------------------------------------------------------------------------
template <typename C>
void Grafo<C>::agregarArco(int origen, int destino, const C & costo)
{
    
    typename list<NGrafo>::iterator begin=grafo.begin();

    typename list<NGrafo>::iterator origen_vertice;
    typename list<Arco>::const_iterator it_adyacentes;
    typename list<Arco>::const_iterator it_adyacentes_end;

    bool _origen = false;
    bool _destino = false;
    while ( (begin!=grafo.end()) && ((!_origen)||(!_destino)) )
    {
        if ( (begin->vertice==origen) && (!_origen) )
        {
            _origen = true;
            it_adyacentes = begin->adyacentes.begin();
            origen_vertice = begin;
            it_adyacentes_end = begin->adyacentes.end();
        }

        if ( (begin->vertice==destino) && (!_destino) )
            _destino = true;

        if(_destino&&_origen)
            break;
        begin++;
    }
    if (_origen&&_destino)
    {
        while ( (it_adyacentes!=it_adyacentes_end) && (it_adyacentes->devolverAdyacente()!=destino))
            it_adyacentes++;

        if (it_adyacentes==it_adyacentes_end)
            origen_vertice->adyacentes.push_back(Arco(destino,costo));
    }
    else
        cout << "No es posible agregar el arco, uno o mas vertices no existen" << endl;
}


#endif /* GRAFO_H_ */


