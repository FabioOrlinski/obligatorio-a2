/**
 * AVL con cantidadOcurrencias
 * Se tiene un libro, el cual tiene una cantidad N de palabras, siendo en total P
palabras distintas. Se desea implementar una función en que permita mostrar las
distintas P palabras ordenadas y su cantidad de apariciones en el libro.
La función deberá recibir como entrada el número P de palabras, seguido por una
palabra por línea, totalizando P+1 líneas. Debe mostrar por pantalla las P palabras
distintas ordenadas alfabéticamente de forma descendente, con cada línea
conteniendo la palabra y sus apariciones en el texto.
Input
La primera línea de la entrada contiene un número entero positivo N, seguido por N
líneas con una palabra cada una.
Salida
Imprime P líneas conteniendo una palabra y su cantidad de apariciones cada una.
Las P líneas deben estar ordenadas alfabéticamente de forma descendente por
palabra.
Restricciones
● La operación debe tener orden O(P * Log2 P) peor caso, siendo P la cantidad
de palabras distintas en el texto.
Ejemplo
Input:
10
sos
mi
locura
y
mi
pasion
tuya
es
mi
vida
Output:
y 1
vida 1
tuya 1
sos 1
pasion 1
mi 3
locura 1
es 1
 */

#include <iostream>
#include <string>
#include <cstring>

using namespace std;

class NodoAVL
{
  public:
    string palabra;
    int altura;
    NodoAVL *izquierda;
    NodoAVL *derecha;
    int conteo;

    NodoAVL(string palabra, int altura, NodoAVL *izquierda, NodoAVL *derecha, int conteo): palabra(palabra), altura(altura), izquierda(izquierda), derecha(derecha), conteo(conteo){};
    NodoAVL(string palabra): palabra(palabra), altura(1), izquierda(nullptr), derecha(nullptr), conteo(1){};
};

int obtenerAltura(NodoAVL *nodo)
{
  if (nodo == nullptr)
  {
    return 0;
  }
  return nodo->altura;
}

int maximo(int a, int b)
{
  return (a > b) ? a : b;
}

int obtenerFactorBalance(NodoAVL *nodo)
{
  if (nodo == nullptr)
  {
    return 0;
  }
  return obtenerAltura(nodo->izquierda) - obtenerAltura(nodo->derecha);
}

NodoAVL *rotarDerecha(NodoAVL *z)
{
  NodoAVL *y = z->izquierda;
  NodoAVL *T3 = y->derecha;

  y->derecha = z;
  z->izquierda = T3;

  z->altura = maximo(obtenerAltura(z->izquierda), obtenerAltura(z->derecha)) + 1;
  y->altura = maximo(obtenerAltura(y->izquierda), obtenerAltura(y->derecha)) + 1;

  return y;
}
NodoAVL *rotarIzquierda(NodoAVL *y)
{
  NodoAVL *x = y->derecha;
  NodoAVL *T2 = x->izquierda;

  x->izquierda = y;
  y->derecha = T2;

  y->altura = maximo(obtenerAltura(y->izquierda), obtenerAltura(y->derecha)) + 1;
  x->altura = maximo(obtenerAltura(x->izquierda), obtenerAltura(x->derecha)) + 1;

  return x;
}
NodoAVL *insertarPalabraAVL(NodoAVL *nodo, string palabra)
{
  if (nodo == nullptr)
  {
    NodoAVL* nuevoNodo = new NodoAVL(palabra);
    return nuevoNodo;
  }

  if (palabra < nodo->palabra)
  {
    nodo->izquierda = insertarPalabraAVL(nodo->izquierda, palabra);
  }
  else if (palabra > nodo->palabra)
  {
    nodo->derecha = insertarPalabraAVL(nodo->derecha, palabra);
  }
  else
  {
    nodo->conteo++;
    return nodo;
  }
  nodo->altura = 1 + maximo(obtenerAltura(nodo->izquierda), obtenerAltura(nodo->derecha));
  int factorBalance = obtenerFactorBalance(nodo);

  // Rotación a la derecha
  if (factorBalance > 1 && palabra < nodo->izquierda->palabra)
  {
    return rotarDerecha(nodo);
  }

  // Rotación a la izquierda
  if (factorBalance < -1 && palabra > nodo->derecha->palabra)
  {
    return rotarIzquierda(nodo);
  }

  // Rotación doble a la derecha
  if (factorBalance > 1 && palabra > nodo->izquierda->palabra)
  {
    nodo->izquierda = rotarIzquierda(nodo->izquierda);
    return rotarDerecha(nodo);
  }

  // Rotación doble a la izquierda
  if (factorBalance < -1 && palabra < nodo->derecha->palabra)
  {
    nodo->derecha = rotarDerecha(nodo->derecha);
    return rotarIzquierda(nodo);
  }

  return nodo;
}

void imprimirAVL(NodoAVL *nodo)
{
  if (nodo != nullptr)
  {
    imprimirAVL(nodo->derecha);
    cout << nodo->palabra << " " << nodo->conteo << endl; // Imprimir palabra y conteo
    imprimirAVL(nodo->izquierda);
    delete nodo;
  }
}

int main()
{
  NodoAVL *raiz = nullptr; // Inicializar el árbol AVL como vacío
  int cantidadPalabras;
  cin >> cantidadPalabras;
  // Leer las palabras del texto y insertarlas en el árbol AVL
  for (int i = 0; i < cantidadPalabras; i++)
  {
    string palabra;
    cin >> palabra;
    raiz = insertarPalabraAVL(raiz, palabra);
  }
  imprimirAVL(raiz);
}

// g++ -o ejemplo ejercicio2.cpp
// ./ejemplo.exe < pruebas/pruebaej2.in.txt > pruebas/pruebaej2.out.txt
// diff --strip-trailing-cr pruebas/pruebaej2.out.txt pruebas/pruebaej2.expected.txt