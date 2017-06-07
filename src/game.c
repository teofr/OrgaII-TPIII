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

void game_init(){

  ///CLOCK
  state=0;
  states="|/-\\";


  ///JUGADORES
  JUGADOR[0].fila = 43;
  JUGADOR[0].col = 0;
  JUGADOR[0].attr.c = 'M';
  JUGADOR[0].attr.a = C_BG_RED | C_FG_WHITE;

  JUGADOR[1].fila = 0;
  JUGADOR[1].col = 79;
  JUGADOR[1].attr.c = 'M';
  JUGADOR[1].attr.a = C_BG_BLUE | C_FG_WHITE;

  int i;
  for(i=0; i<8; i++){
    JUGADOR[0].zombis[i]=crearZombie(IDLE);
    JUGADOR[1].zombis[i]=crearZombie(IDLE);
  }

  print_jug(0);
  print_jug(1);

}


zombie crearZombie(clase tipo){
  zombie z;
  z.cl=tipo;
  z.fila=0;
  z.col=0;
  z.cr3=0;

  return z;
}

void print_jug(unsigned int j){
  jug curr = JUGADOR[j];
  print_ca(curr.attr, curr.col, curr.fila + 1);
  curr.attr.c = 0x20;
  print_ca(curr.attr, curr.col, ((curr.fila + 1) % 44) +1);
  print_ca(curr.attr, curr.col, ((curr.fila +43) % 44) +1 );
}


unsigned int pos2mem(unsigned int x, unsigned int y){
  return ((y * SIZE_W + x) << 12) + MAP_INIT;
}

void mem2pos(unsigned int mem, unsigned int* x, unsigned int* y){
  *x = ((mem - MAP_INIT) >> 12) % SIZE_W;
  *y = ((mem - MAP_INIT) >> 12) / SIZE_W;
}

void game_clock(){
  state++;
  state=state%diffStates;
  ca temp;
  temp.c=states[state];
  temp.a=C_BG_BLACK | C_FG_WHITE;
  print_ca(temp, 79, 49);
}
