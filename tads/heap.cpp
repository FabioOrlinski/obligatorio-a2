#include <iostream>
// #include ".\lista.cpp"
using namespace std;

class nodoHeap
{
public:
    float prioridad;
    int largo;
    string *pasajeros;

    nodoHeap(int prioridad, int largo, string *pasajeros) : prioridad(prioridad), largo(largo), pasajeros(pasajeros) {}
    ~nodoHeap(){
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
        int valorPadre = this->heap[posPadre]->prioridad;
        string* datoPadre = this->heap[posPadre]->pasajeros;
        int largoPadre = this->heap[posPadre]->largo;
        int valor = this->heap[pos]->prioridad;
        string* dato = this->heap[pos]->pasajeros;
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
        int prior = this->heap[pos]->prioridad;
        string* dato = this->heap[pos]->pasajeros;
        if (tengoIzq(pos))
        {
            int posMin = hijoIzq(pos);
            int prioIzq = this->heap[hijoIzq(pos)]->prioridad;
            if (tengoDer(pos) && this->heap[hijoDer(pos)]->prioridad < prioIzq)
            {
                posMin++;
            }
            if (this->heap[posMin]->prioridad >= prior)
            {
                this->heap[pos]->prioridad = this->heap[posMin]->prioridad;
                this->heap[pos]->pasajeros = this->heap[posMin]->pasajeros;
                this->heap[posMin]->prioridad = prior;
                this->heap[posMin]->pasajeros = dato;
                hundir(posMin);
            }
        }

        /*
            int posHijoIzq = hijoIzq(pos);
            int posHijoDer = hijoDer(pos);
            if (posHijoIzq >= this->tope && posHijoDer >= this->tope)
                return;
            int valor = this->heap[pos]->prioridad;
            T dato = this->heap[pos]->dato;
            int valorHijoIzq = this->heap[posHijoIzq]->prioridad;
            T datoHijoIzq = this->heap[posHijoIzq]->dato;
            int valorHijoDer = this->heap[posHijoDer]->prioridad;
            T datoHijoDer = this->heap[posHijoDer]->dato;

            if (posHijoDer >= this->tope && valor >= valorHijoIzq)
            {
                this->heap[posHijoIzq]->prioridad = valor;
                this->heap[posHijoIzq]->dato = dato;
                this->heap[pos]->prioridad = valorHijoIzq;
                this->heap[pos]->dato = datoHijoIzq;
                hundir(posHijoIzq);
                return;
            }
            if (valorHijoDer > valorHijoIzq && valor >= valorHijoIzq)
            {
                this->heap[posHijoIzq]->prioridad = valor;
                this->heap[posHijoIzq]->dato = dato;
                this->heap[pos]->prioridad = valorHijoIzq;
                this->heap[pos]->dato = datoHijoIzq;
                hundir(posHijoIzq);
                return;
            }
            if (valor >= valorHijoDer)
            {
                this->heap[posHijoDer]->prioridad = valor;
                this->heap[posHijoDer]->dato = dato;
                this->heap[pos]->prioridad = valorHijoDer;
                this->heap[pos]->dato = datoHijoDer;
                hundir(posHijoDer);
                return;}*/
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

    void encolar(float prioridad, string *pasajeros, int largo)
    {
        this->heap[tope] = new nodoHeap(prioridad, largo, pasajeros);
        this->flotar(this->tope++);
    }

    // Pre: !EsVacia()
    void desencolar()
    {
        cout << this->heap[0]->prioridad << " ";
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
    //T minimo()
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

// int main()
//{
//     Heap<int> monticulo(10);
//     monticulo.encolar(19, 0);
//     monticulo.encolar(21, 1);
//     monticulo.encolar(32, 2);
//     monticulo.encolar(24, 3);
//     monticulo.encolar(31, 4);
//     monticulo.encolar(38, 5);
//     monticulo.encolar(68, 6);
//     monticulo.encolar(65, 7);
//     monticulo.encolar(26, 8);
//     monticulo.mostrar();
//     monticulo.mostrar();
//     monticulo.desencolar();
//     return 0;
// }