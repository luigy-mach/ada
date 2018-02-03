#ifndef GRAFO_H_
#define GRAFO_H_
#include <list>
#include <iostream>
#define INFINITO 9999999;
//-----------------------------------------------------------------------------------------------//
using namespace std;
//--------------------------------------  CLASE GRAFO  ------------------------------------------//
template <typename C> class Grafo
{
    public:
    //--------------------------------------  CLASE GRAFO  ------------------------------------------//
        class Arco
        {
            public:
                Arco();
                Arco(const Arco & otroArco);
                Arco(int adyacente, const C & costo);
                int devolverAdyacente() const;
                const C & devolverCosto() const;
                int vertice;
                C costo;
        };
    public:
        Grafo();
        Grafo(const Grafo & otroGrafo);
        ~Grafo();
        Grafo & operator = (const Grafo & otroGrafo);
        bool estaVacio() const;   // Devuelve true si la cantidad de vértices es cero
        int devolverLongitud() const;   // Indica la cantidad de vértices del grafo
        bool existeVertice(int vertice) const;
        bool existeArco(int origen, int destino) const;
        const C & costoArco(int origen, int destino) const;  // PRE CONDICION: existeArco(origen, destino)
        void devolverVertices(list<int> & vertices) const;
        void devolverAdyacentes(int origen, list<Arco> & adyacentes) const;
        void agregarVertice(int vertice);
        void eliminarVertice(int vertice);  // POST CONDICION: Para todo vértice v != vertice: !existeArco(v, vertice) && !existeArco(vertice, v)
        void agregarArco(int origen, int destino, const C & costo);  // PRE CONDICION: existeVertice(origen) && existeVertice(destino)  // POST CONDICION: existeArco(origen, destino)
        void eliminarArco(int origen, int destino);  // POST CONDICION: !existeArco(origen, destino)
        void vaciar();
    private:
        struct NGrafo{
            int vertice;
            list<Arco> adyacentes;
        };
        list<NGrafo> grafo;
};
//-----------------------------------------------------------------------------------------------//
//------------------------------- Implementacion clase ARCO -------------------------------------//
//-----------------------------------------------------------------------------------------------//
template <typename C> Grafo<C>::Arco::Arco()
{
}
//-----------------------------------------------------------------------------------------------//
template <typename C> Grafo<C>::Arco::Arco(const Arco & otroArco)
{
    this->costo = otroArco.devolverCosto();
    this->vertice = otroArco.devolverAdyacente();
}
//-----------------------------------------------------------------------------------------------//
template <typename C> Grafo<C>::Arco::Arco(int adyacente, const C & costo)
{
    vertice = adyacente;
    this->costo = costo;
}
//-----------------------------------------------------------------------------------------------//
template <typename C> int Grafo<C>::Arco::devolverAdyacente() const
{
    return this->vertice;
}
//-----------------------------------------------------------------------------------------------//
template <typename C> const C & Grafo<C>::Arco::devolverCosto() const
{
    return costo;
}
//-----------------------------------------------------------------------------------------------//
//------------------------------- Implementacion clase GRAFO ------------------------------------//
//-----------------------------------------------------------------------------------------------//

template <typename C> ostream & operator << (ostream & salida, const Grafo<C> & grafo)
{
	list<int> vertices;   //Recorremos todos los vertices
	grafo.devolverVertices(vertices);
	list<int>::iterator v;
	v = vertices.begin();
	cout << endl << "//------------------------------- GRAFO ------------------------------------//" << endl << endl;
	while (v != vertices.end()) 
	{
		salida << "Vertice: " << *v << endl;  // Recorremos todos los adyacentes de cada vertice
		list<typename Grafo<C>::Arco> adyacentes;
		grafo.devolverAdyacentes(*v, adyacentes);
		typename list<typename Grafo<C>::Arco>::iterator ady;
		ady = adyacentes.begin();
		while (ady != adyacentes.end()) 
		{
			salida << "            " << "-> " << ady->devolverAdyacente() << " con costo: (" << ady->costo << ")" << endl;
			ady++;
		}
		v++;
		cout << endl;
	}
	cout << "//-------------------------------------------------------------------------//" << endl << endl;
	return salida;
}
//-----------------------------------------------------------------------------------------------//
template <typename C> Grafo<C>::Grafo()
{
}
//-----------------------------------------------------------------------------------------------//
template <typename C> Grafo<C>::Grafo(const Grafo & otroGrafo)
{
    list<int> otroGrafo_vertices;
    list<Arco> otroGrafo_adyacentes;
    vaciar();
    typename list<int>::const_iterator vertices;
    otroGrafo.devolverVertices(otroGrafo_vertices);
    for(vertices = otroGrafo_vertices.begin(); vertices != otroGrafo_vertices.end(); vertices++)
        this->agregarVertice(*vertices);
    typename list<int>::const_iterator otroGrafo_iterador;
    typename list<Arco>::const_iterator otroGrafo_adyacentes_iterador;
    for(vertices = otroGrafo_vertices.begin(); vertices != otroGrafo_vertices.end(); vertices++, otroGrafo_adyacentes_iterador++)
    {
        otroGrafo.devolverAdyacentes(*vertices,otroGrafo_adyacentes);
        for(otroGrafo_adyacentes_iterador = otroGrafo_adyacentes.begin(); otroGrafo_adyacentes_iterador != otroGrafo_adyacentes.end(); otroGrafo_adyacentes_iterador++)
            agregarArco(*vertices, otroGrafo_adyacentes_iterador->devolverAdyacente(), otroGrafo_adyacentes_iterador->devolverCosto());
    }
}
//-----------------------------------------------------------------------------------------------//
template <typename C> Grafo<C>::~Grafo()
{
}
//-----------------------------------------------------------------------------------------------//
template <typename C> Grafo<C> & Grafo<C>::operator = (const Grafo & otroGrafo)
{
    list<int> otroGrafo_vertices;
    list<Arco> otroGrafo_adyacentes;
    vaciar();
    typename list<int>::const_iterator vertices;
    otroGrafo.devolverVertices(otroGrafo_vertices);
    for(vertices = otroGrafo_vertices.begin(); vertices != otroGrafo_vertices.end(); vertices++)
        this->agregarVertice(*vertices);
    typename list<int>::const_iterator otroGrafo_iterador;
    typename list<Arco>::const_iterator otroGrafo_adyacentes_iterador;
    for(vertices = otroGrafo_vertices.begin(); vertices != otroGrafo_vertices.end(); vertices++, otroGrafo_adyacentes_iterador++)
    {
        otroGrafo.devolverAdyacentes(*vertices,otroGrafo_adyacentes);
        for(otroGrafo_adyacentes_iterador = otroGrafo_adyacentes.begin(); otroGrafo_adyacentes_iterador != otroGrafo_adyacentes.end(); otroGrafo_adyacentes_iterador++)
            agregarArco(*vertices, otroGrafo_adyacentes_iterador->devolverAdyacente(), otroGrafo_adyacentes_iterador->devolverCosto());
    }
}
//-----------------------------------------------------------------------------------------------//
template <typename C> bool Grafo<C>::estaVacio() const
{
    return grafo.size();
}
//-----------------------------------------------------------------------------------------------//
template <typename C> int Grafo<C>::devolverLongitud() const
{
    return grafo.size();
}
//-----------------------------------------------------------------------------------------------//
template <typename C> bool Grafo<C>::existeVertice(int vertice) const
{
    typename list<NGrafo>::const_iterator it;
    it = grafo.begin();
    while ((it != grafo.end())&&(it->vertice != vertice))
        it++;
    if (it != grafo.end())
        return true;
    else 
        return false;
}
//-----------------------------------------------------------------------------------------------//
template <typename C> bool Grafo<C>::existeArco(int origen, int destino) const
{
    list<Arco> adyacentes;
    devolverAdyacentes(origen,adyacentes);
    if(adyacentes.size())
    {
        typename list<Arco>::const_iterator it;
        it = adyacentes.begin();
        while((it != adyacentes.end())&&(it->devolverAdyacente() != destino))
            it++;
        if (it != adyacentes.end())
            return true;
        else 
            return false;
    }
    else 
        return false;
}
//-----------------------------------------------------------------------------------------------//
template <typename C> const C & Grafo<C>::costoArco(int origen, int destino) const
{
    list<Arco> adyacentes;
    devolverAdyacentes(origen,adyacentes);
    if (adyacentes.size())
    {
        typename list<Arco>::const_iterator it;
        it = adyacentes.begin();
        while ((it != adyacentes.end())&&(it->devolverAdyacente() != destino))
            it++;
        if (it != adyacentes.end())
            return it->devolverCosto();
    }
    return INFINITO;
}
//-----------------------------------------------------------------------------------------------//
template <typename C> void Grafo<C>::devolverVertices(list<int> & vertices) const
{
    typename list<NGrafo>::const_iterator it;
    it = grafo.begin();
    while (it != grafo.end())
    {
        vertices.push_back(it->vertice);
        it++;
    }
}
//-----------------------------------------------------------------------------------------------//
template <typename C> void Grafo<C>::devolverAdyacentes(int origen, list<Arco> & adyacentes) const
{
    if(existeVertice(origen))
    {
        typename list<NGrafo>::const_iterator it;
        it = grafo.begin();
        while ((it != grafo.end())&&(it->vertice != origen))
            it++;
        adyacentes = it->adyacentes;
    }
}
//-----------------------------------------------------------------------------------------------//
template <typename C> void Grafo<C>::agregarVertice(int vertice)
{
    NGrafo Nuevo;
    Nuevo.vertice = vertice;
    this->grafo.push_back(Nuevo);
}
//-----------------------------------------------------------------------------------------------//
template <typename C> void Grafo<C>::eliminarVertice(int vertice)
{
    typename list<NGrafo>::iterator it;
    it = grafo.begin();
    while((it != grafo.end())&&(it->vertice != vertice))
        it++;
    if(it != grafo.end())
    {
        it->adyacentes.clear();
        grafo.erase(it);
    }
    else 
        cout << "El elemento que desea borrar no existe" << endl;
}
//-----------------------------------------------------------------------------------------------//
template <typename C> void Grafo<C>::agregarArco(int origen, int destino, const C & costo)
{
    // para hacer esta funcion, se verifica de que existan los vertices, si existen se busca la lista de adyacentes y se verifica de que no exista el arco.
    typename list<NGrafo>::iterator begin;
    typename list<NGrafo>::iterator origen_vertice;
    typename list<Arco>::const_iterator it_adyacentes;
    typename list<Arco>::const_iterator it_adyacentes_end;
    begin = grafo.begin();
    bool _origen = false;
    bool _destino = false;   // se comienza con los dos vertices no encontrados (false)
    while ((begin != grafo.end())&&((!_origen)||(!_destino)))
    {
        if ((begin->vertice == origen)&&(!_origen))
        {
            _origen = true;
            it_adyacentes = begin->adyacentes.begin();
            origen_vertice = begin;
            it_adyacentes_end = begin->adyacentes.end();
        }
        if ((begin->vertice == destino)&&(!_destino))
            _destino = true;
        begin++;
    }
    if ((_origen)&&(_destino))
    {   
        while ((it_adyacentes != it_adyacentes_end)&&(it_adyacentes->devolverAdyacente() != destino))
            it_adyacentes++;
        if (it_adyacentes == it_adyacentes_end)
        {
            Arco nuevo(destino,costo);
            origen_vertice->adyacentes.push_back(nuevo);
        }
    }
    else 
        cout << "No es posible agregar el arco, uno o mas vertices no existen" << endl;
}
//-----------------------------------------------------------------------------------------------//
template <typename C> void Grafo<C>::eliminarArco(int origen, int destino)
{
    typename list<NGrafo>::iterator begin;
    typename list<NGrafo>::iterator origen_vertice;
    typename list<Arco>::iterator it_adyacentes;
    typename list<Arco>::const_iterator it_adyacentes_end;
    begin = grafo.begin();
    bool _origen = false;
    bool _destino = false;    // se comienza con los dos vertices no encontrados (false)
    while ((begin != grafo.end())&&((!_origen)||(!_destino)))
    {
        if ((begin->vertice == origen)&&(!_origen))
        {
            _origen = true;
            it_adyacentes = begin->adyacentes.begin();
            origen_vertice = begin;
            it_adyacentes_end = begin->adyacentes.end();
        }
        if ((begin->vertice == destino)&&(!_destino))
            _destino = true;
        begin++;
    }
    if ((_origen)&&(_destino))
    {
        while ((it_adyacentes != it_adyacentes_end)&&(it_adyacentes->devolverAdyacente() != destino))
            it_adyacentes++;
        if (it_adyacentes != it_adyacentes_end)
            origen_vertice->adyacentes.erase(it_adyacentes);
        else 
            cout << "No es posible eliminar el arco, uno o mas vertices no existen" << endl;
    }
    else 
        cout << "No es posible eliminar el arco, uno o mas vertices no existen" << endl;
}
//-----------------------------------------------------------------------------------------------//
template <typename C> void Grafo<C>::vaciar()
{
    typename list<NGrafo>::iterator it;
    typename list<Arco>::iterator borrar;
    typename list<Arco>::iterator borrar_aux;
    it = grafo.begin();
    while(it!=grafo.end())
    {
        borrar = it->adyacentes.begin();
        while(borrar != it->adyacentes.end())
        {
            borrar_aux = borrar;
            borrar++;
            it->adyacentes.erase(borrar_aux);
        }
        it++;
    }
    grafo.clear();
}
//-----------------------------------------------------------------------------------------------//
#endif /* GRAFO_H_ */
