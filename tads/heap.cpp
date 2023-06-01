#include <iostream>
#include <fstream>

using namespace std;

template <class T>
class nodoHeap
{
public:
  int prioridad;
  T dato;

  nodoHeap(int prioridad, T dato) : prioridad(prioridad), dato(dato) {}
};

template <class T>
class Heap
{
private:
  nodoHeap<T> **heap;
  int tope;
  int maxElementos;

  bool tengoIzq(int pos)
  {
    return this->tope > pos * 2 + 1;
  }

  bool tengoDer(int pos)
  {
    return this->tope > pos * 2 + 2;
  }

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
    float valorPadre = this->heap[posPadre]->prioridad;
    T datoPadre = this->heap[posPadre]->dato;
    float valor = this->heap[pos]->prioridad;
    T dato = this->heap[pos]->dato;
    if (valor < valorPadre)
    {
      this->heap[posPadre]->prioridad = valor;
      this->heap[posPadre]->dato = dato;
      this->heap[pos]->prioridad = valorPadre;
      this->heap[pos]->dato = datoPadre;
      flotar(posPadre);
    }
  }

  void hundir(int pos)
  {
    float prior = this->heap[pos]->prioridad;
    T dato = this->heap[pos]->dato;
    if (tengoIzq(pos))
    {
      int posMin = hijoIzq(pos);
      int prioIzq = this->heap[hijoIzq(pos)]->prioridad;
      if (tengoDer(pos) && this->heap[hijoDer(pos)]->prioridad < prioIzq)
      {
        posMin++;
      }
      if (this->heap[posMin]->prioridad <= prior)
      {
        this->heap[pos]->prioridad = this->heap[posMin]->prioridad;
        this->heap[pos]->dato = this->heap[posMin]->dato;
        this->heap[posMin]->prioridad = prior;
        this->heap[posMin]->dato = dato;
        hundir(posMin);
      }
    }
  }

public:
  Heap(int maxElementos)
  {
    this->maxElementos = maxElementos;
    this->tope = 0;
    this->heap = new nodoHeap<T> *[this->maxElementos];
  }
  ~Heap()
  {
    for (int i = 0; i < tope; delete this->heap[i++])
      ;
    delete[] this->heap;
  }

  void encolar(int prioridad, T dato)
  {
    this->heap[tope] = new nodoHeap<T>(prioridad, dato);
    this->flotar(this->tope++);
  }

  // Pre: !EsVacia()
  void desencolar()
  {
    delete this->heap[0];
    this->heap[0] = this->heap[--this->tope];
    hundir(0);
  }

  // Pre: !EsVacia()
  T minimo()
  {
    return this->heap[0]->dato;
  }

  bool esVacia()
  {
    return this->tope == 0;
  }

  int largo()
  {
    return this->tope;
  }

  bool existe(T elemento)
  {
    for (int i = 0; i < tope; i++)
    {
      if (this->heap[i]->dato == elemento)
      {
        return true;
      }
    }
    return false;
  }

  void cambiarPrioridad(T elemento, int nuevaPrioridad)
  {
    for (int i = 0; i < tope; i++)
    {
      if (this->heap[i]->dato == elemento)
      {
        this->heap[i]->prioridad = nuevaPrioridad;
        if (nuevaPrioridad < this->heap[padre(i)]->prioridad)
        {
          flotar(i);
        }
        else
        {
          hundir(i);
        }
        break;
      }
    }
  }
};