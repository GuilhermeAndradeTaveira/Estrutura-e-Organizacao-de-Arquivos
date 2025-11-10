#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TABLE_SIZE 10

typedef struct {
  long offset;
  int chave;
  int isOcupado;
} Registro;

typedef struct {
  Registro *registros;
} HashTable;

HashTable *initTable() {
  HashTable *table = (HashTable *)malloc(TABLE_SIZE * sizeof(HashTable));
  for (int i = 0; i < TABLE_SIZE; i++) {
    table[i].registros = NULL;
  }
  return table;
}

unsigned int hash(int chave) { return chave % TABLE_SIZE; }

int addEntry(Registro *r, HashTable *h, FILE *fp) {
  if (r == NULL) {
    return 0;
  }
  int index = hash(r->chave);
  fseek(fp, 0, SEEK_END);
  long pos = ftell(fp);
  r->offset = pos;
  r->isOcupado = 1;

  fwrite(r, sizeof(Registro), 1, fp);
  h[index].registros = (Registro *)malloc(sizeof(Registro));
  *h[index].registros = *r;

  return 1;
}

Registro *searchEntry(int chave, HashTable *h, FILE *fp) {
  int index = hash(chave);

  if (h[index].registros != NULL && h[index].registros->chave == chave) {
    Registro *r = (Registro *)malloc(sizeof(Registro));
    fseek(fp, h[index].registros->offset, SEEK_SET);
    fread(r, sizeof(Registro), 1, fp);
    return r;
  }
  return NULL;
}

int deleteEntry(int chave, HashTable *h, FILE *fp) {
  int index = hash(chave);
  if (h[index].registros == NULL) {
    return -1;
  }
  if (h[index].registros->chave == chave &&
      h[index].registros->isOcupado == 1) {
    fseek(fp, h[index].registros->offset, SEEK_SET);
    Registro aux;
    fread(&aux, sizeof(Registro), 1, fp);
    aux.isOcupado = 0;
    fseek(fp, h[index].registros->offset, SEEK_SET);
    fwrite(&aux, sizeof(Registro), 1, fp);
    free(h[index].registros);
    h[index].registros = NULL;
    return 1;
  }
  return 0;
}

int main() { return 0; }
