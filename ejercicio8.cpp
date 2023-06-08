#include <iostream>
#include <string>
#include <fstream>
#include "./tads/heap.cpp"

using namespace std;

class Vuelo
{
public:
  int llegada;
  int salida;
  Vuelo(int llegada, int salida) : salida(salida), llegada(llegada) {}
};

// me ingresa la cantidad de vuelos y los datos de cada vuelo
// quiero saber cuantas plataformas necesito como minimo para que no se superpongan
int main()
{
  // ifstream myFile("Pruebas/Ejercicio6/10.in.txt");
  // cin.rdbuf(myFile.rdbuf());
  // ofstream myFile2("Pruebas/Ejercicio6/10.prueba.txt");
  // cout.rdbuf(myFile2.rdbuf());
  int cantActual = 0;
  int cantPlataformas = 1;
  int cantidadVuelos;
  cin >> cantidadVuelos;
  Heap<Vuelo *> *vuelosPorLlegada = new Heap<Vuelo *>(cantidadVuelos);
  Heap<Vuelo *> *vuelosPorSalida = new Heap<Vuelo *>(cantidadVuelos);
  for (int i = 0; i < cantidadVuelos; i++)
  {
    int salida, llegada;
    cin >> llegada >> salida;
    Vuelo *vuelo = new Vuelo(llegada, salida);
    vuelosPorLlegada->encolar(llegada, vuelo);
    vuelosPorSalida->encolar(salida, vuelo);
  }
  while (!vuelosPorLlegada->esVacia())
  {
    Vuelo *proximoLlegada = vuelosPorLlegada->minimo();
    vuelosPorLlegada->desencolar();
    cantActual++;
    while (!vuelosPorSalida->esVacia() && vuelosPorSalida->minimo()->salida <= proximoLlegada->llegada)
    {
      vuelosPorSalida->desencolar();
      cantActual--;
    }
    if (cantActual > cantPlataformas)
    {
      cantPlataformas = cantActual;
    }
  }
  cout << cantPlataformas << endl;
  delete vuelosPorLlegada;
  delete vuelosPorSalida;
  return 0;
}
