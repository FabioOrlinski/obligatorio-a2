#include <iostream>
#include <string>
#include <fstream>
#define INF 999999999
using namespace std;

bool esSolucion(int x1, int y1, int x2, int y2)
{
  return x1 == x2 && y1 == y2;
}

bool volvi(int x1, int y1, int x2, int y2)
{
  return x1 == x2 && y1 == y2;
}

void backTracking(string **plano, int x1, int y1, int x2, int y2, bool **visitados, int pasos, int &pasosOptimo, int x, int y)
{

  if (esSolucion(x1, y1, x2, y2))
  {
    if (pasos < pasosOptimo)
    {
      pasosOptimo = pasos;
    }
    return;
  }
  if (visitados[x1][y1] || plano[x1][y1] == "P")
  {
    return;
  }
  visitados[x1][y1] = true;
  pasos++;
  if (pasos >= pasosOptimo)
  {
    return;
  }
  if (x1 + 1 < x)
  {
    backTracking(plano, x1 + 1, y1, x2, y2, visitados, pasos, pasosOptimo, x, y);
  }
  if (y1 + 1 < y)
  {
    backTracking(plano, x1, y1 + 1, x2, y2, visitados, pasos, pasosOptimo, x, y);
  }
  if (x1 - 1 >= 0)
  {
    backTracking(plano, x1 - 1, y1, x2, y2, visitados, pasos, pasosOptimo, x, y);
  }
  if (y1 - 1 >= 0)
  {
    backTracking(plano, x1, y1 - 1, x2, y2, visitados, pasos, pasosOptimo, x, y);
  }
}

int main()
{
  ifstream myFile("Pruebas/Ejercicio10/facu10e1.in.txt");
  cin.rdbuf(myFile.rdbuf());
  ofstream myFile2("Pruebas/Ejercicio10/facu10e1.prueba.txt");
  cout.rdbuf(myFile2.rdbuf());
  cout << "hola";
  int x, y, xBedelia, yBedelia;
  cin >> x >> y;
  string **plano = new string *[x];
  for (int i = 0; i < x; i++)
  {
    plano[i] = new string[y];
    for (int j = 0; j < y; j++)
    {
      string valor;
      cin >> valor;
      plano[i][j] = valor;
      if (valor == "B")
      {
        xBedelia = i;
        yBedelia = j;
      }
    }
  }
  int P;
  cin >> P;
  for (int i = 0; i < P; i++)
  {
    int x1, y1, x2, y2;
    cin >> x1 >> y1 >> x2 >> y2;
    bool **visitadosParaBedelia = new bool *[x];
    bool **visitadosParaClase = new bool *[x];
    for (int i = 0; i < x; i++)
    {
      visitadosParaBedelia[i] = new bool[y];
      visitadosParaClase[i] = new bool[y];
      for (int j = 0; j < y; j++)
      {
        visitadosParaBedelia[i][j] = false;
        visitadosParaClase[i][j] = false;
      }
    }
    int pasosOptimoABedelia = INF;
    int pasosOptimosAClase = INF;
    backTracking(plano, x1 - 1, y1 - 1, xBedelia, yBedelia, visitadosParaBedelia, 0, pasosOptimoABedelia, x, y);
    if (pasosOptimoABedelia == INF)
    {
      cout << "0" << endl;
      continue;
    }
    backTracking(plano, xBedelia, yBedelia, x2 - 1, y2 - 1, visitadosParaClase, 0, pasosOptimosAClase, x, y);
    if (pasosOptimoABedelia == INF)
    {
      cout << "0" << endl;
      continue;
    }
    cout << pasosOptimoABedelia + pasosOptimosAClase << endl;
  }
  return 0;
}