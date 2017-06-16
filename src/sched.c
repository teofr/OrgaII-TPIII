/* ** por compatibilidad se omiten tildes **
================================================================================
 TRABAJO PRACTICO 3 - System Programming - ORGANIZACION DE COMPUTADOR II - FCEN
================================================================================
  definicion de funciones del scheduler
*/

/*
Si un jugador no tiene tareas, corre idle o pasa al otro jug
Dato de color: podes llegar a perder el turno si agregas un zombi despues de que el scheduler recorrio mi lista de zombies.


*/

#include "sched.h"

typedef struct node_t{
  unsigned char avl;
  unsigned short offset; //selector GDT
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

unsigned char avanzar(unsigned char repeat){
  this.curr=(this.curr+1)%2;
  unsigned int size=0;
  unsigned int curr=this.curr;
  unsigned int next=(this.colas[curr].next+1)%CANT_ZOMBIS;

  while (size<=CANT_ZOMBIS && this.colas[curr].queue[next].avl){
    next=(next+1)%CANT_ZOMBIS;
    size++;
  }
  if(size==CANT_ZOMBIS+1 && repeat){
    return avanzar(0);
  }else if(size==CANT_ZOMBIS+1){
    return 0;
  }

  this.colas[curr].next=next;
  return 1;
}

unsigned short sched_proximo_indice() {
  if (avanzar(1)){
    print_int(this.colas[this.curr].queue[this.colas[this.curr].next].offset, 20, 20, C_BG_BLACK | C_FG_WHITE);
    return this.colas[this.curr].queue[this.colas[this.curr].next].offset;
  }else{
    return 0;
  }
}

void sched_init(){
  this.curr=0;

  int jug;
  for(jug=0; jug<2; jug++){
    this.colas[jug].next=CANT_ZOMBIS;
    int i;

    for(i=0; i<CANT_ZOMBIS; i++){
      unsigned int gdt_idx=GDT_IDX_TSS_ZOMBIS+jug*CANT_ZOMBIS+i;

      this.colas[jug].queue[i].offset=gdt_idx<<3;
      this.colas[jug].queue[i].avl=1;

      init_tss_desc(gdt_idx, (unsigned int) &(tss_zombis[jug][i]), (unsigned int) sizeof(tss_zombis[jug][i]), 3);

    }
  }
}

unsigned int sched_insert_task(unsigned int jug){
  unsigned int where=nextAVL(jug);

  if (where<CANT_ZOMBIS){
    tss_new_task(jug, where);

    this.colas[jug].queue[where].avl=0;
  }
  return where;
}
