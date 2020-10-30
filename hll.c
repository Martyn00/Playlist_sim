// Copyright [2020] <Ionescu Martin>
#include <stdio.h>

#include <stdlib.h>

#include <string.h>

#define MAX 1 << 11
// functie de hash
unsigned int hash_function_int(void * a) {
  unsigned int uint_a = * ((unsigned int *) a);
  uint_a = ((uint_a >> 16u) ^ uint_a) * 0x45d9f3b;
  uint_a = ((uint_a >> 16u) ^ uint_a) * 0x45d9f3b;
  uint_a = (uint_a >> 16u) ^ uint_a;
  return uint_a;
}
// functie cu parametru un  int ce returneaza
// numarul de 0-uri in baza 2 de la finalul acestuia
// din primii 21 de biti
int num_zeros(int x) {
  int aux;
  for (int i = 1; i <= 21; i++) {
    if ((1 << i) > x) {
      aux = i;
      break;
    }
  }
  return 21 - (aux - 1);
}

int main(int argc, char * argv[]) {
  FILE * in;
  int k, m, has, val, bucket, nr;
  float S, z, alfa, e;
  int * M;
  M = (int * ) calloc(MAX, sizeof(int));
  if ((in = fopen(argv[argc - 1], "rb")) == NULL) {
    printf("error\n");
    return 0;
  }
  m = ((1 << 21) - 1);
  // citirea numerelor si punerea acestora in vector
  while (fscanf(in , "%d", & k) != EOF) {
    has = hash_function_int(& k) % (1 << 31);
// se iau primii 11 de biti in bucket
    bucket = (hash_function_int(& k) & (m << 21)) >> 21;
// se iau ultimii 21 de biti in bucket
    val = (has & m);
    nr = num_zeros(val);
// schimbare valorii din vector in cazul in care numarul
// de 0-uri este mai mare decat cel curent
    if (nr > M[bucket]) {
      M[bucket] = nr;
    }
  }
// crearea lui Z
  float n = (float)(1 << 11);
  S = 0;
  for (int i = 0; i < MAX; i++) {
    float sum = 1 << M[i];
    S = S + 1 / sum;
  }
  z = 1 / S;
// Formula lui alfa pentru 11 biti
  alfa = 0.7213 / (1 + 1.079 / n);
// Calcularea lui E
  e = alfa * n * n * z;
// afisarea lui E
  printf("%d", (int) e);
  free(M);
  fclose(in);
  return 0;
}
