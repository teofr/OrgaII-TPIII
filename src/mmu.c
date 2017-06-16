/* ** por compatibilidad se omiten tildes **
================================================================================
 TRABAJO PRACTICO 3 - System Programming - ORGANIZACION DE COMPUTADOR II - FCEN
================================================================================
  definicion de funciones del manejador de memoria
*/

#include "mmu.h"

unsigned int last_libre;

void mmu_inicializar() {
  last_libre = INIT_LIBRE;
}

unsigned int mmu_dameMem(){
  last_libre += PAG_SIZE;
  return last_libre - PAG_SIZE;
}

void mmu_mappear_pagina(unsigned int virtual, unsigned int dir_pd, unsigned int fisica, unsigned int permisos){

  pag_entry* dir = (pag_entry*) dir_pd;

  if (! dir[DIR_IDX(virtual)].present){
    // Asumo que la memoria viene en 0s
    dir[DIR_IDX(virtual)].addr = mmu_dameMem() >> 12;
    dir[DIR_IDX(virtual)].present = 1;
    dir[DIR_IDX(virtual)].supervisor = permisos;
  }

  pag_entry* tbl = (pag_entry*) (dir[DIR_IDX(virtual)].addr << 12);

  tbl[TBL_IDX(virtual)].present = 1;
  tbl[TBL_IDX(virtual)].supervisor = permisos;
  tbl[TBL_IDX(virtual)].addr = fisica >> 12;

  tlbflush();

}

void mmu_desmappear_pagina(unsigned int virtual, unsigned int dir_pd){
  pag_entry* dir = (pag_entry*) dir_pd;

  pag_entry* tbl = (pag_entry*) (dir[DIR_IDX(virtual)].addr << 12);
  tbl[TBL_IDX(virtual)].present = 0;

}

unsigned int mmu_inicializar_dir_zombi(unsigned int jug, unsigned int z){
  unsigned int dir = mmu_dameMem();
  //pag_entry* tblid=(pag_entry*) mmu_dameMem();

  int i;
  for (i = 0; i < PAG_COUNT; i++){
    mmu_mappear_pagina(i * PAG_SIZE, dir, i * PAG_SIZE, 1);
  }

  int cambioCol []={0, 1, 1, 1, 0, 0, -1, -1 ,-1};
  int cambioFil []={0, 0, 1, -1, 1, -1, 0, -1 ,1};
  //TODO:Espear para JUGADOR 1

  for (i = 0; i < 9; i++){
    mmu_mappear_pagina(0x08000000 + 0x1000 * i, dir,
          pos2mem((int) (JUGADOR[jug].col + 2 - 4 * jug) + cambioCol[i],
                 ((int) JUGADOR[jug].fila + cambioFil[i] + 44) % 44), 0 );
  }

  mmu_mappear_pagina(0x08000000, PAG_DIR, pos2mem(JUGADOR[jug].col + 2 - 4 * jug, JUGADOR[jug].fila), 1);

  char* toCopy = (char*) 0x08000000;
  char* from;
  
  if (JUGADOR[jug].zombis[z].cl){
    from = (char*) ((unsigned int)JUGADOR[jug].zombis[z].cl + 0x3000 * jug);
  }else{
    from = (char*) 0x16000;
  }

  for (i = 0; i < PAG_SIZE; i++){
    *(toCopy+i) = *(from + i);
  }

  mmu_desmappear_pagina(0x08000000, PAG_DIR);
  return dir;
}
