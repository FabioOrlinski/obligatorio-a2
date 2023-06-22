#include <iostream>
#include <string>
#include <fstream>

using namespace std;

void cambiarNivel(long long int *coeficientesBinomiales, int nivel)
{
  for (int i = nivel; i >= 0; i--)
  {
    if (i == 0 || i == nivel)
    {
      continue;
    }
    coeficientesBinomiales[i] = coeficientesBinomiales[i] + coeficientesBinomiales[i - 1];
  }
}

int main()
{
  int Cota, P, nivel = 0;
  cin >> Cota >> P;
  long long int *coeficientesBinomiales = new long long int[Cota + 1];
  for (int i = 0; i < Cota + 1; coeficientesBinomiales[i++] = 1);
  for (int i = 0; i < P; i++)
  {
    int N, K;
    cin >> N >> K;
    if (N > nivel)
    {
      for (int i = nivel + 1; i < N + 1; i++)
      {
        cambiarNivel(coeficientesBinomiales, i);
      }
      nivel = N;
    }
    cout << coeficientesBinomiales[K] << endl;
  }
  delete[] coeficientesBinomiales;
  return 0;
}