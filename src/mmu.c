/* ** por compatibilidad se omiten tildes **
================================================================================
 TRABAJO PRACTICO 3 - System Programming - ORGANIZACION DE COMPUTADOR II - FCEN
================================================================================
  definicion de funciones del manejador de memoria
*/

#include "mmu.h"

unsigned int last_libre;

void mmu_inicializar() {
  last_libre=INIT_LIBRE;
}

unsigned int mmu_dameMem(){
  last_libre+=PAG_SIZE;
  return last_libre-PAG_SIZE;
}

void mmu_mappear_pagina(unsigned int virtual, unsigned int dir_pd, unsigned int fisica, unsigned int permisos){
  pag_entry *dir = (pag_entry*) dir_pd;

  if (! dir[DIR_IDX(virtual)].present){
    dir[DIR_IDX(virtual)].addr=mmu_dameMem()>>12;
    // Asumo que la memoria viene en 0s
    dir[DIR_IDX(virtual)].present=1;
    dir[DIR_IDX(virtual)].supervisor=permisos;



  }

  pag_entry *tbl=(pag_entry*) (dir[DIR_IDX(virtual)].addr<<12);

  tbl[TBL_IDX(virtual)].present=1;
  tbl[TBL_IDX(virtual)].supervisor=permisos;
  tbl[TBL_IDX(virtual)].addr=fisica>>12;

  tlbflush();

}

void mmu_desmappear_pagina(unsigned int virtual, unsigned int dir_pd){
  pag_entry *dir = (pag_entry*) dir_pd;

  pag_entry *tbl=(pag_entry*) (dir[DIR_IDX(virtual)].addr<<12);
  tbl[TBL_IDX(virtual)].present=0;

}
