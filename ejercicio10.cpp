#include <iostream>
#include <string>
#include <fstream>
#define INF 999999999
using namespace std;

int vX[4]{-1, 0, 1, 0};
int vY[4]{0, 1, 0, -1};

bool esSolucion(int x1, int y1, int x2, int y2)
{
  return x1 == x2 && y1 == y2;
}

bool esAceptable(bool **visitados, string **plano, int x1, int y1, int x, int y)
{
  // me fijo si ya lo visite, o si es pared, o si se sale del plano
  return x1 >= 0 && y1 >= 0 && x1 < x && y1 < y && !visitados[x1][y1] && plano[x1][y1] != "P";}

void backTracking(string **plano, int x1, int y1, int x2, int y2, bool **visitados, int pasos, int &pasosOptimo, int x, int y)
{
  // me fijo si es solucion
  if (esSolucion(x1, y1, x2, y2))
  {
    // me fijo si es mejor que la solucion anterior
    if (pasos < pasosOptimo)
    {
      // si es mejor, la guardo
      pasosOptimo = pasos;
    }
    return;
  }
  // me fijo si es aceptable
  if (!esAceptable(visitados, plano, x1, y1, x, y))
  {
    return;
  }
  // marco como visitado y avanzo
  visitados[x1][y1] = true;
  pasos++;
  // me fijo si mi solucion es peor que otra ya encontrada
  if (pasos >= pasosOptimo)
  {
    return;
  }
  // avanzo en todas las direcciones
  for (int k = 0; k < 4; k++)
  {
    backTracking(plano, x1 + vX[k], y1 + vY[k], x2, y2, visitados, pasos, pasosOptimo, x, y);
  }
  visitados[x1][y1] = false;
}

int main()
{
  ifstream myFile("Pruebas/Ejercicio10/facu10e1.in.txt");
  cin.rdbuf(myFile.rdbuf());
  ofstream myFile2("Pruebas/Ejercicio10/facu10e1.prueba.txt");
  cout.rdbuf(myFile2.rdbuf());
  int x, y, xBedelia, yBedelia;
  cin >> x >> y;
  string **plano = new string *[x];
  for (int i = 0; i < x; i++)
  {
    plano[i] = new string[y];
  }
  for (int j = 0; j < y; j++)
  {
    for (int i = 0; i < x; i++)
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
    if (pasosOptimosAClase == INF)
    {
      cout << "0" << endl;
      continue;
    }
    cout << pasosOptimoABedelia + pasosOptimosAClase + 1 << endl;
  }
  return 0;
}