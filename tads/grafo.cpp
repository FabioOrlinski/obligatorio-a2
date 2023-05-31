#include <iostream>
#include <fstream>
#include "lista.cpp"
#include "heap.cpp"
#define INF 99999
using namespace std;

class Arista
{
public:
    int costo, origen, destino;
    bool existe;
    Arista(int costo, int origen, int destino) : costo(costo), origen(origen), destino(destino), existe(true) {}
    Arista(int costo) : costo(costo), existe(true) {}
    Arista() : costo(0), existe(false) {}
};

int fComp(Arista *a, Arista *b)
{
    return a->costo - b->costo;
}

class Grafo
{
private:
    int cantVertices;
    int tope;
    bool esDirigido;
    Arista ***matAdy;

public:
    Grafo(int tope, bool esDirigido)
    {
        this->tope = tope;
        this->esDirigido = esDirigido;
        this->matAdy = new Arista **[tope];
        for (int i = 0; i < tope; i++)
        {
            this->matAdy[i] = new Arista *[tope];
        }

        if (esDirigido)
        {
            for (int i = 0; i < tope; i++)
            {
                for (int j = 0; j < tope; j++)
                {
                    this->matAdy[i][j] = new Arista();
                }
            }
        }
        else
        {
            for (int i = 0; i < tope; i++)
            {
                for (int j = i + 1; j < tope; j++)
                {
                    this->matAdy[i][j] = this->matAdy[j][i] = new Arista();
                }
                this->matAdy[i][i] = new Arista();
            }
        }
    }

    bool existeArista(int origen, int destino)
    {
        return this->matAdy[origen][destino]->existe;
    }

    // Pre: !existeArista(origen)
    void agregarArista(int origen, int destino, int costo = 1)
    {
        this->matAdy[origen][destino]->existe = true;
        this->matAdy[origen][destino]->costo = costo;
    }

    void *ordenTopologico(int *cantIncidencias)
    {
        int prioridad = 0;
        Heap<int> *heap = new Heap<int>(tope);
        // Inicializar la cola de prioridad con los nodos de grado de entrada cero
        for (int i = 1; i < tope; i++)
        {
            if (cantIncidencias[i] == 0)
            {
                heap->encolar(prioridad++, i);
            }
        }
        while (!heap->esVacia())
        {
            int v = heap->minimo(); // extrae el siguiente vertice sin incidencias
            heap->desencolar();
            cantIncidencias[v] = -1;
            cout << v << endl;
            for (int w = 0; w < tope; w++)
            {
                if (matAdy[v][w]->existe && cantIncidencias[w] != -1)
                {
                    cantIncidencias[w]--;
                    if (cantIncidencias[w] == 0)
                    {
                        heap->encolar(prioridad++, w);
                    }
                }
            }
        }
        delete heap;
    }
};

// 1 -> 4
// 2 -> 3
// 4
// 3
