#include <iostream>
#include <string>
#include <fstream>

using namespace std;

class Elemento
{
public:
  int tamano;
  int lineasCodigo;
  int puntaje;

  Elemento(int tamano, int lineasCodigo, int puntaje) : tamano(tamano), lineasCodigo(lineasCodigo), puntaje(puntaje) {}
};

int max(int a, int b)
{
    return a > b ? a : b;
}

void mochilaDP(Elemento **elementos, int cantArchivos, int maximoTamano, int maximoLineasCodigo)
{
  int ***matDP = new int **[cantArchivos];
  // lleno una arista de la matriz con 0s
  for (int i = 0; i < cantArchivos; i++) {
      matDP[i] = new int*[maximoTamano+1];
        for (int j = 0; j < maximoTamano+1; j++){
        matDP[i][j] = new int [maximoLineasCodigo+1];
        matDP[i][j][0] = 0;
        }
  }

  for (int j = 1; j <= maximoTamano; j++) {
    for (int k = 1; k <= maximoLineasCodigo; k++) {
      bool condicionTamano= j/ elementos[0]->tamano >=1;
      bool condicionLineas= k/ elementos[0]->lineasCodigo >=1;
      matDP[0][j][k] = (condicionTamano && condicionLineas) ? elementos[0]->puntaje : 0;
    }
  }

  for (int i = 1; i < cantArchivos; i++) {
    for (int j = 1; j <= maximoTamano; j++) {
        for (int k = 1; k <= maximoLineasCodigo; k++) {
          bool condicionTamano= j < elementos[i]->tamano;
          bool condicionLineas= k < elementos[i]->lineasCodigo;
          int valorAnt = matDP[i-1][j-1][k];
          matDP[i][j][k] = (condicionTamano || condicionLineas) ? valorAnt :
              max(valorAnt, elementos[i]->puntaje + matDP[i][j-elementos[i]->tamano][k-elementos[i]->lineasCodigo]);
        }
    }
  }
  cout << matDP[cantArchivos -1][maximoTamano -1][maximoLineasCodigo - 1] << endl;
  for (int i = 0; i < cantArchivos; i++) {
    for (int j = 0; j <= maximoTamano; j++) {
      delete[] matDP[i][j];
    }
    delete[] matDP[i];
  }
  delete[] matDP;
}

int main()
{
  ifstream myFile("Pruebas/Ejercicio7/100.in.txt");
  cin.rdbuf(myFile.rdbuf());
  ofstream myFile2("Pruebas/Ejercicio7/100.prueba.txt");
  cout.rdbuf(myFile2.rdbuf());
  int cantArchivos, maximoTamano, maximoLineasCodigo;
  cin >> cantArchivos >> maximoTamano >> maximoLineasCodigo;
  Elemento **elementos = new Elemento *[cantArchivos];
  for (int i = 0; i < cantArchivos; i++)
  {
    int tamano, lineasCodigo, puntaje;
    cin >> tamano >> lineasCodigo >> puntaje;
    elementos[i] = new Elemento(tamano, lineasCodigo, puntaje);
  }
  mochilaDP(elementos, cantArchivos, maximoTamano, maximoLineasCodigo);
  for (int i = 0; i < cantArchivos; delete elementos[i++])
    ;
  delete[] elementos;
  return 0;
}
