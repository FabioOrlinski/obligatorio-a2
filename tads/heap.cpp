#include <iostream>
#include <string>
#include <iomanip>
// #include ".\lista.cpp"
using namespace std;

class nodoHeap
{
public:
    double prioridad;
    int largo;
    string *pasajeros;

    nodoHeap(double prioridad, int largo, string *pasajeros) : prioridad(prioridad), largo(largo), pasajeros(pasajeros) {}
    ~nodoHeap()
    {
        delete[] pasajeros;
    }
};

template <class T>
class Heap
{
private:
    nodoHeap **heap;
    int tope;
    int maxElementos;

    int padre(int pos)
    {
        return (pos - 1) / 2;
    }
    int hijoIzq(int pos)
    {
        return pos * 2 + 1;
    }
    int hijoDer(int pos)
    {
        return pos * 2 + 2;
    }

    void flotar(int pos)
    {
        int posPadre = padre(pos);
        if (posPadre == pos)
        {
            return;
        }
        double valorPadre = this->heap[posPadre]->prioridad;
        string *datoPadre = this->heap[posPadre]->pasajeros;
        int largoPadre = this->heap[posPadre]->largo;
        double valor = this->heap[pos]->prioridad;
        string *dato = this->heap[pos]->pasajeros;
        int largo = this->heap[pos]->largo;
        if (valor > valorPadre)
        {
            this->heap[posPadre]->prioridad = valor;
            this->heap[posPadre]->pasajeros = dato;
            this->heap[posPadre]->largo = largo;
            this->heap[pos]->prioridad = valorPadre;
            this->heap[pos]->pasajeros = datoPadre;
            this->heap[pos]->largo = largoPadre;
            flotar(posPadre);
        }
    }

    bool tengoIzq(int pos)
    {
        return this->tope > pos * 2 + 1;
    }

    bool tengoDer(int pos)
    {
        return this->tope > pos * 2 + 2;
    }

    void hundir(int pos)
    {
        double prior = this->heap[pos]->prioridad;
        string *dato = this->heap[pos]->pasajeros;
        int largo = this->heap[pos]->largo;
        if (tengoIzq(pos))
        {
            int posMin = hijoIzq(pos);
            double prioIzq = this->heap[hijoIzq(pos)]->prioridad;
            if (tengoDer(pos) && this->heap[hijoDer(pos)]->prioridad > prioIzq)
            {
                posMin++;
            }
            if (this->heap[posMin]->prioridad > prior)
            {
                this->heap[pos]->prioridad = this->heap[posMin]->prioridad;
                this->heap[pos]->largo = this->heap[posMin]->largo;
                this->heap[pos]->pasajeros = this->heap[posMin]->pasajeros;
                this->heap[posMin]->prioridad = prior;
                this->heap[posMin]->pasajeros = dato;
                this->heap[posMin]->largo = largo;
                hundir(posMin);
            }
        }
    }

public:
    Heap(int maxElementos)
    {
        this->maxElementos = maxElementos;
        this->tope = 0;
        this->heap = new nodoHeap *[this->maxElementos];
    }
    ~Heap()
    {
        for (int i = 0; i < tope; delete this->heap[i++])
            ;
        delete[] this->heap;
    }

    void encolar(double prioridad, string *pasajeros, int largo)
    {
        this->heap[tope] = new nodoHeap(prioridad, largo, pasajeros);
        this->flotar(this->tope++);
    }

    // Pre: !EsVacia()
    void desencolar()
    {
        if (this->heap[0]->prioridad != (int)this->heap[0]->prioridad)
        {

            cout << fixed << setprecision(2) << this->heap[0]->prioridad << " ";
            cout << fixed << setprecision(0);
        }
        else
        {

            cout << this->heap[0]->prioridad << " ";
        }
        int largo = this->heap[0]->largo;
        for (int i = 0; i < largo; i++)
        {
            cout << this->heap[0]->pasajeros[i] << " ";
        }
        cout << endl;
        delete this->heap[0];
        this->heap[0] = this->heap[--this->tope];
        hundir(0);
    }

    // Pre: !EsVacia()
    // T minimo()
    //{
    //    return this->heap[0];
    //}

    bool esVacia()
    {
        return this->tope == 0;
    }

    int largo()
    {
        return this->tope;
    }

    void mostrar()
    {
        for (int i = 0; i < tope; i++)
        {
            cout << this->heap[i]->prioridad << endl;
        }
    }
};