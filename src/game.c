/* ** por compatibilidad se omiten tildes **
================================================================================
 TRABAJO PRACTICO 3 - System Programming - ORGANIZACION DE COMPUTADOR II - FCEN
================================================================================
*/

#include "game.h"

void game_jugador_mover(unsigned int jugador, unsigned int value) {
}
void game_lanzar_zombi(unsigned int jugador) {
}
void game_move_current_zombi(direccion dir) {
}



unsigned int pos2mem(unsigned int x, unsigned int y){
  return (y * SIZE_W + x) << 12;
}

void mem2pos(unsigned int mem, unsigned int* x, unsigned int* y){
  *x = (mem >> 12) % SIZE_W;
  *y = (mem >> 12) / SIZE_W;
}
