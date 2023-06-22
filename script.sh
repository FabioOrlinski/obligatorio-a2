#!/bin/bash

# ejercicios=("ejercicio7")
# archivos=("10" "100" "1000" "10000")
ejercicios=("ejercicio2")
archivos=("10" "100" "1000" "10000" "162793")

# Crear archivo de resultados
> resultados.txt

for ejercicio in "${ejercicios[@]}"
do
    echo "Ejecutando para el ejercicio: $ejercicio"

    # Compilar el código fuente
    g++ -o "$ejercicio" "$ejercicio.cpp"

    for archivo in "${archivos[@]}"
    do
        echo "Ejecutando para el archivo: $archivo"

        # Ejecutar el programa con la entrada y guardar la salida en un archivo de prueba
        ./"$ejercicio.exe" < "Pruebas/$ejercicio/$archivo.in.txt" > "Pruebas/$ejercicio/$archivo.prueba.txt"

        # Comparar la salida generada con la salida esperada
        if diff --strip-trailing-cr "Pruebas/$ejercicio/$archivo.out.txt" "Pruebas/$ejercicio/$archivo.prueba.txt" >/dev/null; then
            echo "$ejercicio prueba $archivo resultado OK" >> resultados.txt
        else
            echo "$ejercicio prueba $archivo resultado ERROR" >> resultados.txt
        fi
    done

    echo "======================================"
done