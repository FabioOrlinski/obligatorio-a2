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
    nodoLista<Arista> **listaAdy;
    int V;
    int A;

    bool esDirigido;
    bool esPonderado;

    void imprimirCamino(int destino, int *ant)
    {
        nodoLista<int> *recorrido = new nodoLista<int>(destino);
        destino = ant[destino];
        while (destino != -1)
        {
            recorrido = new nodoLista<int>(destino, recorrido);
            destino = ant[destino];
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
    GrafoListaAdy(int cantidadDeVertices, bool esDirigido = true, bool esPonderado = true)
    {
        this->V = cantidadDeVertices;
        this->A = 0;
        this->esDirigido = esDirigido;
        this->esPonderado = esPonderado;

        this->listaAdy = new nodoLista<Arista> *[V + 1];
        for (int i = 1; i <= V; i++)
        {
            this->listaAdy[i] = NULL;
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
        bool *vis = new bool[V + 1];
        int *dist = new int[V + 1];
        int *ant = new int[V + 1];
        for (int i = 1; i <= V; i++)
        {
            vis[i] = false;
            dist[i] = INF;
            ant[i] = -1;
        }
        dist[origen] = 0;
        Heap<int> *heap = new Heap<int>(V);
        heap->encolar(0, origen);
        while (!heap->esVacia())
        {
            int v = heap->minimo();
            heap->desencolar();
            vis[v] = true;
            nodoLista<Arista> *arista = this->adyacentesA(v);
            while (arista != NULL)
            {
                int w = arista->dato.destino;
                int peso = arista->dato.peso;
                if (dist[w] > dist[v] + peso)
                {
                    dist[w] = dist[v] + peso;
                    ant[w] = v;
                    if (heap->existe(w))
                    {
                        heap->cambiarPrioridad(w, dist[w]);
                    }
                    else
                    {
                        heap->encolar(dist[w], w);
                    }
                }
                arista = arista->sig;
            }
        }
        cout << dist[destino] << endl;

        imprimirCamino(destino, ant);
        delete heap;
        delete vis;
        delete dist;
        delete ant;
    }
};