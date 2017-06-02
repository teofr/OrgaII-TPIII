/* ** por compatibilidad se omiten tildes **
================================================================================
 TRABAJO PRACTICO 3 - System Programming - ORGANIZACION DE COMPUTADOR II - FCEN
================================================================================
  definicion de funciones del manejador de memoria
*/

#ifndef __MMU_H__
#define __MMU_H__

#include "defines.h"
#include "i386.h"
#include "tss.h"
#include "game.h"
#include "paginacion.h"

#define DIR_IDX(n) n>>22
#define TBL_IDX(n) (n<<10)>>22

void mmu_inicializar();
unsigned int mmu_dameMem();
void mmu_mappear_pagina(unsigned int virtual, unsigned int dir_pd, unsigned int fisica, unsigned int permisos);
void mmu_desmappear_pagina(unsigned int virtual, unsigned int dir_pd);




#endif	/* !__MMU_H__ */
