#define TAMANIO 10
#ifndef TABLERO_H_
#define TABLERO_H_

//estructura del tablero
typedef struct Tablero {
    int matriz[TAMANIO][TAMANIO];
}Tablero;

void mostrarTablero(Tablero *t);
void inicializarTablero(Tablero *t);
void copiarTablero(Tablero *from, Tablero *to);
int sonIguales(Tablero *t, Tablero *tj);
int condicionFinal(Tablero *t, Tablero *tj);
void informarEstado(Tablero *t);

#endif /* TABLERO_H_ */
