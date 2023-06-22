#include <iostream>
#include <fstream>
#include "lista.cpp"
#include "heap.cpp"
#define INF 99999
using namespace std;

class Arista
{
public:
    int costo;
    bool existe;
    Arista(int costo) : costo(costo), existe(true) {}
    Arista() : costo(0), existe(false) {}
};

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
                    this->matAdy[i][j] = new Arista();
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

    ~Grafo()
    {
        for (int i = 0; i < tope; i++)
        {
            for (int j = 0; j < tope; j++)
            {
                delete this->matAdy[i][j];
            }
            delete[] this->matAdy[i];
        }
        delete[] this->matAdy;
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
        int nivel = this->tope + 1;
        int cantidadNivelActual = 0;
        int cantidadSiguienteNivel = 0;
        Heap<int> *heap = new Heap<int>(tope);
        // Inicializar la cola de prioridad con los nodos de grado de entrada cero
        for (int i = 1; i < tope; i++)
        {
            if (cantIncidencias[i] == 0)
            {
                heap->encolar(i, i);
                cantidadNivelActual++;
            }
        }
        while (!heap->esVacia())
        {
            int v = heap->minimo(); // extrae el siguiente vertice sin incidencias
            heap->desencolar();
            cantidadNivelActual--;
            cantIncidencias[v] = -1;
            cout << v << endl;
            for (int w = 0; w < tope; w++)
            {
                if (matAdy[v][w]->existe && cantIncidencias[w] != -1)
                {
                    cantIncidencias[w]--;
                    if (cantIncidencias[w] == 0)
                    {
                        heap->encolar(w + nivel, w);
                        cantidadSiguienteNivel++;
                    }
                }
            }
            if (cantidadNivelActual == 0)
            {
                nivel += this->tope + 1;
                cantidadNivelActual = cantidadSiguienteNivel;
                cantidadSiguienteNivel = 0;
            }
        }
        delete heap;
    }
};
