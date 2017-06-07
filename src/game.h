/* ** por compatibilidad se omiten tildes **
================================================================================
 TRABAJO PRACTICO 3 - System Programming - ORGANIZACION DE COMPUTADOR II - FCEN
================================================================================
*/

#ifndef __GAME_H__
#define __GAME_H__

#include "defines.h"
#include "screen.h"
#include "mmu.h"
// Si le dejo esto desde mmu no puedo agarrar las declaraciones de aca

typedef enum direccion_e { IZQ = 0xAAA, DER = 0x441, ADE = 0x83D, ATR = 0x732 } direccion;


///ZOMBIES
typedef enum clase_e { GUERRERO=0x10000, MAGO=0x11000, CLERIGO=0x12000, IDLE=0} clase;

typedef struct zombie_s{
  unsigned int cr3;
  clase cl;
  unsigned int fila;
  unsigned int col;
}__attribute__((__packed__, aligned (8))) zombie;

zombie crearZombie(clase tipo);

///JUGADORES
typedef struct jug_t {
  unsigned int fila;
  unsigned int col;
  ca attr;
  zombie zombis[8];
}__attribute__((__packed__, aligned (8))) jug;

jug JUGADOR[2];


///CLOCK
#define diffStates 4
char* states;
unsigned int state;

void game_clock();

void game_init();

void game_jugador_mover(unsigned int jugador, unsigned int value);

void game_lanzar_zombi(unsigned int jugador);

void game_move_current_zombi(direccion dir);

unsigned int pos2mem(unsigned int x, unsigned int y);

void mem2pos(unsigned int mem, unsigned int *x, unsigned int *y);

void print_jug(unsigned int j);


#endif  /* !__GAME_H__ */
