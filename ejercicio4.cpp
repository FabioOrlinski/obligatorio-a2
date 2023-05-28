#include <iostream>
#include <fstream>
#include ".\tads\grafo-lista-ady.cpp"

using namespace std;

int main()
{
  // ifstream myFile("Pruebas/Ejercicio4/10.in.txt");
  // cin.rdbuf(myFile.rdbuf());
  // ofstream myFile2("Pruebas/Ejercicio4/10.prueba.txt");
  // cout.rdbuf(myFile2.rdbuf());
  int V, E;
  cin >> V;
  GrafoListaAdy *g = new GrafoListaAdy(V);
  cin >> E;
  for (int i = 0; i < E; i++)
  {
    int v1, v2, p, esDoble, estaHabilitado;
    cin >> v1 >> v2 >> p >> esDoble >> estaHabilitado;
    if (estaHabilitado)
    {
      g->aniadirArista(v1, v2, p);
      if (esDoble == 2)
      {
        g->aniadirArista(v2, v1, p);
      }
    }
  }
  int cantidadCiudadesDeshabilitadas;
  cin >> cantidadCiudadesDeshabilitadas;
  for (int i = 0; i < cantidadCiudadesDeshabilitadas; i++)
  {
    int ciudadDeshabilitada;
    cin >> ciudadDeshabilitada;
    g->borrarVertice(ciudadDeshabilitada);
  }
  int cantidadAristasDeshabilitadas;
  cin >> cantidadAristasDeshabilitadas;
  for (int i = 0; i < cantidadAristasDeshabilitadas; i++)
  {
    int ciudad1, ciudad2;
    cin >> ciudad1 >> ciudad2;
    g->borrarArista(ciudad1, ciudad2);
  }
  int origen, destino;
  cin >> origen >> destino;
  dijkstra(g, origen, destino);
  delete g;
  return 0;
}
// g++ -g ejercicio4.cpp (para debbuger)
// g++ -o ejercicio4 ejercicio4.cpp
// ./ejercicio4.exe