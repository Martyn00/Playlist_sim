// Copyright [2020] <Ionescu Martin>
#include <stdio.h>

#include <stdlib.h>

#include <string.h>
// structura pentru hash
struct info {
  char * key;
  unsigned char value;
};

// functia de hash
unsigned int hashh(void * a) {
  unsigned char * puchar_a = (unsigned char *) a;
  int hash = 5381;
  int c;

  while ((c = * puchar_a++))
    hash = ((hash << 5u) + hash) + c; /* hash * 33 + c */

  return hash;
}
// structura de hashtable
struct Hashtable {
  struct info buckets[100];
  int size;
  int hmax;
  // f has
  // compare
};
// initializare hash_table-ului
void init_table(struct Hashtable * vect) {
  vect -> size = 0;
  vect -> hmax = 100;
  for (int i = 0; i < 100; i++) {
    vect -> buckets[i].key = NULL;
    vect -> buckets[i].value = 0;
  }
}
// adaugare de element in hashtable
void put_in_hash(char * key, struct Hashtable * vect) {
  unsigned char t;
  t = hashh(key) % 100;
  // cazul in care bucket-ul e NULL
  if (vect -> buckets[t].key == NULL) {
    vect -> buckets[t].key = key;
    vect -> buckets[t].value = 1;
    vect -> size++;
    return;
  }
// Verificare daca se afla acelasi lucru in bucket
// si creste size si value in caz pozitiv
  if (strcmp(vect -> buckets[t].key, key) == 0) {
    vect -> buckets[t].value++;
    vect -> size++;
    free(key);
    return;
  }
// Daca cheia nu e aceeasi cu sirul se cauta in
// hashtable pana la gasirea unei valori nule
// inserandu-se pe pozitia respectiva
// daca nu se gaseste se reincepe cautarea
// de la inceputul hashtable-ului
  t++;
  while (vect -> buckets[t].key != NULL) {
    t++;
    if (t == 99) {
      t = 0;
    }
  }
  vect -> buckets[t].key = key;
  vect -> buckets[t].value = 1;
  vect -> size++;
}
// functie pentru afisare hashtable
void show_hash(struct Hashtable * vect) {
  for (int i = 0; i <= 99; i++) {
    if (vect -> buckets[i].key != NULL) {
      printf("%s %d\n", vect -> buckets[i].key, vect -> buckets[i].value);
    }
  }
}
// eliberare memorie hashtable
void free_hash(struct Hashtable * vect) {
  for (int i = 0; i < vect -> hmax; i++) {
    free(vect -> buckets[i].key);
  }
}
// alocare memorie pentru hashtable
// citire si adaugare in hashtable
// afisare si eliberare hashtable
int main() {
  char val[101];
  struct Hashtable * vect;
  char * key;
  vect = malloc(sizeof(struct Hashtable));
  init_table(vect);
  while (scanf("%s", val) != EOF) {
    key = calloc(100, sizeof(char));
    snprintf(key, sizeof(val), "%s", val);
    put_in_hash(key, vect);
  }
  show_hash(vect);
  free_hash(vect);
  free(vect);
  return 0;
}
