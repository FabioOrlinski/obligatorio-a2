#include <climits>
#include <string>
#include <iostream>
using namespace std;

#define INF 999999999;

class Heap
{
private:
    int **elementos;
    int *pos;
    int largo;
    int ultimoLibre;

    // navegar hacia la izquierda
    int hijoIzq(int posNodo)
    {
        return posNodo * 2;
    }

    // navegar hacia la derecha
    int hijoDer(int posNodo)
    {
        return posNodo * 2 + 1;
    }

    // navego hacia mi padre
    int padre(int posNodo)
    {
        return posNodo / 2;
    }

    void intercambiar(int x, int y)
    {
        int eleAux = elementos[0][x];
        int prioridadAux = elementos[1][x];
        // intercambio los elementos
        elementos[0][x] = elementos[0][y];
        elementos[0][y] = eleAux;
        // intercambio las prioridades
        elementos[1][x] = elementos[1][y];
        elementos[1][y] = prioridadAux;

        int posAux = pos[x];
        pos[x] = pos[y];
        pos[y] = posAux;
    }

    void flotar(int posNodo)
    {
        // si no llegue a la raiz
        if (posNodo != 1)
        {
            int posNodoPadre = padre(posNodo);
            // en el caso de que no sea mi posicion: intercambio y sigo flotando
            if (elementos[1][posNodo] < elementos[1][posNodoPadre])
            {
                intercambiar(posNodo, posNodoPadre);
                flotar(posNodoPadre);
            }
        }
    }

    void hundir(int posNodo)
    {
        // si tiene hijos (al menos 1)
        if (hijoIzq(posNodo) < ultimoLibre)
        {
            int posIzq = hijoIzq(posNodo);
            int posDer = hijoDer(posNodo);
            int hijoMenor = posIzq;

            // si tengo hijo derecho && el hijo derecho es menor que el hijo izquierdo
            if (posDer < ultimoLibre && elementos[1][posDer] < elementos[1][posIzq])
            {
                hijoMenor = posDer;
            }

            if (elementos[1][hijoMenor] < elementos[1][posNodo])
            {
                intercambiar(hijoMenor, posNodo);
                hundir(hijoMenor);
            }
        }
    }

public:
    Heap(int tamanio)
    {
        elementos = new int *[2];
        elementos[0] = new int[tamanio + 1];
        elementos[1] = new int[tamanio + 1];
        pos = new int[tamanio + 1];
        for (int i = 0; i < tamanio + 1; i++)
        {
            pos[i] = -1;
        }
        largo = tamanio;
        ultimoLibre = 1;
    }

    void insertar(int nuevoElemento, int prioridad)
    {
        if (!estaLleno())
        {
            // inserto en la ultima posicion libre
            elementos[0][ultimoLibre] = nuevoElemento;
            elementos[1][ultimoLibre] = prioridad;
            pos[nuevoElemento] = ultimoLibre;
            // floto la ultima posicion libre
            flotar(ultimoLibre);
            ultimoLibre++;
        }
    }

    void cambiarPrioridad(int elemento, int nuevaPrioridad)
    {
        cout << "empieza cambiar prioridad con parametros: elemento: " << elemento << ", y nuevaPrioridad: " << nuevaPrioridad << endl;
        if (existe(elemento))
        {
            cout << "existe cambiar prioridad con parametros: elemento: " << elemento << ", y nuevaPrioridad: " << nuevaPrioridad << endl;
            int posDelElemento = pos[elemento];
            cout << "posDelElemento:  " << nuevaPrioridad << endl;
            elementos[1][posDelElemento] = nuevaPrioridad;
            flotar(posDelElemento);
            hundir(posDelElemento);
        }
        cout << "termina cambiar prioridad con parametros: elemento: " << elemento << ", y nuevaPrioridad: " << nuevaPrioridad << endl;
    }

    bool existe(int elemento)
    {
        return pos[elemento] != -1;
    }

    int obtenerMinimo()
    {
        if (!esVacio())
        {
            return elementos[0][1];
        }
        return -1;
    }

    void borrarMinimo()
    {
        if (!esVacio())
        {
            // pongo en la raiz el ultimo elemento
            pos[elementos[0][1]] = -1;
            elementos[0][1] = elementos[0][ultimoLibre - 1];
            elementos[1][1] = elementos[1][ultimoLibre - 1];
            ultimoLibre--;
            // hundo la raiz
            hundir(1);
        }
    }

    bool esVacio()
    {
        return ultimoLibre == 1;
    }

    bool estaLleno()
    {
        return ultimoLibre > largo;
    }
};

struct Arista
{
    int origen;
    int destino;
    int peso; // puede que sea 1, en el caso de que no sea ponderado.
    Arista(int unOrigen, int unDestino, int unPeso = 1) : origen(unOrigen), destino(unDestino), peso(unPeso) {}
};

struct nodoLista
{
    Arista dato;
    nodoLista *sig;
    nodoLista(Arista &unDato) : dato(unDato), sig(0){};
    nodoLista(Arista &unDato, nodoLista *unSig) : dato(unDato), sig(unSig){};
};

class GrafoListaAdy
{
private:
    nodoLista **listaAdy; // represetnacion del grafo con listas
    int V;                // cantidad de vertices
    int A;                // cantidad de arsitas

    bool esDirigido;  // indica si el grafo es dirigido
    bool esPonderado; // indica si el grafo es ponderado

public:
    // Crea un grafo con V vertices (del 1 al V)
    // O(V)
    GrafoListaAdy(int cantidadDeVertices, bool esDirigido = true, bool esPonderado = true)
    {
        this->V = cantidadDeVertices;
        this->A = 0;
        this->esDirigido = esDirigido;
        this->esPonderado = esPonderado;

        this->listaAdy = new nodoLista *[V + 1];
        for (int i = 1; i <= V; i++)
        {
            this->listaAdy[i] = NULL; // inicializa todas las listas como vacias
        }
    }
    // O(1)
    void aniadirArista(int v, int w, int peso = 1)
    {
        int pesoArista = this->esPonderado ? peso : 1; // en el caso de ser ponderado se toma en cuenta el parametro
        Arista a1(v, w, pesoArista);
        listaAdy[v] = new nodoLista(a1, listaAdy[v]); // se agrega al ppio de la lista de los adyacentes al veritce v
        this->A++;
        if (!esDirigido) // en caso de no ser dirigido podemos duplicar la arista hacia el otro sentido w->v
        {
            Arista a2(w, v, pesoArista);
            listaAdy[w] = new nodoLista(a2, listaAdy[w]);
        }
    }

    // O(V)
    void borrarArista(int v, int w)
    {
        // busco la arista en la lista de adyacencia de v
        nodoLista *listaAux = listaAdy[v];
        nodoLista *listaAnterior = NULL;
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
            // delete listaAux;
            this->A--;
        }
        // si no la encontre no hago nada
    }

    // O(V + A)
    void borrarVertice(int V)
    {
        // borro todas las aristas que salen de V
        nodoLista *listaAuxiliar = listaAdy[V];
        while (listaAuxiliar != NULL)
        {
            borrarArista(V, listaAuxiliar->dato.destino);
            listaAuxiliar = listaAuxiliar->sig;
        }
        // borro todas las aristas que llegan a V
        for (int i = 1; i <= this->V; i++)
        {
            borrarArista(i, V);
        }
    }

    // O(V) pc
    // si bien esta funcion podria ser O(1) si retornamos la lista original, es peligroso si la manipulan => corrompiendo el grafo
    nodoLista *adyacentesA(int origen)
    {
        // copio la lista
        nodoLista *listaRetorno = NULL;
        nodoLista *listaAuxiliar = listaAdy[origen];

        while (listaAuxiliar != NULL)
        {
            Arista aristaAuxiliar = listaAuxiliar->dato;
            listaRetorno = new nodoLista(aristaAuxiliar, listaRetorno);
            listaAuxiliar = listaAuxiliar->sig;
        }

        return listaRetorno;
    }
};

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
    // 5<-4<-1
    // [1,4,5]
    cout << "[";
    while (destino != -1)
    {
        cout << destino;
        if (vengo[destino] != -1)
        {
            cout << ", ";
        }
        destino = vengo[destino];
    }
    cout << "]";
}

void dijkstra(GrafoListaAdy *g, int origen, int V)
{
    bool *visitados = initVisitados(V);  // array V casilleros, todos en false
    int *costos = initCostos(origen, V); // array V casillero, todos en INF menos origen con 0
    int *vengo = initVengo(V);           // array V casilleros, todos en -1
    Heap *heap = new Heap(V);
    heap->insertar(origen, 0);
    cout << "insertar" << endl;
    int corrida = 0;
    while (!heap->esVacio())
    {
        corrida++;
        int v = heap->obtenerMinimo(); // extrae el vértice de menor costo no visitado
        heap->borrarMinimo();
        visitados[v] = true;
        nodoLista *arista = g->adyacentesA(v);
        int corridaWhile = 0;
        while (arista != NULL)
        {
            corridaWhile++;
            cout << "1: "
                 << "corrida: " << corrida << "corrida while: " << corridaWhile << endl;
            int w = arista->dato.destino;
            int peso = arista->dato.peso;
            // pregunto si mejoro el costo tentativo
            cout << "2: "
                 << "corrida: " << corrida << "corrida while: " << corridaWhile << endl;
            if (costos[w] > costos[v] + peso)
            {
                cout << "3: "
                     << "corrida: " << corrida << "corrida while: " << corridaWhile << endl;
                costos[w] = costos[v] + peso;
                vengo[w] = v;
                if (heap->existe(w))
                {
                    cout << "4: "
                         << "corrida: " << corrida << "corrida while: " << corridaWhile << endl;
                    heap->cambiarPrioridad(w, costos[w]);
                    cout << "5: "
                         << "corrida: " << corrida << "corrida while: " << corridaWhile << endl;
                }
                else
                {
                    cout << "6: "
                         << "corrida: " << corrida << "corrida while: " << corridaWhile << endl;
                    heap->insertar(w, costos[w]);
                    cout << "7: "
                         << "corrida: " << corrida << "corrida while: " << corridaWhile << endl;
                }
            }
            cout << "termina: "
                 << "corrida: " << corrida << endl;
            arista = arista->sig;
        }
    }
    cout << "xd";
    cout << costos[V] << endl;
    imprimirCamino(V, vengo);
}