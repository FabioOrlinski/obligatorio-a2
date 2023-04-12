#include <iostream>
#include <fstream>
#include ".\tads\heap.cpp"
//#include ".\tads\lista.cpp"
using namespace std;

int main()
{
    ifstream myFile("pruebas/pruebaej3.in.txt");
    cin.rdbuf(myFile.rdbuf());
    // Si desean tirar la salida a un archivo, usen las siguientes líneas (si no, sáquenlas):
    ofstream myFile2("pruebas/pruebaej3.out.txt");
    cout.rdbuf(myFile2.rdbuf());
    int reservas;
    int cantPer;

    cin >> reservas;
    Heap<string[]> *heap = new Heap<string[]>(reservas);
    string *lista;
    for (int i = 0; i < reservas; i++)
    {
        int total = 0;
        int cantVuelos;
        string pasaporte;
        cin >> cantPer;

        lista=new string[cantPer];
        for (int j = 0; j < cantPer; j++)
        {
            cin >> pasaporte;
            lista[j] = pasaporte;
            cin >> cantVuelos;
            total += cantVuelos;
        }
        heap->encolar((total / float(cantPer)), lista,cantPer);
    }

    for (int i = 0; i < reservas; i++)
    {
        heap->desencolar();
    }

    return 0;
}
