#include <iostream>
#include "Grafo.h"
#include "windows.h"
#define infinito 9999
#define no_visitado -1
//---------------------------------------------------------------------//
using namespace std;
//---------------------------------------------------------------------//
struct estructura_etiqueta{
            int padre;
            int costo;
       };
//---------------------------------------------------------------------//
void cargar_grafo(Grafo<int> &grafo1)
{
    grafo1.agregarVertice(1);
    grafo1.agregarVertice(2);
    grafo1.agregarVertice(3);
    grafo1.agregarVertice(4);
    grafo1.agregarVertice(5);
    grafo1.agregarVertice(6);
    grafo1.agregarVertice(7);
    grafo1.agregarArco(1,2,3);
    grafo1.agregarArco(2,1,3);
    grafo1.agregarArco(1,4,3);
    grafo1.agregarArco(4,1,3);
    grafo1.agregarArco(2,5,2);
    grafo1.agregarArco(5,2,2);
    grafo1.agregarArco(2,3,1);
    grafo1.agregarArco(3,2,1);
    grafo1.agregarArco(3,5,3);
    grafo1.agregarArco(5,3,3);
    grafo1.agregarArco(4,3,2);
    grafo1.agregarArco(3,4,2);
    grafo1.agregarArco(4,7,3);
    grafo1.agregarArco(7,4,3);
    grafo1.agregarArco(5,6,1);
    grafo1.agregarArco(6,5,1);
    grafo1.agregarArco(6,7,2);
    grafo1.agregarArco(7,6,2);
    cout << grafo1 << endl;
}
//---------------------------------------------------------------------//
bool existe_en_lista(int nodo, list<int> vertices_visitados)
{
    list<int>::const_iterator iterador;
    bool existe = false;
    for(iterador = vertices_visitados.begin(); iterador != vertices_visitados.end(); iterador++)
        if(*iterador == nodo)
            existe = true;
    return existe;
}
//---------------------------------------------------------------------//
int extraer_minimo(Grafo<int> grafo1, list<int> &vertices, list<int> &vertices_visitados, estructura_etiqueta etiqueta[])
{
    list<int>::const_iterator iterador;
    int costo, origen, destino;
    costo = infinito;
    for(iterador = vertices_visitados.begin(); iterador != vertices_visitados.end(); iterador++)
    {
        list<Grafo<int>::Arco> adyacentes;
        grafo1.devolverAdyacentes(*iterador, adyacentes);
        list<Grafo<int>::Arco>::const_iterator iterador_adyacente;
        for(iterador_adyacente = adyacentes.begin(); iterador_adyacente != adyacentes.end(); iterador_adyacente++)
            if(existe_en_lista(iterador_adyacente->devolverAdyacente(), vertices_visitados) == false)
                if(costo > grafo1.costoArco(*iterador, iterador_adyacente->devolverAdyacente()))
                {
                    costo = grafo1.costoArco(*iterador, iterador_adyacente->devolverAdyacente());
                    origen = *iterador;
                    destino = iterador_adyacente->devolverAdyacente();
                }  
    }
    etiqueta[destino].padre = origen;
    etiqueta[destino].costo = costo;
    return destino;
}
//---------------------------------------------------------------------//
void Prim(Grafo<int> grafo1, estructura_etiqueta etiqueta[], list<int> &vertices, list<int> &vertices_visitados)
{
    list<int>::const_iterator iterador;
    iterador = vertices.begin();
    etiqueta[*iterador].costo = 0;
    etiqueta[*iterador].padre = 0;
    vertices_visitados.push_front(*iterador);
    vertices.remove(*iterador);
    while(!vertices.empty())
    {
        int nodo = extraer_minimo(grafo1, vertices, vertices_visitados, etiqueta);
        vertices_visitados.push_back(nodo);
        vertices.remove(nodo);
    }
}
//---------------------------------------------------------------------//
int main()
{
    Grafo<int> grafo1;
    cargar_grafo(grafo1);
    list<int> vertices;
    grafo1.devolverVertices(vertices);
    list<int>::const_iterator iterador;
    estructura_etiqueta etiqueta[vertices.size()];
    for(iterador = vertices.begin(); iterador != vertices.end(); iterador++)
    {
        etiqueta[*iterador].padre = no_visitado;
        etiqueta[*iterador].costo = infinito;
    }
    list<int> vertices_visitados;
    Prim(grafo1, etiqueta, vertices, vertices_visitados);
    cout << "//-----------------PRIM-------------//" << endl << endl;
    list<int>::const_iterator iterador_visitados;
    for(iterador_visitados = vertices_visitados.begin(); iterador_visitados != vertices_visitados.end(); iterador_visitados++)
    {
        cout << "//------------------------------//" << endl;
        cout << "Nodo: " << *iterador_visitados << endl;
        cout << "Padre: " << etiqueta[*iterador_visitados].padre << endl;
        cout << "Costo: " << etiqueta[*iterador_visitados].costo << endl;
    }
    return 0;
}
//---------------------------------------------------------------------//