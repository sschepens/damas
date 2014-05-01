#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include "Tablero.c" // FIJATE, YO LO CAMBIE POR .C Y ME ANDUVO TE LO PASO COMO ME LO DIO EL ORIGINALMENTE.
// #include "Juego.h"   NI IDEA QUE ES ESO, COMO NO ME PASO EL ARCHIVO LO COMENTE ASI EJECUTA
#include <time.h>
#include "jugador1.c"

int main(){
	printf("INICIO DE JUEGO");
	printf("\n");
	printf("\n");

	clock_t comienzo, final;
	double tiempo;

	Tablero tActual, tJugado;
	//coloca las fichas en las posiciones iniciales
	inicializarTablero(&tActual);
  //incializo los dos tableros iguales para poder comparar si esta bloqueado el tablero
	inicializarTablero(&tJugado);
	mostrarTablero(&tActual);
  informarEstado(&tActual);

	//inicializa el turno para el primer jugador
	int turno = 0;
  char c;
  do {
    // printf("Presione Enter para continuar\n");
    // scanf("%c", &c);
    if (turno != 0) {
      copiarTablero(&tJugado, &tActual);
    }
    if (turno == 1000) {
      return;
    }
		//jugador 1
		if(turno % 2 == 0){
			printf("Jugada nº: %d, Jugador 1 \n",turno);
			comienzo = clock();
			jugar1(&tActual,&tJugado);
			final = clock();
			tiempo = (double)(final - comienzo);

			printf("El jugador 1 tardo %f segundos\n",tiempo);
			mostrarTablero(&tJugado);
      informarEstado(&tJugado);
		//jugador 2
		} else {
			printf("Jugada nº: %d, Jugador 2 \n",turno);
			comienzo = clock();
			jugar2(&tActual,&tJugado);
			final = clock();
			tiempo = (double)(final - comienzo);

			printf("El jugador 2 tardo %f segundos\n",tiempo);
			mostrarTablero(&tJugado);
      informarEstado(&tJugado);
		}
		turno++;
  } while (!condicionFinal(&tActual, &tJugado));

	return 0;
}
