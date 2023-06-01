#include <iostream>
#include <string>
#include <fstream>

using namespace std;

void sinPareja(int *elementos, int comienzo, int fin)
{
  if (comienzo == fin)
  {
    cout << elementos[comienzo] << endl;
    return;
  }
  int medio = (fin - comienzo) / 2 + comienzo;
  if (elementos[medio] == elementos[medio + 1])
  {
    if (medio % 2 == 0)
    {
      return sinPareja(elementos, medio + 2, fin);
    }
    else
    {
      return sinPareja(elementos, comienzo, medio - 1);
    }
  }
  if (elementos[medio] == elementos[medio - 1])
  {
    if (medio % 2 == 0)
    {
      return sinPareja(elementos, comienzo, medio - 2);
    }
    else
    {
      return sinPareja(elementos, medio + 1, fin);
    }
  }
  cout << elementos[medio] << endl;
  return;
}

int main()
{
  // ifstream myFile("Pruebas/Ejercicio6/10.in.txt");
  // cin.rdbuf(myFile.rdbuf());
  // ofstream myFile2("Pruebas/Ejercicio6/10.prueba.txt");
  // cout.rdbuf(myFile2.rdbuf());
  int fin;
  cin >> fin;
  int *elementos = new int[fin];
  for (int i = 0; i < fin; i++)
  {
    cin >> elementos[i];
  }
  sinPareja(elementos, 0, fin - 1);
  return 0;
}