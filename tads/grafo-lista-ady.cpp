#include <climits>
#include <string>
#include <iostream>
#include "heap.cpp"

using namespace std;

#define INF 999999999
struct Arista
{
    int origen;
    int destino;
    int peso; // puede que sea 1, en el caso de que no sea ponderado.
    Arista(int unOrigen, int unDestino, int unPeso = 1) : origen(unOrigen), destino(unDestino), peso(unPeso) {}
};

template <class T>
struct nodoLista
{
    T dato;
    nodoLista *sig;
    nodoLista(T &unDato) : dato(unDato), sig(0){};
    nodoLista(T &unDato, nodoLista *unSig) : dato(unDato), sig(unSig){};
};

class GrafoListaAdy
{
private:
    nodoLista<Arista> **listaAdy; // represetnacion del grafo con listas
    int V;                        // cantidad de vertices
    int A;                        // cantidad de arsitas

    bool esDirigido;  // indica si el grafo es dirigido
    bool esPonderado; // indica si el grafo es

    bool *initVisitados(int V)
    {
        bool *ret = new bool[V + 1]();
        for (int i = 1; i <= V; i++)
        {
            ret[i] = false;
        }
        return ret;
    }

    int *initCostos(int origen, int V)
    {
        int *ret = new int[V + 1]();
        for (int i = 1; i <= V; i++)
        {
            ret[i] = INF;
        }
        ret[origen] = 0;
        return ret;
    }

    int *initVengo(int V)
    {
        int *ret = new int[V + 1]();
        for (int i = 1; i <= V; i++)
        {
            ret[i] = -1;
        }
        return ret;
    }

    int verticeDesconocidoDeMenorCosto(bool *visitados, int *costos, int V)
    {
        int menor = -1;
        int costoMenorHastaElMomento = INF;
        for (int i = 1; i <= V; i++)
        {
            if (!visitados[i] && costos[i] < costoMenorHastaElMomento)
            {
                menor = i;
                costoMenorHastaElMomento = costos[i];
            }
        }
        return menor;
    }

    void imprimirCamino(int destino, int *vengo)
    {
        nodoLista<int> *recorrido = new nodoLista<int>(destino);
        destino = vengo[destino];
        while (destino != -1)
        {
            recorrido = new nodoLista<int>(destino, recorrido);
            destino = vengo[destino];
        }
        while (recorrido != NULL)
        {
            nodoLista<int> *temp = recorrido;
            cout << recorrido->dato << " ";
            recorrido = recorrido->sig;
            delete temp;
        }
    }

public:
    // Crea un grafo con V vertices (del 1 al V)
    // O(V)
    GrafoListaAdy(int cantidadDeVertices, bool esDirigido = true, bool esPonderado = true)
    {
        this->V = cantidadDeVertices;
        this->A = 0;
        this->esDirigido = esDirigido;
        this->esPonderado = esPonderado;

        this->listaAdy = new nodoLista<Arista> *[V + 1];
        for (int i = 1; i <= V; i++)
        {
            this->listaAdy[i] = NULL; // inicializa todas las listas como vacias
        }
    }

    ~GrafoListaAdy()
    {
        for (int i = 1; i <= V; i++)
        {
            nodoLista<Arista> *listaAuxiliar = listaAdy[i];
            while (listaAuxiliar != nullptr)
            {
                nodoLista<Arista> *nodoAEliminar = listaAuxiliar;
                listaAuxiliar = listaAuxiliar->sig;
                delete nodoAEliminar;
            }
        }
        delete[] listaAdy;
    }
    // O(1)
    void aniadirArista(int v, int w, int peso = 1)
    {
        int pesoArista = this->esPonderado ? peso : 1; // en el caso de ser ponderado se toma en cuenta el parametro
        Arista a1(v, w, pesoArista);
        listaAdy[v] = new nodoLista<Arista>(a1, listaAdy[v]); // se agrega al ppio de la lista de los adyacentes al veritce v
        this->A++;
        if (!esDirigido) // en caso de no ser dirigido podemos duplicar la arista hacia el otro sentido w->v
        {
            Arista a2(w, v, pesoArista);
            listaAdy[w] = new nodoLista<Arista>(a2, listaAdy[w]);
        }
    }

    // O(V)
    void borrarArista(int v, int w)
    {
        // busco la arista en la lista de adyacencia de v
        nodoLista<Arista> *listaAux = listaAdy[v];
        nodoLista<Arista> *listaAnterior = NULL;
        while (listaAux != NULL && listaAux->dato.destino != w)
        {
            listaAnterior = listaAux;
            listaAux = listaAux->sig;
        }
        // si la encontre la borro
        if (listaAux != NULL)
        {
            if (listaAnterior == NULL)
            {
                listaAdy[v] = listaAux->sig;
            }
            else
            {
                listaAnterior->sig = listaAux->sig;
            }
            delete listaAux;
            this->A--;
        }
        // si no la encontre no hago nada
    }

    // O(V + A)
    void borrarVertice(int VerticeABorrar)
    {
        // borro todas las aristas que llegan a V
        for (int i = 1; i <= this->V; i++)
        {
            borrarArista(i, VerticeABorrar);
            borrarArista(VerticeABorrar, i);
        }
    }

    // O(V) pc
    // si bien esta funcion podria ser O(1) si retornamos la lista original, es peligroso si la manipulan => corrompiendo el grafo
    nodoLista<Arista> *adyacentesA(int origen)
    {
        // copio la lista
        nodoLista<Arista> *listaRetorno = NULL;
        nodoLista<Arista> *listaAuxiliar = listaAdy[origen];

        while (listaAuxiliar != NULL)
        {
            Arista aristaAuxiliar = listaAuxiliar->dato;
            listaRetorno = new nodoLista<Arista>(aristaAuxiliar, listaRetorno);
            listaAuxiliar = listaAuxiliar->sig;
        }

        return listaRetorno;
    }

    void dijkstra(int origen, int destino)
    {
        bool *visitados = initVisitados(V);  // array V casilleros, todos en false
        int *costos = initCostos(origen, V); // array V casillero, todos en INF menos origen con 0
        int *vengo = initVengo(V);           // array V casilleros, todos en -1
        Heap<int> *heap = new Heap<int>(V);
        heap->encolar(0, origen);
        while (!heap->esVacia())
        {
            int v = heap->minimo(); // extrae el vértice de menor costo no visitado
            heap->desencolar();
            visitados[v] = true;
            nodoLista<Arista> *arista = this->adyacentesA(v);
            while (arista != NULL)
            {
                int w = arista->dato.destino;
                int peso = arista->dato.peso;
                // pregunto si mejoro el costo tentativo
                // cout << "entro if" << endl;
                if (costos[w] > costos[v] + peso)
                {
                    costos[w] = costos[v] + peso;
                    vengo[w] = v;
                    // cout << "existe entra: " << w << endl;
                    if (heap->existe(w))
                    {
                        // cout << "cambiarPrioridad entra" << endl;
                        heap->cambiarPrioridad(w, costos[w]);
                        // cout << "cambiarPrioridad sale" << endl;
                    }
                    else
                    {
                        // cout << "encolar entra" << endl;
                        heap->encolar(costos[w], w);
                        // cout << "encolar sale" << endl;
                    }
                }
                arista = arista->sig;
                // cout << "salgo if" << endl;
            }
        }
        delete heap;
        cout << costos[destino] << endl;
        imprimirCamino(destino, vengo);
    }
};