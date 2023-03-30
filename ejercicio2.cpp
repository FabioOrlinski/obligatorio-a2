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