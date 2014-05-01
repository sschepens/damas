#include "Tablero.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include "funcjugador.c"

#define NIVELES 3

int filaAvance(int j){ //devuelve sentido que avanza cada jugador
  if (j == 1){
    return 1;
  } else {
    return -1;
  }
}

int filaObjetivo(int j){ //devuelve sentido que avanza cada jugador
  if (j == 1){
    return 9;
  } else {
    return 0;
  }
}

int peon(int j){   //devuelve el numero para el peon del jugador
  if (j == 1){
    return 2;
  } else {
    return 4;
  }
}

int dama(int j){  //devuelve el numero para la dama del jugador
  if (j == 1){
    return 3;
  } else {
    return 5;
  }
}

int dOponente(int j){ //devuelve el numero de la dama del oponente
  if (j == 1){
    return 5;
  } else {
    return 3;
  }
}

int pOponente(int j){ //devuelve el numero del peon del oponente
  if (j == 1){
    return 4;
  } else {
    return 2;
  }
}

int jOponente(int j){ //devuelve el numero del peon del oponente
  if (j == 1){
    return 2;
  } else {
    return 1;
  }
}

bool casilleroVacio(Nodo *n, int i, int j) {
  return n->tablero[i][j] == 1;
}

void convertirADama(Nodo * nodo, int i, int j){ //convierte un peon a dama
  nodo->tablero[i][j] = nodo->tablero[i][j] + 1;
}

bool estoyEnBorde(int i, int j){ //me dice si la ficha esta parada en el borde del tablero
  return ((i == 0) || (i == TAMANIO - 1) || (j == 0) || (j == TAMANIO - 1));
}

bool dimensionesValidas (int num){ //me dice si el numero se encuentra entre 0 y TAMANIO
  return ((num < TAMANIO) && (num >= 0));
}

int fichaEnCasillero(Nodo *n, int i, int j){ //me dice que ficha se encuentra en el casillero i j
  return n->tablero[i][j];
}

bool fichaOponente(Nodo *n, int i, int j, int jug) {
  return n->tablero[i][j] == pOponente(jug) || n->tablero[i][j] == dOponente(jug);
}

bool fichaAliada(Nodo *n, int i, int j, int jug) {
  return n->tablero[i][j] == peon(jug) || n->tablero[i][j] == dama(jug);
}

int asignarRiesgoSiPuedoComer(Nodo * n, int i,int j, int jug){ //En caso de poder comer un peon le resta 1 a riesgo, en caso de dama 2
  int riesgo = 0, aux = 1;
  bool salir1, salir2, salir3, salir4;
  salir1 = salir2 = salir3 = salir4 = false;
  if (fichaEnCasillero(n, i, j) == peon(jug)) {
    if (dimensionesValidas(i+(2*filaAvance(jug))) && dimensionesValidas(j+2) && casilleroVacio(n, i+(2*filaAvance(jug)), j+2)) {
      if (pOponente(jug) == fichaEnCasillero(n,i+filaAvance(jug),j+1)) {
        riesgo = -1;
      } else if (dOponente(jug) == fichaEnCasillero(n,i+filaAvance(jug),j+1)) {
        riesgo = -2;
      }
    } else if (dimensionesValidas(i+(2*filaAvance(jug))) && dimensionesValidas(j-2) && casilleroVacio(n, i+(2*filaAvance(jug)), j-2)) {
      if (pOponente(jug) == fichaEnCasillero(n,i+filaAvance(jug),j+1)) {
        riesgo = -1;
      } else if (dOponente(jug) == fichaEnCasillero(n,i+filaAvance(jug),j+1)) {
        riesgo = -2;
      }
    }
  } else {
    while ((aux<TAMANIO) && (!salir1 && !salir2 && !salir3 && !salir4 )) {
      if (!(dimensionesValidas(i+aux) && dimensionesValidas(j+aux) && (casilleroVacio(n,i+aux,j+aux) && !salir1))){
        if (dimensionesValidas(i+aux+1) && dimensionesValidas(j+aux+1) && casilleroVacio(n,i+aux+1,j+aux+1) && (fichaOponente(n, i+aux, j+aux, jug) && !salir1)){
          if (pOponente(jug) == fichaEnCasillero(n,i+aux,j+aux)) {
            riesgo = -1;
          } else if (dOponente(jug) == fichaEnCasillero(n,i+aux,j+aux)) {
            riesgo = -2;
          }
        }
        salir1 = true;
      }

      if (!(dimensionesValidas(i+aux) && dimensionesValidas(j-aux) && (casilleroVacio(n,i+aux,j-aux) && !salir1))){
        if (dimensionesValidas(i+aux+1) && dimensionesValidas(j-aux-1) && casilleroVacio(n,i+aux+1,j-aux-1) && (fichaOponente(n, i+aux, j-aux, jug) && !salir1)){
          if (pOponente(jug) == fichaEnCasillero(n,i+aux,j-aux)) {
            riesgo = -1;
          } else if (dOponente(jug) == fichaEnCasillero(n,i+aux,j-aux)) {
            riesgo = -2;
          }
        }
        salir2 = true;
      }

      if (!(dimensionesValidas(i-aux) && dimensionesValidas(j+aux) && (casilleroVacio(n,i-aux,j+aux) && !salir1))){
        if (dimensionesValidas(i-aux-1) && dimensionesValidas(j+aux+1) && casilleroVacio(n,i-aux-1,j+aux+1) && (fichaOponente(n, i-aux, j+aux, jug) && !salir1)){
          if (pOponente(jug) == fichaEnCasillero(n,i-aux,j+aux)) {
            riesgo = -1;
          } else if (dOponente(jug) == fichaEnCasillero(n,i-aux,j+aux)) {
            riesgo = -2;
          }
        }
        salir3 = true;
      }

      if (!(dimensionesValidas(i-aux) && dimensionesValidas(j-aux) && (casilleroVacio(n,i-aux,j-aux) && !salir1))){
        if (dimensionesValidas(i-aux-1) && dimensionesValidas(j-aux-1) && casilleroVacio(n,i-aux-1,j-aux-1) && (fichaOponente(n, i-aux, j-aux, jug) && !salir1)){
          if (pOponente(jug) == fichaEnCasillero(n,i-aux,j-aux)) {
            riesgo = -1;
          } else if (dOponente(jug) == fichaEnCasillero(n,i-aux,j-aux)) {
            riesgo = -2;
          }
        }
        salir4 = true;
      }
      aux++;
    }
    //si soy dama
  }
  return riesgo;
}

bool damaMePuedeComer(Nodo *n, int i, int j, int jug){ // si una dama me puede comer me devuelve true
  //Aca no pregunto si i-1, i+1, j+1, j-1 se excede de las dimensiones validas, ya que si i o j estubieran en el borde no hubiese entrado
  //a esta funcion
  int aux = 1;
  bool salir1, salir2, salir3, salir4;
  salir1 = false;
  salir2 = false;
  salir3 = false;
  salir4 = false;
  while ((aux<TAMANIO) && (!salir1 || !salir2 || !salir3 || !salir4 )){
    if ((dimensionesValidas(i+aux)) && (dimensionesValidas(j+aux)) && (!casilleroVacio(n,i+aux,j+aux) && !salir1)){ //si hay una ficha en el medio salvo uqe sea dama no me pueden comer se supone que no va a aparecer la opcion de sumar uno y que haya un peon
      if ((dOponente(jug) == fichaEnCasillero(n,i + aux, j + aux)) && (casilleroVacio(n,i-1,j-1))){
        return true; //salgo porque se que una dama me puede comer
      } else {
        salir1 = true; //lo pongo en verdadero porque por mas que despues aparezca una ficha la dama no puede llegar a mi.
      }
    }
    if ((dimensionesValidas(i+aux)) && (dimensionesValidas(j-aux)) && (!casilleroVacio(n,i+aux,j-aux) && !salir2)){ //si hay una ficha en el medio salvo uqe sea dama no me pueden comer se supone que no va a aparecer la opcion de sumar uno y que haya un peon
      if ((dOponente(jug) == fichaEnCasillero(n,i + aux, j - aux)) && (casilleroVacio(n,i-1,j+1))){
        return true; //salgo porque se que una dama me puede comer
      } else {
        salir2 = true; //lo pongo en verdadero porque por mas que despues aparezca una ficha la dama no puede llegar a mi.
      }
    }
    if ((dimensionesValidas(i-aux)) && (dimensionesValidas(j+aux)) && (!casilleroVacio(n,i-aux,j+aux) && !salir3)){ //si hay una ficha en el medio salvo uqe sea dama no me pueden comer se supone que no va a aparecer la opcion de sumar uno y que haya un peon
      if ((dOponente(jug) == fichaEnCasillero(n,i - aux, j + aux)) && (casilleroVacio(n,i+1,j-1))){
        return true; //salgo porque se que una dama me puede comer
      } else {
        salir3 = true; //lo pongo en verdadero porque por mas que despues aparezca una ficha la dama no puede llegar a mi.
      }
    }
    if ((dimensionesValidas(i-aux)) && (dimensionesValidas(j-aux)) && (!casilleroVacio(n,i-aux,j-aux) && !salir4)){ //si hay una ficha en el medio salvo uqe sea dama no me pueden comer se supone que no va a aparecer la opcion de sumar uno y que haya un peon
      if ((dOponente(jug) == fichaEnCasillero(n,i - aux, j - aux)) && (casilleroVacio(n,i+1,j+1))){
        return true; //salgo porque se que una dama me puede comer
      } else {
        salir4 = true; //lo pongo en verdadero porque por mas que despues aparezca una ficha la dama no puede llegar a mi.
      }
    }
    aux++;
  }
  return false;
}

int evaluarRiesgo(Nodo *t, int i, int j, int jug){ //devuelve el riesgo basado en comparaciones despues de haber realizado el movimiento
  int riesgo = 0;
  if(estoyEnBorde(i,j) || ((fichaAliada(t,i+filaAvance(jug),j+1,jug)) && (fichaAliada(t,i+filaAvance(jug),j-1,jug)))) {//si tengo dos fichas atras una a cada lado entonces 0
    //si puedo comer en el proximo turno.
    riesgo += asignarRiesgoSiPuedoComer(t, i,j, jug);
  } else{
    if ((fichaOponente(t,i+filaAvance(jug),j+1,jug) && casilleroVacio(t,i-filaAvance(jug),j-1))
        || (fichaOponente(t,i+filaAvance(jug),j-1,jug) && casilleroVacio(t,i-filaAvance(jug),j+1))){//si tengo un peon enfrente o una dama y nada que me cubra atras entonces 1
      riesgo += 2;
      if (fichaEnCasillero(t,i,j) == dama(jug)) {
        riesgo += 2;
      }
    }
    if (damaMePuedeComer(t, i, j, jug)) {
      riesgo += 2;
      if (fichaEnCasillero(t,i,j) == dama(jug)) {
        riesgo += 2;
      }
    }
  }

  return riesgo;
}

int evaluarRiesgoInicial(Nodo *t, int i, int j, int jug){ //devuelve el riesgo basado en comparaciones despues de haber realizado el movimiento
  int riesgo = 0;
  if(estoyEnBorde(i,j) || ((fichaAliada(t,i+filaAvance(jug),j+1,jug)) && (fichaAliada(t,i+filaAvance(jug),j-1,jug)))) {//si tengo dos fichas atras una a cada lado entonces 0
    riesgo += 0;
  } else{
    if ((fichaOponente(t,i+filaAvance(jug),j+1,jug) && casilleroVacio(t,i-filaAvance(jug),j-1))
        || (fichaOponente(t,i+filaAvance(jug),j-1,jug) && casilleroVacio(t,i-filaAvance(jug),j+1))){//si tengo un peon enfrente o una dama y nada que me cubra atras entonces 1
      riesgo -= 1;
      if (fichaEnCasillero(t,i,j) == dama(jug)) {
        riesgo -= 2;
      }
    }
    if (damaMePuedeComer(t, i, j, jug)) {
      riesgo -= 1;
      if (fichaEnCasillero(t,i,j) == dama(jug)) {
        riesgo -= 2;
      }
    }
  }

  return riesgo;
}

Array * recursionComiendoDama(Nodo *t, int jugador, int dir, int i, int j){
  bool nomovDerecha, nomovIzquierda;
  int iDestino,jDestino;
  Nodo *nuevo;
  Array *movimientos = crearArray(0);
  nomovDerecha = false;
  nomovIzquierda = false;

  if (dimensionesValidas(i+(2*dir)) && dimensionesValidas(j+2) && dimensionesValidas(i+dir) && dimensionesValidas(j+1) && casilleroVacio(t, i+(2*dir), j+2) && fichaOponente(t, i+dir, j+1, jugador)){
    iDestino = i + (2 * dir);
    jDestino = j + 2;
    nuevo = crearNodo();
    copiarArbolArbol(t, nuevo);
    nuevo->riesgo = t->riesgo;
    nuevo->tablero[iDestino - dir][jDestino - 1] = 1; //lugar donde estaba la ficha
    nuevo->riesgo -= 2; //resto 1 a riesgo porque estaria comiendo una ficha
    if (fichaEnCasillero(t, iDestino - dir, jDestino - 1) == dOponente(jugador)) {
      nuevo->riesgo -= 2; //resto 1 mas a riesgo porque estaria comiendo una dama
    }
    nuevo->tablero[iDestino][jDestino] = t->tablero[i][j]; //coloco mi ficha una despues
    nuevo->tablero[i][j] = 1; //pongo blanco donde estaba mi ficha
    concatArray(movimientos, recursionComiendoDama(nuevo, jugador, dir, iDestino, jDestino));
    free(nuevo);
    nuevo = NULL;
  } else {
    nomovDerecha = true;
  }
  if (dimensionesValidas(i+(2*dir)) && dimensionesValidas(j-2) && casilleroVacio(t, i+(2*dir), j-2) && fichaOponente(t, i+dir, j-1, jugador)){
    iDestino = i + (2 * dir);
    jDestino = j - 2;
    nuevo = crearNodo();
    copiarArbolArbol(t, nuevo);
    nuevo->riesgo = t->riesgo;
    nuevo->tablero[iDestino - dir][jDestino + 1] = 1; //lugar donde estaba la ficha comida
    nuevo->riesgo -= 2;//resto uno a riesgo porque estaria comiendo una ficha
    if (fichaEnCasillero(t, iDestino - dir, jDestino + 1) == dOponente(jugador)) {
      nuevo->riesgo -= 2;//resto uno mas a riesgo porque estaria comiendo una dama
    }
    nuevo->tablero[iDestino][jDestino] = t->tablero[i][j]; //coloco mi ficha una despues
    nuevo->tablero[i][j] = 1; //pongo blanco donde estaba mi ficha
    concatArray(movimientos, recursionComiendoDama(nuevo, jugador, dir, iDestino, jDestino));
    free(nuevo);
    nuevo = NULL;
  } else {
    nomovIzquierda = true;
  }
  if (nomovDerecha && nomovIzquierda) {
    nuevo = crearNodo();
    copiarArbolArbol(t, nuevo);
    insertArray(movimientos, nuevo);
    free(nuevo);
  }
  return movimientos;
}

Array * agregarMovimientosDama(Nodo *n, int i, int j, int jug){//devuelve un arreglo con todos los movimientos posibles para la dama posicionada en i,j
  Nodo *nuevo;
  Array *movimientos = crearArray(0);
  int aux = 1;
  bool salir1, salir2, salir3, salir4;
  salir1 = false;
  salir2 = false;
  salir3 = false;
  salir4 = false;
  while ((aux<TAMANIO) && (!salir1 && !salir2 && !salir3 && !salir4 )){
    if (dimensionesValidas(i+aux) && dimensionesValidas(j+aux) && (casilleroVacio(n,i+aux,j+aux) && !salir1)){
      nuevo = crearNodo();
      copiarArbolArbol(n, nuevo);
      nuevo->riesgo += n->riesgo;
      nuevo->tablero[i+aux][j+aux] = nuevo ->tablero[i][j];
      nuevo->tablero[i][j] = 1;
      nuevo->riesgo += evaluarRiesgo(n, i+aux, j+aux, jug);
      insertArray(movimientos, nuevo);
      free(nuevo);
      nuevo = NULL;
    } else {
      if (dimensionesValidas(i+aux+1) && dimensionesValidas(j+aux+1) && casilleroVacio(n,i+aux+1,j+aux+1) && (fichaOponente(n, i+aux, j+aux, jug) && !salir1)){
        nuevo = crearNodo();
        copiarArbolArbol(n, nuevo);
        nuevo->riesgo += n->riesgo;
        nuevo->tablero[i+aux+1][j+aux+1] = nuevo ->tablero[i][j];
        nuevo ->tablero[i][j] = 1;
        nuevo->tablero[i+aux][j+aux] = 1;
        nuevo->riesgo -= 1;
        if (fichaOponente(n, i+aux, j+aux, jug) == dOponente(jug))
            nuevo->riesgo -= 1;
        nuevo->riesgo += evaluarRiesgo(n, i+aux+1, j+aux+1, jug);
        concatArray(movimientos, recursionComiendoDama(nuevo, jug, 1, i+aux+1, j+aux+1));
        free(nuevo);
        nuevo = NULL;
      }
      salir1 = true;
    }

    if (dimensionesValidas(i+aux) && dimensionesValidas(j-aux) && casilleroVacio(n,i+aux,j-aux) && !salir2){
      nuevo = crearNodo();
      copiarArbolArbol(n, nuevo);
      nuevo->riesgo += n->riesgo;
      nuevo->tablero[i+aux][j-aux] = nuevo ->tablero[i][j];
      nuevo ->tablero[i][j] = 1;
      nuevo->riesgo += evaluarRiesgo(n, i+aux, j-aux, jug);
      insertArray(movimientos, nuevo);
      free(nuevo);
      nuevo = NULL;
    } else {
      if (dimensionesValidas(i+aux+1) && dimensionesValidas(j-aux-1)  && casilleroVacio(n,i+aux+1,j-aux-1) && (fichaOponente(n, i+aux, j-aux, jug) && !salir2)){
        nuevo = crearNodo();
        copiarArbolArbol(n, nuevo);
        nuevo->riesgo += n->riesgo;
        nuevo->tablero[i+aux+1][j-aux-1] = nuevo ->tablero[i][j];
        nuevo ->tablero[i][j] = 1;
        nuevo->tablero[i+aux][j-aux] = 1;
        nuevo->riesgo -= 1;
        if (fichaOponente(n, i+aux, j-aux, jug) == dOponente(jug))
          nuevo->riesgo -= 1;
        nuevo->riesgo += evaluarRiesgo(n, i+aux+1, j-aux-1, jug);
        concatArray(movimientos, recursionComiendoDama(nuevo, jug, 1, i+aux+1, j-aux-1));
        free(nuevo);
        nuevo = NULL;
      }
      salir2 = true;
    }
    if (dimensionesValidas(i-aux) && dimensionesValidas(j+aux) && (casilleroVacio(n,i-aux,j+aux) && !salir3)){
      nuevo = crearNodo();
      copiarArbolArbol(n, nuevo);
      nuevo->riesgo += n->riesgo;
      nuevo->tablero[i-aux][j+aux] = nuevo ->tablero[i][j];
      nuevo ->tablero[i][j] = 1;
      nuevo->riesgo += evaluarRiesgo(n, i-aux, j+aux, jug);
      insertArray(movimientos, nuevo);
      free(nuevo);
      nuevo = NULL;
    }else{
      if (dimensionesValidas(i-aux-1) && dimensionesValidas(j+aux+1)  && casilleroVacio(n,i-aux-1,j+aux+1) && (fichaOponente(n, i-aux, j+aux, jug) && !salir3)){
        nuevo = crearNodo();
        copiarArbolArbol(n, nuevo);
        nuevo->riesgo += n->riesgo;
        nuevo->tablero[i-aux-1][j+aux+1] = nuevo ->tablero[i][j];
        nuevo ->tablero[i][j] = 1;
        nuevo->tablero[i-aux][j+aux] = 1;
        nuevo->riesgo -= 1;
        if (fichaOponente(n, i-aux, j+aux, jug) == dOponente(jug))
            nuevo->riesgo -= 1;
        nuevo->riesgo += evaluarRiesgo(n, i-aux-1, j+aux+1, jug);
        concatArray(movimientos, recursionComiendoDama(nuevo, jug, -1, i-aux-1, j+aux+1));
        free(nuevo);
        nuevo = NULL;
      }
      salir3 = true;
    }
    if (dimensionesValidas(i-aux) && dimensionesValidas(j-aux) && (casilleroVacio(n,i-aux,j-aux) && !salir4)){
      nuevo = crearNodo();
      copiarArbolArbol(n, nuevo);
      nuevo->riesgo += n->riesgo;
      nuevo->tablero[i-aux][j-aux] = nuevo ->tablero[i][j];
      nuevo ->tablero[i][j] = 1;
      nuevo->riesgo += evaluarRiesgo(n, i-aux, j-aux, jug);
      insertArray(movimientos, nuevo);
      free(nuevo);
      nuevo = NULL;
    } else {
      if (dimensionesValidas(i-aux-1) && dimensionesValidas(j-aux-1)  && (casilleroVacio(n,i-aux-1,j-aux-1) && fichaOponente(n, i-aux, j-aux, jug) && !salir4)){
        nuevo = crearNodo();
        copiarArbolArbol(n, nuevo);
        nuevo->riesgo += n->riesgo;
        nuevo->tablero[i-aux-1][j-aux-1] = nuevo ->tablero[i][j];
        nuevo ->tablero[i][j] = 1;
        nuevo->tablero[i-aux][j-aux] = 1;
        nuevo->riesgo -= 1;
        if (fichaOponente(n, i-aux, j-aux, jug) == dOponente(jug))
            nuevo->riesgo -= 1;
        nuevo->riesgo += evaluarRiesgo(n, i-aux-1, j-aux-1, jug);
        concatArray(movimientos, recursionComiendoDama(nuevo, jug, -1, i-aux-1, j-aux-1));
        free(nuevo);
        nuevo = NULL;
      }
      salir4 = true;
    }
    aux++;
  }
  return movimientos;
}

Array* recursionComiendo(Nodo *t, int jugador, int i, int j) {//i es para filas y j para columnas, sory reutilice un toque de codigo paja cambiarlo
  bool nomovDerecha, nomovIzquierda;
  int iDestino,jDestino;
  Nodo *nuevo;
  Array *movimientos = crearArray(0);
  nomovDerecha = false;
  nomovIzquierda = false;

  if (dimensionesValidas(i+(2*filaAvance(jugador))) && dimensionesValidas(j+2) && dimensionesValidas(i+filaAvance(jugador)) && dimensionesValidas(j+1) && casilleroVacio(t, i+(2*filaAvance(jugador)), j+2) && fichaOponente(t, i+filaAvance(jugador), j+1, jugador)){
    iDestino = i + (2 * filaAvance(jugador));
    jDestino = j + 2;
    nuevo = crearNodo();
    copiarArbolArbol(t, nuevo);
    nuevo->riesgo = t->riesgo;
    nuevo->tablero[iDestino - filaAvance(jugador)][jDestino - 1] = 1; //lugar donde estaba la ficha
    nuevo->riesgo -= 2; //resto 1 a riesgo porque estaria comiendo una ficha
    if (fichaEnCasillero(t, iDestino - filaAvance(jugador), jDestino - 1) == dOponente(jugador)) {
      nuevo->riesgo -= 2; //resto 1 mas a riesgo porque estaria comiendo una dama
    }
    if (iDestino == filaObjetivo(jugador)){
      nuevo->riesgo -= 2; //resto riesgo porque me converti en dama
      nuevo->tablero[iDestino][jDestino] = t->tablero[i][j] + 1;
    } else {
      nuevo->tablero[iDestino][jDestino] = t->tablero[i][j]; //coloco mi ficha una despues
    }
    nuevo->tablero[i][j] = 1; //pongo blanco donde estaba mi ficha
    concatArray(movimientos, recursionComiendo(nuevo, jugador, iDestino, jDestino));
    free(nuevo);
    nuevo = NULL;
  } else {
    nomovDerecha = true;
  }
  if (dimensionesValidas(i+(2*filaAvance(jugador))) && dimensionesValidas(j-2) && casilleroVacio(t, i+(2*filaAvance(jugador)), j-2) && fichaOponente(t, i+filaAvance(jugador), j-1, jugador)){
    iDestino = i + (2 * filaAvance(jugador));
    jDestino = j - 2;
    nuevo = crearNodo();
    copiarArbolArbol(t, nuevo);
    nuevo->riesgo = t->riesgo;
    nuevo->tablero[iDestino - filaAvance(jugador)][jDestino + 1] = 1; //lugar donde estaba la ficha comida
    nuevo->riesgo -= 2;//resto uno a riesgo porque estaria comiendo una ficha
    if (fichaEnCasillero(t, iDestino - filaAvance(jugador), jDestino + 1) == dOponente(jugador)) {
      nuevo->riesgo -= 2;//resto uno mas a riesgo porque estaria comiendo una dama
    }
    if (iDestino == filaObjetivo(jugador)){
      nuevo->riesgo -= 2; //resto riesgo porque me converti en dama
      nuevo->tablero[iDestino][jDestino] = t->tablero[i][j] + 1;
    } else {
      nuevo->tablero[iDestino][jDestino] = t->tablero[i][j]; //coloco mi ficha una despues
    }
    nuevo->tablero[i][j] = 1; //pongo blanco donde estaba mi ficha
    concatArray(movimientos, recursionComiendo(nuevo, jugador, iDestino, jDestino));
    free(nuevo);
    nuevo = NULL;
  } else {
    nomovIzquierda = true;
  }
  if (nomovDerecha && nomovIzquierda) {
    nuevo = crearNodo();
    copiarArbolArbol(t, nuevo);
    insertArray(movimientos, nuevo);
    free(nuevo);
  }
  return movimientos;
}

Array* arbolMovimientos(Tablero *t, int jugador, int i, int j) {
  //generar un arbol de movimientos posibles a partir de este casillero; jugador se pasa para saber la direccion hacia donde jugar;
  Nodo *nuevo;
  Nodo *naux = crearNodo();
  int iDestino, jDestino;
  Array *movimientos = crearArray(0);
  copiarTableroArbol(t, naux);
  naux->riesgo += evaluarRiesgoInicial(naux, i, j, jugador);

  if (fichaEnCasillero(naux, i, j) == peon(jugador)) {
    if (dimensionesValidas(i+filaAvance(jugador)) && dimensionesValidas(j+1) && casilleroVacio(naux, i+filaAvance(jugador), j+1)) {
      iDestino = i + filaAvance(jugador);
      jDestino = j + 1;
      nuevo = crearNodo();
      copiarTableroArbol(t, nuevo);
      nuevo->riesgo += naux->riesgo;
      nuevo->tablero[iDestino][jDestino] = t->matriz[i][j];
      nuevo->tablero[i][j] = 1;
      if (iDestino == filaObjetivo(jugador)) { //llegue al final, me convierto en dama
        convertirADama(nuevo, iDestino, jDestino);
        nuevo->riesgo -= 1; //resto riesgo porque me converti en dama
      }
      nuevo->riesgo += evaluarRiesgo(nuevo, iDestino, jDestino, jugador);
      insertArray(movimientos, nuevo);
      free(nuevo);
      nuevo = NULL;
    } else if (dimensionesValidas(i+(2*filaAvance(jugador))) && dimensionesValidas(j+2)
        && casilleroVacio(naux, i+(2*filaAvance(jugador)), j+2)
        && fichaOponente(naux, i+filaAvance(jugador), j+1, jugador)) {
      iDestino = i + (2 * filaAvance(jugador));
      jDestino = j + 2;
      nuevo = crearNodo();
      copiarTableroArbol(t,nuevo);
      nuevo->riesgo += naux->riesgo;
      nuevo->riesgo -= 1;//por comer
      if (fichaEnCasillero(naux, iDestino - filaAvance(jugador), jDestino - 1) == dOponente(jugador)) {
        nuevo->riesgo -= 1;//por comer una dama
      }
      nuevo->tablero[iDestino - filaAvance(jugador)][jDestino - 1] = 1; //lugar donde estaba la ficha
      if (iDestino == filaObjetivo(jugador)) { //llegue al final, me convierto en dama
        nuevo->tablero[iDestino][jDestino] = t->matriz[i][j] + 1; //coloco mi ficha una despues sumandole una para convertir en dama
        nuevo->riesgo -= 1; //por ser dama
      } else {
        nuevo->tablero[iDestino][jDestino] = t->matriz[i][j]; //coloco mi ficha una despues
      }
      nuevo->tablero[i][j] = 1; //pongo blanco donde estaba mi ficha
      nuevo->riesgo += evaluarRiesgo(nuevo, iDestino, jDestino, jugador);
      concatArray(movimientos, recursionComiendo(nuevo, jugador, iDestino, jDestino));
      free(nuevo);
      nuevo = NULL;
    }
    //moviendo en diagonal hacia la izquierda
    if (dimensionesValidas(i+filaAvance(jugador)) && dimensionesValidas(j-1) && casilleroVacio(naux, i+filaAvance(jugador),j-1)){ //Casillero esquina de abajo a la derecha
      iDestino = i+filaAvance(jugador);
      jDestino = j - 1;
      nuevo = crearNodo();
      copiarTableroArbol(t, nuevo);
      nuevo->riesgo += naux->riesgo;
      if (iDestino == filaObjetivo(jugador)) { //llegue al final, me convierto en dama
        nuevo->tablero[iDestino][jDestino] = t->matriz[i][j] + 1; //sumo uno para convertir en dama
        nuevo->riesgo -= 1; //por ser dama
      } else {
        nuevo->tablero[iDestino][jDestino] = t->matriz[i][j];
      }
      nuevo->tablero[i][j] = 1;
      nuevo->riesgo += evaluarRiesgo(nuevo, iDestino, jDestino, jugador);
      insertArray(movimientos, nuevo);
      free(nuevo);
      nuevo = NULL;
    } else {
      if (dimensionesValidas(j-2) && dimensionesValidas(i+(2*filaAvance(jugador))) && casilleroVacio(naux, i+(2*filaAvance(jugador)), j-2) && fichaOponente(naux, i+filaAvance(jugador), j-1, jugador)){
        iDestino = i + (2 * filaAvance(jugador));
        jDestino = j - 2;
        nuevo = crearNodo();
        copiarTableroArbol(t,nuevo);
        nuevo->riesgo += naux->riesgo;
        nuevo->riesgo -= 1; //por comer
        if (fichaEnCasillero(naux, iDestino - filaAvance(jugador), jDestino + 1) == dOponente(jugador)) {
          nuevo->riesgo -= 1;//por comer una dama
        }
        nuevo->tablero[iDestino - filaAvance(jugador)][jDestino + 1] = 1; //lugar donde estaba la ficha comida
        if (iDestino == filaObjetivo(jugador)) { //llegue al final, me convierto en dama
          nuevo->tablero[iDestino][jDestino] = t->matriz[i][j] + 1; //coloco mi ficha una despues sumandole una para convertir en dama
          nuevo->riesgo -= 1;//por ser dama
        } else {
          nuevo->tablero[iDestino][jDestino] = t->matriz[i][j]; //coloco mi ficha una despues
        }
        nuevo->tablero[i][j] = 1; //pongo blanco donde estaba mi ficha
        nuevo->riesgo += evaluarRiesgo(nuevo, iDestino, jDestino, jugador);
        concatArray(movimientos, recursionComiendo(nuevo, jugador, iDestino, jDestino));
        free(nuevo);
        nuevo = NULL;
      }
    }
  //Seria una dama con la ficha que estamos tratando
  } else if (fichaEnCasillero(naux, i, j) == dama(jugador)) {
    concatArray(movimientos, agregarMovimientosDama(naux, i, j, jugador));
  }
  free(naux);
  naux = NULL;
  return movimientos;
}

int mejorCamino(Nodo *n, int nivel) {
  int menorRiesgo, riesgoAux, i;
  if (n->hijos.used == 0) {
    return n->riesgo;
  }
  if (nivel % 2 == 0) {
    menorRiesgo = n->riesgo + mejorCamino(&(n->hijos.array[0]), nivel+1);
    for (i = 1; i < n->hijos.used; i++) {
      riesgoAux = n->riesgo + mejorCamino(&(n->hijos.array[i]), nivel+1);
      if (riesgoAux < menorRiesgo) {
        menorRiesgo = riesgoAux;
      }
    }
  } else {
    menorRiesgo = n->riesgo - mejorCamino(&(n->hijos.array[0]), nivel+1);
    for (i = 1; i < n->hijos.used; i++) {
      riesgoAux = n->riesgo - mejorCamino(&(n->hijos.array[i]), nivel+1);
      if (riesgoAux > menorRiesgo) {
        menorRiesgo = riesgoAux;
      }
    }
  }
  return menorRiesgo;
}

Nodo* mejorMovimiento(Array *a) {
  int i, menorRiesgo, riesgoAux, r;
  Nodo* naux = crearNodo();
  Nodo* mejor = crearNodo();
  Array *array = crearArray(0);
  if (a->used == 0) {
    return NULL;
  }
  menorRiesgo = mejorCamino(&(a->array[0]), 0);
  copiarArbolArbol(&(a->array[0]), naux);
  insertArray(array, naux);
  free(naux);
  naux = NULL;
  naux = crearNodo();
  for (i = 1; i < a->used; i++) {
    riesgoAux = mejorCamino(&(a->array[i]),0 );
    if (riesgoAux == menorRiesgo) {
      copiarArbolArbol(&(a->array[i]), naux);
      insertArray(array, naux);
      free(naux);
      naux = NULL;
      naux = crearNodo();
    } else if (riesgoAux < menorRiesgo) {
      if (array->used > 0) {
        freeArray(array);
        free(array);
        array = NULL;
        array = crearArray(0);
      }
      menorRiesgo = riesgoAux;
      copiarArbolArbol(&(a->array[i]), naux);
      insertArray(array, naux);
      free(naux);
      naux = NULL;
      naux = crearNodo();
    }
  }
  srand(time(NULL));
  r = rand() % (array->used);
  copiarArbolArbol(&(array->array[r]), mejor);
  freeArray(array);
  free(array);
  free(naux);
  return mejor;
}

Array* generarMovimientos(Nodo *n, int jugador, int nivel) {
  int i, j;
  Tablero *taux = crearTableroVacio();
  //arreglo de arboles, cada ficha que tengo me va a dar un arbol de movimientos
  Array *arboles = crearArray(0);
  if (nivel == NIVELES) {
    free(taux);
    return arboles;
  }
  for (i = 0; i < TAMANIO; i++) {
    for (j = 0; j < TAMANIO; j++) {
      if (n->tablero[i][j] == peon(jugador) || n->tablero[i][j] == dama(jugador)) {
        copiarArbolTablero(n, taux);
        concatArray(arboles, arbolMovimientos(taux, jugador, i, j));
      }
    }
  }
  for (i = 0; i < arboles->used; i++) {
    concatArray(&(arboles->array[i].hijos), generarMovimientos(&(arboles->array[i]), jOponente(jugador), nivel + 1));
  }
  free(taux);
  return arboles;
}

Tablero* elegirMovimiento(Tablero *t, int jugador) {
  Tablero *taux = crearTableroVacio();
  Nodo *naux = crearNodo();
  copiarTableroArbol(t, naux);
  //arreglo de arboles, cada ficha que tengo me va a dar un arbol de movimientos
  Array *arboles = generarMovimientos(naux, jugador, 0);

  eliminarNodo(naux);
  free(naux);
  naux = mejorMovimiento(arboles);
  if (naux == NULL) {
    copiarTablero(t, taux);
    return taux;
  }
  copiarArbolTablero(naux, taux);
  freeArray(arboles);
  free(arboles);
  eliminarNodo(naux);
  free(naux);
  return taux;
}

void jugar1(Tablero *t, Tablero *tj) {
  Tablero *taux = elegirMovimiento(t,1);
  copiarTablero(taux, tj);
  free(taux);
}

void jugar2(Tablero *t, Tablero *tj) {
  Tablero *taux = elegirMovimiento(t,2);
  copiarTablero(taux, tj);
  free(taux);
}
