/* ** por compatibilidad se omiten tildes **
================================================================================
 TRABAJO PRACTICO 3 - System Programming - ORGANIZACION DE COMPUTADOR II - FCEN
================================================================================
*/

#include "game.h"



void game_keyboard_parser(char key){
  action temp;

  //if (key>0x80) return;

  //jug=0 es el jugador A
  temp.jug = key==KEY_I
          || key==KEY_J
          || key==KEY_K
          || key==KEY_L
          || key==KEY_RS;


  switch (key) {
    case KEY_W:
    case KEY_I:
      temp.acc=ARRIBA;
      break;
    case KEY_A:
    case KEY_J:
      temp.acc=CAMBIAR_L;
      break;
    case KEY_S:
    case KEY_K:
      temp.acc=ABAJO;
      break;
    case KEY_D:
    case KEY_L:
      temp.acc=CAMBIAR_R;
      break;
    case KEY_LS:
    case KEY_RS:
      temp.acc=LANZAR;
      break;
    default:
      temp.acc=NOTHING;
      break;
  }

  game_keyboard_handler(temp);

}

void game_keyboard_handler(action a){
  switch (a.acc) {
    case ARRIBA:
      game_jugador_mover(a.jug, 1);
      break;
    case ABAJO:
      game_jugador_mover(a.jug,  -1);
      break;
    case LANZAR:
      game_lanzar_zombi(a.jug);
      break;
    case CAMBIAR_R:
      game_shift_zombie(a.jug, 1);
      break;
    case CAMBIAR_L:
      game_shift_zombie(a.jug, -1);
      break;
    default:
      break;

  }
}

void game_jugador_mover(unsigned int jugador, int value) {
  int prev=(int) JUGADOR[jugador].fila;
  prev=(prev-value+44)%44;
  JUGADOR[jugador].fila=(unsigned int) prev;

  print_jug(jugador);

}

void game_lanzar_zombi(unsigned int jugador) {
  if (!JUGADOR[jugador].zRestantes) return;
  breakpoint();
  unsigned int where = sched_insert_task(jugador);

  if (where<CANT_ZOMBIS){
    JUGADOR[jugador].zRestantes--;
    JUGADOR[jugador].zombis[where].cl=JUGADOR[jugador].currZ;
    JUGADOR[jugador].zombis[where].fila=JUGADOR[jugador].fila;
    unsigned int col = jugador ? VIDEO_COLS-3 : 2;
    JUGADOR[jugador].zombis[where].col = col;
    game_move_zombie(jugador, where, col, JUGADOR[jugador].fila);
  }

}



void game_shift_zombie(unsigned int jugador, int a){
  int prev=(int)JUGADOR[jugador].currZ;
  prev=(prev+a+3)%3;
  JUGADOR[jugador].currZ=(unsigned int) prev;
  print_jug(jugador);
}

void game_move_zombie(unsigned int jug, unsigned int z, unsigned int col, unsigned int fila){
  ca temp;
  temp.c='X';
  temp.a= C_BG_GREEN | C_FG_WHITE;
  print_ca(temp, JUGADOR[jug].zombis[z].col, JUGADOR[jug].zombis[z].fila);
  JUGADOR[jug].zombis[z].col=col;
  JUGADOR[jug].zombis[z].fila=fila;
  temp.c = tiposZombie[JUGADOR[jug].zombis[z].cl];
  temp.a = C_FG_WHITE | (jug ? C_BG_RED : C_BG_BLUE);
  print_ca(temp, col, fila);

  upd_jugs();
}

void game_move_current_zombi(direccion dir) {
}

void game_sumar_punto (unsigned int j){

}

void game_init(){

  ///CLOCK
  state=0;
  states="|/-\\";

  //ARRAY TIPOS DE ZOMBIE
  tiposZombie = "GMC";

  ///JUGADORES
  JUGADOR[0].fila = 43;
  JUGADOR[0].col = 0;
  JUGADOR[0].currZ = 0;
  JUGADOR[0].zRestantes=20;
  JUGADOR[0].puntos=0;

  JUGADOR[1].fila = 0;
  JUGADOR[1].col = 79;
  JUGADOR[1].currZ = 0;
  JUGADOR[1].zRestantes=20;
  JUGADOR[1].puntos=0;

  int i;
  for(i=0; i<8; i++){
    JUGADOR[0].zombis[i]=crearZombie(IDLE);
    JUGADOR[1].zombis[i]=crearZombie(IDLE);
  }

  print_jug(0);
  print_jug(1);

  upd_jugs();

}

void avanzar_reloj(){
  state++;
  state=state%diffStates;
  ca temp;
  temp.c=states[state];
  temp.a=C_BG_BLACK | C_FG_WHITE;
  print_ca(temp, 79, 49);
}

zombie crearZombie(clase tipo){
  zombie z;
  z.cl=tipo;
  z.fila=0;
  z.col=0;
  //z.cr3=0;

  return z;
}

void print_Z(unsigned int a){
  //ca temp;

}
void print_jug(unsigned int j){
  jug curr = JUGADOR[j];
  ca temp;
  temp.c=(unsigned char)tiposZombie[curr.currZ];
  temp.a= ((1-j)*C_BG_RED) | (j*C_BG_BLUE) | C_FG_WHITE;
  print_ca(temp, curr.col, curr.fila + 1);
  temp.c = 0x20;
  print_ca(temp, curr.col, ((curr.fila + 1) % 44) +1);
  print_ca(temp, curr.col, ((curr.fila +43) % 44) +1 );
}

void upd_jugs(){
  print_int(JUGADOR[0].puntos, SCORE_A_COL, SCORE_RESTANTES_FIL, C_BG_RED | C_FG_WHITE);
  print_int(JUGADOR[1].puntos, SCORE_B_COL, SCORE_RESTANTES_FIL, C_BG_BLUE | C_FG_WHITE);

  //Printea cantidad de zombies disponibles de cada jugador
  print_int(JUGADOR[0].zRestantes, RESTANTES_A_COL, SCORE_RESTANTES_FIL, C_BG_RED | C_FG_WHITE);
  print_int(JUGADOR[1].zRestantes, RESTANTES_B_COL, SCORE_RESTANTES_FIL, C_BG_BLUE | C_FG_WHITE);


}


unsigned int pos2mem(unsigned int x, unsigned int y){
  return ((y * SIZE_W + x) << 12) + MAP_INIT;
}

void mem2pos(unsigned int mem, unsigned int* x, unsigned int* y){
  *x = ((mem - MAP_INIT) >> 12) % SIZE_W;
  *y = ((mem - MAP_INIT) >> 12) / SIZE_W;
}
