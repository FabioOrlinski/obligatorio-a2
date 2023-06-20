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

void mochilaDP(Elemento **elementos, int cantArchivos, int maximoTamano, int maximoLineasCodigo)
{
  int ***matDP = new int **[cantArchivos];
  // lleno una arista de la matriz con 0s
  for (int i = 0; i < cantArchivos; i++) {
      matDP[i] = new int*[maximoTamano+1];
        for (int j = 0; j < maximoTamano; j++){
        matDP[i][j] = new int [maximoLineasCodigo+1];
        matDP[i][j][0] = 0;
        }
  }
  for (int j = 1; j <= maximoTamano; j++) {
    for (int k = 1; k <= maximoLineasCodigo; k++) {
      matDP[0][j][k] = ((j / elementos[0]->tamano) && (k/ elementos[0]->lineasCodigo)) ? elementos[0]->puntaje : 0;
    }
  }

  for (int i = 1; i < cantArchivos; i++) {
    for (int j = 1; j <= maximoTamano; j++) {
        for (int k = 1; k <= maximoLineasCodigo; k++) {
          matDP[i][j][k] = ((j < elementos[i]->tamano) && (k < elementos[i]->lineasCodigo)) ? matDP[i-1][j-1][k] :
              max(matDP[i-1][j-1][k], elementos[i]->puntaje + matDP[i][j-elementos[i]->tamano][k-elementos[i]->lineasCodigo]);
        }
    }
  }
  cout << matDP[cantArchivos -1][maximoTamano -1][maximoLineasCodigo - 1] << endl;
}

int main()
{
  ifstream myFile("Pruebas/Ejercicio7/10.in.txt");
  cin.rdbuf(myFile.rdbuf());
  ofstream myFile2("Pruebas/Ejercicio7/10.prueba.txt");
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
