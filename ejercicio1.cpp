#include <iostream>
#include <fstream>
#include <cmath>
#include ".\tads\asociacion.cpp"
#include ".\tads\hash.cpp"
#include ".\tads\lista.cpp"
using namespace std;

int main()
{
   ifstream myFile("pruebas/pruebaej1.in.txt");
    cin.rdbuf(myFile.rdbuf());
    // Si desean tirar la salida a un archivo, usen las siguientes líneas (si no, sáquenlas):
    ofstream myFile2("pruebas/pruebaej1.out.txt");
    cout.rdbuf(myFile2.rdbuf());
  int cantAlumnos;
  cin >> cantAlumnos;
  HashCerrado *hash = new HashCerrado(cantAlumnos);//, fHash);
  Lista<string> *lista = new Lista<string>();
  string nombre;
  float cantMaterias;
  int nota;
  for (int i = 0; i < cantAlumnos; i++)
  {
    int total=0;
    cin >> nombre;
    lista->insertarFin(nombre);
    cin >> cantMaterias;
    for (float i = 0; i < cantMaterias; i++)
    {
      cin >> nota;
      total += nota;
    }
    total = int(round(total / cantMaterias));
    Asociacion *as = new Asociacion(nombre, total);
    hash->agregar(as);
  }
  for (int i = 0; i < cantAlumnos; i++)
  {
    hash->imprimir(lista->primero());
    lista->borrar(lista->primero());
  }
  
  return 0;
}