#include "Tablero.h"
#include <stdio.h>

void inicializarTablero(Tablero *t){
	// 0 para los cuadros que no se pueden utilizar
	// 1 para los cuadros donde no hay piezas
	// 2 para las fichas del jugador 1
	// 3 para las damas del jugador 1
	// 4 para las fichas del jugador 2
	// 5 para las damas del jugador 2

	//fichas jugador 1
	int fila,col,init;
	for(fila = 0; fila < 3; fila++){
		init = fila%2;
		//fichas
		for(col = init; col < TAMANIO; col+=2){
			t->matriz[fila][col] = 2;
		}
		//casilleros nulos
		for(col = (init+1)%2; col < TAMANIO; col+=2){
			t->matriz[fila][col] = 0;
		}
	}

	//casilleros centrales
	for(fila = 3; fila < 7; fila++){
		init = fila%2;
		//casilleros vacios
		for(col = init; col < TAMANIO; col+=2){
			t->matriz[fila][col] = 1;
		}
		//casilleros nulos
		for(col = (init+1)%2; col < TAMANIO; col+=2){
			t->matriz[fila][col] = 0;
		}
	}

	//fichas jugador 2
	for(fila = 7; fila < TAMANIO; fila++){
		init = fila%2;
		//fichas
		for(col = init; col < TAMANIO; col+=2){
			t->matriz[fila][col] = 4;
		}
		//casilleros nulos
		for(col = (init+1)%2; col < TAMANIO; col+=2){
			t->matriz[fila][col] = 0;
		}
	}

}

int condicionFinal(Tablero *t, Tablero *tj){
	// A la funcion le faltaria la opcion de que empataron que seria cuando todas las fichas quedan bloqueadas,
	// en otras palabras ningun jugador puede mover ninguna ficha. Nose como hacerlo todavia

	int hayfichasJ1 = false, hayfichasJ2 = false, bloqueado = false, fil = 0, col = 0, final = false;
	//mientras no se haya terminado de recorrer el tablero y todavia no se hayan encontrado fichas de los dos jugadores
  for (fil = 0; fil < TAMANIO; fil++) {
    for (col = 0; col < TAMANIO; col++) {
      if(tj->matriz[fil][col] == 2 || tj->matriz[fil][col] == 3){
        hayfichasJ1 = true;
      } else if (tj->matriz[fil][col] == 4 || tj->matriz[fil][col] == 5){
        hayfichasJ2 = true;
      }
      if (hayfichasJ1 && hayfichasJ2) {
        break;
      }
    }
    if (hayfichasJ1 && hayfichasJ2) {
      break;
    }
  }

  bloqueado = sonIguales(t, tj);

  if (!hayfichasJ1) {
    printf("Jugador 1 ha quedado sin fichas, fin del juego");
    final = true;
  } else if (!hayfichasJ2) {
    printf("Jugador 2 ha quedado sin fichas, fin del juego");
    final = true;
  } else if (bloqueado) {
    printf("Tablero bloqueado, fin del juego");
    final = true;
  }
	return final;
}

//chequeo si los dos tableros son iguales
int sonIguales(Tablero *t, Tablero *tj) {
  int i, j, iguales = 1;
  for (i = 0; i < TAMANIO; i ++) {
    for (j = 0; j < TAMANIO; j++) {
      if (t->matriz[i][j] != tj->matriz[i][j]) {
        iguales = 0;
        break;
      }
    }
    if (iguales == 0) {
      break;
    }
  }
  return iguales;
}

void mostrarTablero(Tablero *t){
	int fila,col;

	printf("Estado actual del tablero: \n");
	for(col = 0; col < TAMANIO; col++){
		if (col == 0) {
			printf(" [%d] ",col);
		} else {
			printf("[%d] ",col);
		}

	}
	printf("\n");
	for(col = 0; col < TAMANIO; col++){
		//printf("[%d ] ",col);
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
        printf("| %d |",t->matriz[fila][col]);
      } else if (col == 9){
        printf(" %d | [%d]",t->matriz[fila][col], fila);
      } else {
        printf(" %d |",t->matriz[fila][col]);
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
	printf("\n\n");
}

void copiarTablero(Tablero *from, Tablero *to){
	int fil,col;
	for(fil = 0; fil < TAMANIO; fil++){
		for(col = 0; col < TAMANIO; col++){
			to->matriz[fil][col] = from->matriz[fil][col];
		}
	}
}

void informarEstado(Tablero *t){
	int fil,col,fichasJ1,fichasJ2,damasJ1,damasJ2;
	fichasJ1 = 0;
	damasJ1 = 0;
	fichasJ2 = 0;
	damasJ2 = 0;
	for(fil = 9; fil >= 0; fil--){
		for(col = 0; col < TAMANIO; col++){
			if(t->matriz[fil][col] == 2){
				fichasJ1++;
			}else if(t->matriz[fil][col] == 3){
				damasJ1++;
			}else if(t->matriz[fil][col] == 4){
				fichasJ2++;
			}else if(t->matriz[fil][col] == 5){
				damasJ2++;
			}
		}
	}
	printf("fichas Jugador 1: %d \n",fichasJ1);
	printf("damas Jugador 1: %d \n",damasJ1);
	printf("fichas Jugador 2: %d \n",fichasJ2);
	printf("damas Jugador 2: %d \n",damasJ2);
	printf("\n");
	printf("\n");
}
