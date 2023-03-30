#include <iostream>
using namespace std;

template<class T>
class nodoLista {
    public:
        T dato;
        nodoLista<T> * sig, * ant;

        nodoLista(T dato) : dato(dato), sig(NULL), ant(NULL){}
        nodoLista(T dato, nodoLista<T> *ant, nodoLista<T> *sig): dato(dato), sig(sig), ant(ant){}
};

template<class T>
class Lista {
    private:
        nodoLista<T> * ppio, * fin;
        int largo;

        bool perteneceRec(T dato, nodoLista<T>* nodo){
            return nodo && (dato == nodo->dato || perteneceRec(dato, nodo->sig));
        }

        void borrarRec(T dato, nodoLista<T> *& nodo){
            if(nodo){
                if(dato == nodo->dato){
                    nodoLista<T> * aBorrar = nodo;
                    nodo = nodo->sig;
                    if(nodo){
                        nodo->ant = aBorrar->ant;
                    } else {
                        this->fin = this->fin->ant;
                        if(!this->fin){
                            this->ppio=NULL;
                        }
                    }
                    delete aBorrar;
                    this->largo--;
                } else {
                    borrarRec(dato, nodo->sig);
                }
            }
        }

        void mostrarRec(nodoLista<T> *nodo){
            if(nodo){
                cout << nodo->dato << endl;
                mostrarRec(nodo->sig);
            }
        }

    public:
        int cantidadElementos(){
            return this->largo;
        }

        bool esVacia() {
            return this->largo==0;
        }

        bool pertenece(T dato) {
            return perteneceRec(dato, this->ppio);
        }

        void insertarPpio(T dato){
            this->ppio = new nodoLista<T>(dato, NULL, this->ppio);
            if(!this->fin){
                this->fin = this->ppio;
            }
            else
            {
                this->ppio->sig->ant = this->ppio;
            }
            this->largo++;
        }

        void insertarFin(T dato){
            this->fin = new nodoLista<T>(dato, this->fin, NULL);
            if(!this->ppio){
                this->ppio = this->fin;
            }
            else
            {
                this->fin->ant->sig = this->fin;
            }
            this->largo++;
        }

        T primero(){
            return this->ppio->dato;
        }

        void borrar(T dato){
            borrarRec(dato, this->ppio);
        }

        void mostrar(){
            mostrarRec(this->ppio);
        }
};

//int main(){
//    Lista<int>* lista = new Lista<int>();
//    lista->insertarFin(3);
//    lista->insertarFin(4);
//    lista->insertarFin(5);
//    lista->insertarPpio(2);
//    lista->insertarPpio(1);
//
//    lista->mostrar();
//}