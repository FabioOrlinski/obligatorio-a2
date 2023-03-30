/**
 * Cola de prioridad
 * Letra
Una aerolínea desea optimizar su sistema de check-in para favorecer a los
pasajeros más frecuentes de la misma. Se recibirá un número R de reservas
distintas, compuestas por P personas indicadas en la reserva. Cada persona tiene
un pasaporte y cantidad de vuelos realizados con la aerolínea. Las personas
pertenecientes a la misma reserva ingresan juntos, favoreciendo inicialmente a
aquellas reservas que tienen un más alto promedio de vuelos realizados con la
aerolínea.
Input
La función deberá recibir como entrada el número R de reservas, seguido por R
grupos conformados por un número P de personas en la reserva para seguir con P
líneas, cada una conteniendo al número de pasaporte del viajero y la cantidad de
vuelos realizados.
Salida
Debe mostrar por pantalla R líneas ordenadas descendientemente por promedio de
vuelos de los integrantes de la reserva. Las líneas deben contener el promedio de
vuelos de los integrantes seguido por sus pasaportes, todos separados por un
espacio y en el mismo orden original en el que fueron ingresados.
Restricciones
● El orden de ejecución de la carga de datos no puede superar O(P + R) caso
promedio y O(P + R * Log2 R) peor caso, mientras que la impresión no debe
llevar más de O(R * Log2 R) peor caso.
Ejemplo:
Input:
3
2
A123456 10
B234567 11
1
C345678 40
3
D456789 50
E567890 10
F678901 30
Output:
40 C345678
30 D456789 E567890 F678901
10.5 A123456 B234567
 */