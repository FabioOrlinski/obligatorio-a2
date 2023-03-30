#include <iostream>
#pragma once
using namespace std;
struct Asociacion
{
  string clave;
  int valor;
  Asociacion(string clave, int valor) : clave(clave), valor(valor){};
};