// Copyright [2020] <Ionescu Martin>
#include <stdio.h>

#include <stdlib.h>

#include <string.h>

#define NMAX 2000000

int main() {
  unsigned char * v;
  int max, val;
  v = calloc(NMAX, sizeof(unsigned int));
  max = -2;
// citeste fiecare numar pana la final
// si il pune in vectorul de frecventa
  while (scanf("%d", & val) != EOF) {
    if (val > max) {
      max = val;
    }
    v[val]++;
  }
// Afiseaza numarul si apoi numarul de
// aparitii al acestuia
  for (int i = 0; i <= max; i++) {
    if (v[i] != 0)
      printf("%d %d\n", i, v[i]);
  }
  free(v);
  return 0;
}
