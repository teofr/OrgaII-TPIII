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
#include "rutinasc.h"
#include "sched.h"
#include "i386.h"

// Si le dejo esto desde mmu no puedo agarrar las declaraciones de aca

typedef enum direccion_e { IZQ = 0xAAA, DER = 0x441, ADE = 0x83D, ATR = 0x732 } direccion;

typedef enum action_e  { ARRIBA, ABAJO, LANZAR, CAMBIAR_L, CAMBIAR_R, NOTHING } action_enum;

typedef struct action_t{
  unsigned int jug;
  action_enum acc;
}__attribute__((__packed__, aligned (8))) action;

///ZOMBIES
//TODO: ver de cambiar esta abominacion
typedef enum clase_e { GUERRERO = 0x10000, MAGO = 0x11000, CLERIGO = 0x12000, IDLE = 0} clase;

typedef enum claseLinda_e { GUERRERO_L, MAGO_L, CLERIGO_L, CLASE_SIZE} claseLinda;

#define DIFFZOMBIES (unsigned int ) CLASE_SIZE;

typedef struct zombie_s {
  claseLinda cl;
  unsigned int fila;
  unsigned int col;
}__attribute__((__packed__, aligned (8))) zombie;

zombie crearZombie(clase tipo);

char* tiposZombie;

///JUGADORES
typedef struct jug_t {
  unsigned int fila;
  unsigned int col;
  claseLinda currZ;
  unsigned int puntos;
  unsigned int zRestantes;
  zombie zombis[8];
}__attribute__((__packed__, aligned (8))) jug;

jug JUGADOR[2];

/// Keys

#define KEY_W 0x11
#define KEY_A 0x1E
#define KEY_S 0x1F
#define KEY_D 0x20
#define KEY_LS 0x2A
#define KEY_I 0x17
#define KEY_J 0x24
#define KEY_K 0x25
#define KEY_L 0x26
#define KEY_RS 0x36

///CLOCK

void game_keyboard_parser(char key);

void game_keyboard_handler(action a);

void game_sumar_punto (unsigned int j);

void game_init();

void avanzar_reloj();

void game_jugador_mover(unsigned int jugador,  int value);

void game_lanzar_zombi(unsigned int jugador);

void game_shift_zombie(unsigned int jugador, int a);

void game_move_current_zombi(direccion dir);

void game_move_zombie(unsigned int jug, unsigned int z, unsigned int col, unsigned int fila);

unsigned int pos2mem(unsigned int x, unsigned int y);

void mem2pos(unsigned int mem, unsigned int *x, unsigned int *y);

void print_jug(unsigned int j);

void upd_jugs();


#endif  /* !__GAME_H__ */
