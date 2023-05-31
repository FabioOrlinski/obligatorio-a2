#include <iostream>
#include <fstream>
#include <cmath>
#include ".\tads\heap-ej3.cpp"

using namespace std;

int main()
{
    ifstream myFile("Pruebas/Ejercicio3/10000.in.txt");
    cin.rdbuf(myFile.rdbuf());
    ofstream myFile2("Pruebas/Ejercicio3/10000.prueba.txt");
    cout.rdbuf(myFile2.rdbuf());
    int reservas;
    int cantPer;

    cin >> reservas;
    Heap<string[]> *heap = new Heap<string[]>(reservas);
    string *lista;
    for (int i = 0; i < reservas; i++)
    {
        double total = 0;
        int cantVuelos;
        string pasaporte;
        cin >> cantPer;

        lista = new string[cantPer];
        for (int j = 0; j < cantPer; j++)
        {
            cin >> pasaporte;
            lista[j] = pasaporte;
            cin >> cantVuelos;
            total += cantVuelos;
        }
        double promedio = total / cantPer;
        heap->encolar(promedio, lista, cantPer);
    }

    for (int i = 0; i < reservas; i++)
    {
        heap->desencolar();
    }

    return 0;
}