#include <iostream>

using namespace std;

class Elemento {
public:
    int tamano;
    int lineasCodigo;
    int puntaje;

    Elemento(int tamano, int lineasCodigo, int puntaje) : tamano(tamano), lineasCodigo(lineasCodigo), puntaje(puntaje) {}
};

int max(int a, int b) {
    return a >= b ? a : b;
}

void mochilaDP(Elemento **elementos, int cantArchivos, int maximoTamano, int maximoLineasCodigo) {
    int ***matDP = new int **[cantArchivos + 1];
    for (int i = 0; i <= cantArchivos; i++) {
        matDP[i] = new int *[maximoTamano + 1];
        for (int j = 0; j <= maximoTamano; j++) {
            matDP[i][j] = new int[maximoLineasCodigo + 1];
            for (int k = 0; k <= maximoLineasCodigo; k++) {
                matDP[i][j][k] = 0;
            }
        }
    }
    for (int i = 1; i <= cantArchivos; i++) {
        for (int j = 0; j <= maximoTamano; j++) {
            for (int k = 0; k <= maximoLineasCodigo; k++) {
                bool noEntra = j < elementos[i - 1]->tamano || k < elementos[i - 1]->lineasCodigo;
                matDP[i][j][k] = noEntra ? matDP[i - 1][j][k]
                                        : max(matDP[i - 1][j][k], matDP[i - 1][j - elementos[i - 1]->tamano][k - elementos[i - 1]->lineasCodigo] + elementos[i - 1]->puntaje);
            }
        }
    }
    int maximoPuntaje = matDP[cantArchivos][maximoTamano][maximoLineasCodigo];
    // Liberación de memoria
    for (int i = 0; i <= cantArchivos; i++) {
        for (int j = 0; j <= maximoTamano; j++) {
            delete[] matDP[i][j];
        }
        delete[] matDP[i];
    }
    delete[] matDP;
    // Imprimo el resultado
    cout << maximoPuntaje << endl;
}

int main() {
    int cantArchivos, maximoTamano, maximoLineasCodigo;
    cin >> cantArchivos >> maximoTamano >> maximoLineasCodigo;
    Elemento **elementos = new Elemento *[cantArchivos];
    for (int i = 0; i < cantArchivos; i++) {
        int tamano, lineasCodigo, puntaje;
        cin >> tamano >> lineasCodigo >> puntaje;
        elementos[i] = new Elemento(tamano, lineasCodigo, puntaje);
    }
    mochilaDP(elementos, cantArchivos, maximoTamano, maximoLineasCodigo);
    // Liberación de memoria
    for (int i = 0; i < cantArchivos; i++) {
        delete elementos[i];
    }
    delete[] elementos;
    return 0;
}