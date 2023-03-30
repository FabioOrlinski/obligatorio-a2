#include <iostream>
#include ".\asociacion.cpp"

using namespace std;

// template <class T>
class HashCerrado
{
private:
    Asociacion **hash;
    int nota;
    int largo;
    int maxElementos;
    // int (*fHash)(T);

    bool esPrimo(int num)
    {
        if (num <= 1)
        {
            return false;
        }
        else
        {
            for (int i = 2; i <= num / 2; i++)
            {
                if (num % i == 0)
                {
                    return false;
                }
            }
            return true;
        }
    }

    int primoSup(int num)
    {
        while (!esPrimo(++num))
            ;
        return num;
    }

    int fHash(string dato)
    {

        unsigned long long hash = 0;
        int primoRandom = primoSup(this->maxElementos);
        for (int i = 0; i < dato.length(); i++)
        {
            hash = (int(dato[i]) + hash * primoRandom);
        }

        return hash % this->maxElementos;
    }

public:
    HashCerrado(int maxElementos) //, int (*fHash)(T))
    {
        this->maxElementos = primoSup(maxElementos);
        this->largo = 0;
        this->hash = new Asociacion *[this->maxElementos];
        for (int i = 0; i < this->maxElementos; i++)
        {
            this->hash[i] = NULL;
        }

        // this->fHash = fHash;
    }

    void imprimir(string nombre)
    {
        int pos = this->fHash(nombre);
        while (this->hash[pos]->clave!=nombre)
        {
            pos = (pos + 1) % this->maxElementos;
        }
        cout << nombre << " " << this->hash[pos]->valor<<endl;
    }

    void agregar(Asociacion *dato)
    {
        int pos = this->fHash(dato->clave);
        while (this->hash[pos])
        {
            pos = (pos + 1) % this->maxElementos;
        }
        this->hash[pos] = dato;
    }
};

// int main(){
//     HashCerrado<int>* hash = new HashCerrado<int>(10, fHash);
//
//
//     return 0;
// }