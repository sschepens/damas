#include "Tablero.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct Array {
  struct Nodo *array;
  int used;
  int size;
} Array;

typedef struct Nodo {
  int tablero[TAMANIO][TAMANIO];
  int riesgo;
  Array hijos;
} Nodo;

void initArray(Array *a, int initialSize) {
  a->array = NULL;
  a->used = 0;
  a->size = initialSize;
}

Array* crearArray(int size) {
  Array *a = (Array *) malloc(sizeof(Array));
  initArray(a, size);
  return a;
}

Nodo* crearNodo() {
  Nodo *nodo = (Nodo *) malloc(sizeof(Nodo));
  initArray(&(nodo->hijos), 0);
  //inicializo riesgo en 0;
  nodo->riesgo = 0;
  return nodo;
}

Tablero* crearTableroVacio() {
  int i, j;
  Tablero *t = (Tablero *) malloc(sizeof(Tablero));
  for(i=0; i< TAMANIO; i++){
    for(j=0; j < TAMANIO; j++){
      t->matriz[i][j] = 0;
    }
  }
  return t;
}

void copiarTableroArbol(Tablero *from, Nodo *to){
	int fil,col;
	for(fil = 0; fil < TAMANIO; fil++){
		for(col = 0; col < TAMANIO; col++){
			to->tablero[fil][col] = from->matriz[fil][col];
		}
	}
}

void copiarArbolTablero(Nodo *from, Tablero *to){
	int fil, col;
	for(fil = 0; fil < TAMANIO; fil++){
		for(col = 0; col < TAMANIO; col++){
			to->matriz[fil][col] = from->tablero[fil][col];
		}
	}
}

void copiarArbolArbol(Nodo *from, Nodo *to){
	int fil,col;
	for(fil = 0; fil < TAMANIO; fil++){
		for(col = 0; col < TAMANIO; col++){
			to->tablero[fil][col] = from->tablero[fil][col];
		}
	}
}
void insertArray(Array *a, Nodo *element) {
  if (a->size == 0) {
    a->size = 1;
    a->array = (Nodo *)malloc(sizeof(Nodo));
  } else if (a->used == a->size) {
    a->size += 1;
    a->array = (Nodo *)realloc(a->array, a->size * sizeof(Nodo));
  }
  a->array[a->used] = *element;
  a->used += 1;
}

void eliminarNodo(Nodo *nodo);

void freeArray(Array *a) {
  int i;
  for (i = 0; i < a->used; i++) {
    eliminarNodo(&(a->array[i]));
  }
  free(a->array);
  a->array = NULL;
  a->used = a->size = 0;
}

void eliminarNodo(Nodo *nodo) {
  freeArray(&(nodo->hijos));
}

void freeFirstLevel(Array *a) {
  free(a->array);
  a->array = NULL;
  a->used = a->size = 0;
}

void concatArray(Array *a, Array *b) {
  int i;
  if (b->used == 0) {
    freeArray(b);
    free(b);
    return;
  }
  for (i = 0; i < b->used; i++) {
    insertArray(a, &(b->array[i]));
  }
  freeFirstLevel(b);
  free(b);
}

void inicializarArbol(Nodo *arbol, Tablero *tablero) {
  //copio el tablero al nodo;
  copiarTableroArbol(tablero, arbol);
}

//mostrar el tablero de un nodo
void mostrarTableroNodo(Nodo *t){
	int fila,col;
  printf("Estado actual del tablero: \n");
  for(col = 0; col < TAMANIO; col++){
    if (col == 0) {
      printf("-----");
    } else {
      printf("----");
    }
  }
  printf("\n");
	for(fila = 0; fila < TAMANIO; fila++){
		for(col = 0; col < TAMANIO; col++){
      if (col == 0) {
        printf("| %d |",t->tablero[fila][col]);
      } else {
        printf(" %d |",t->tablero[fila][col]);
      }
		}
		printf("\n");
		for(col = 0; col < TAMANIO; col++){
      if (col == 0) {
        printf("-----");
      } else {
        printf("----");
      }
		}
		printf("\n");
	}
	printf("\n");
	printf("\n");
}
