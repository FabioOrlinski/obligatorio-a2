/**
 * Letra:
 * Se tiene una base de datos de estudiantes de la Universidad ORT. En esta
instancia, cada estudiante está representado por una palabra conformada por las
iniciales de su nombre y sus dos apellidos completos. Se conoce al conjunto de
notas de exoneraciones y exámenes en diferentes asignaturas. Se desea
implementar una tabla de hash cerrado que permita buscar los estudiantes por
número de identificación y obtener el promedio de sus notas.
Se pide implementar una función en que reciba como entrada los códigos de
identificación de los estudiantes y sus respectivas notas de exoneración o
aprobación de examen. La función deberá imprimir por pantalla el código de
identificación de los alumnos y el PAC (Promedio Acumulado de Calificaciones) de
cada uno de ellos. El listado deberá respetar el orden en el que fueron introducidos
los alumnos y sus notas. La implementación debe utilizar una tabla de hash cerrado
con resolución de colisiones distinta al método de exploración lineal
 * Input:
 * La primera línea de la entrada contiene un número entero positivo A, el número de
estudiantes de la universidad. Le siguen A líneas distintas de formato N K K1 K2 …
Kk siendo N las iniciales y apellidos del estudiante, K la cantidad de aprobaciones y
exoneraciones y los siguientes valores las notas obtenidas.
 * Output:
 * A líneas de formato N P, siendo N las iniciales y apellidos del estudiante y P el PAC del alumno.
 * Restricciones:
 * - Utilizar una tabla de hash cerrado
 * - Resolver en orden temporal: O(A) promedio, siendo A la cantidad de usuarios
 * Ejemplo:
 * - Input:
 * 3
 * CHBuenoSuarez 4 10 30 50 70
 * DMForlanCorazo 3 100 100 100
 * FSValverdeDipetta 5 100 90 80 70 60
 * - Output:
 * CHBuenoSuarez 40
 * DMForlanCorazo 100
 * FSValverdeDipetta 80
*/
#include <iostream>
using namespace std;

int main()
{

  return 0;
}