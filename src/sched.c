/* ** por compatibilidad se omiten tildes **
================================================================================
 TRABAJO PRACTICO 3 - System Programming - ORGANIZACION DE COMPUTADOR II - FCEN
================================================================================
  definicion de funciones del scheduler
*/

/*
Si un jugador no tiene tareas, corre idle o pasa al otro jug



*/
#include "sched.h"
#include "tss.h"

typedef struct node_t{
  unsigned char avl;
  unsigned short offset;
} node;

typedef struct cola_t {
  unsigned int next;
  node queue[CANT_ZOMBIS];
} cola;

typedef struct sched_t{
  unsigned int curr;
  cola colas[2];
}sched;

sched this;

unsigned int nextAVL (unsigned int j){
  unsigned int curr=0;
  while (curr<CANT_ZOMBIS){
    if (this.colas[j].queue[curr].avl){
      return curr;
    }
    curr++;
  }
  return curr;
}

void avanzar(unsigned char repeat){
  this.curr=(this.curr+1)%2;
  unsigned int size=0;
  unsigned int curr=this.curr;
  unsigned int next=(this.colas[curr].next+1)%CANT_ZOMBIS;
  while (size<=CANT_ZOMBIS && this.colas[curr].queue[next].avl){
    next=(next+1)%CANT_ZOMBIS;
    size++;
  }
  if(size==CANT_ZOMBIS+1 && repeat){
    avanzar(0);
  }
  this.colas[curr].next=next;
}

unsigned short sched_proximo_indice() {
  avanzar(1);
  return this.colas[this.curr].queue[this.colas[this.curr].next].offset;
}
