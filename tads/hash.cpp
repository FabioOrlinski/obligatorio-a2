#include <iostream>
using namespace std;

template<class T>
class HashCerrado {
    private:
        T** hash;
        int largo;
        int maxElementos;
        int (*fHash)(T);

        bool esPrimo(int num){
            if(num<=1)
            {
                return false;
            } else {
                for (int i = 2; i <= num/2; i++)
                {
                    if(num%i==0)
                    {
                        return false;
                    }
                }
                return true;
            }
        }

        int primoSup(int num){
            while(!esPrimo(++num));
            return num;
        }

    public:
        HashCerrado(int maxElementos, int (*fHash)(T)){
            this->maxElementos = primoSup(maxElementos);
            this->largo = 0;
            this->hash = new T*[this->maxElementos];
            for (int i = 0; i < this->maxElementos; i++)
            {
                this->hash[i]=NULL;
            }
            
            this->fHash=fHash;
        }

        void agregar(T dato){
            int pos = this->fHash(dato) % this->maxElementos;
            while(this->hash[pos]){
                pos=(pos+1)%this->maxElementos;
            }
            this->hash[pos] = &dato;
        }

};