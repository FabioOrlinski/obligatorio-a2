#include <iostream>
#include <fstream>

#include ".\tads\grafo.cpp"
#include ".\tads\lista.cpp"

using namespace std;

int main()
{
  // ifstream myFile("Pruebas/Ejercicio5/tops4.in.txt");
  // cin.rdbuf(myFile.rdbuf());
  // ofstream myFile2("Pruebas/Ejercicio5/tops4.prueba.txt");
  // cout.rdbuf(myFile2.rdbuf());
  int V, E;
  cin >> V;
  Grafo *g = new Grafo(V + 1, true);
  cin >> E;
  int *cantIncidencias = new int[V + 1];
  for (int i = 1; i < V + 1; cantIncidencias[i++] = 0)
    ;
  for (int i = 0; i < E; i++)
  {
    int origen, destino;
    cin >> origen >> destino;
    cantIncidencias[destino]++;
    g->agregarArista(origen, destino);
  }
  g->ordenTopologico(cantIncidencias);
  delete[] cantIncidencias;
  delete g;
  return 0;
}