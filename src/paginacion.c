/* ** por compatibilidad se omiten tildes **
================================================================================
 TRABAJO PRACTICO 3 - System Programming - ORGANIZACION DE COMPUTADOR II - FCEN
================================================================================
  definicion de la tabla de descriptores globales
*/

#include "paginacion.h"

#define PAG_ENTRY_MACRO(pag, index, add)                 \
    pag[index].present=(unsigned char) 1;                 \
    pag[index].write=(unsigned char) 1;                   \
    pag[index].supervisor=(unsigned char) 1;              \
    pag[index].wthrough=(unsigned char) 0;                \
    pag[index].cache_disabled=(unsigned char) 0;          \
    pag[index].accesed=(unsigned char) 0;                 \
    pag[index].dirty=(unsigned char) 0;               \
    pag[index].page_size=(unsigned char) 0;               \
    pag[index].ignored=(unsigned char) 0;                 \
    pag[index].avl=(unsigned char) 0;                 \
    pag[index].addr=(unsigned int) add;

void pag_init(){
  pag_entry (*pag_dir) = (pag_entry*) PAG_DIR;
  PAG_ENTRY_MACRO(pag_dir, 0, PAG_TBL>>12);

  pag_entry (*pag_tbl) = (pag_entry*) PAG_TBL;

  int i;
  for (i=0; i<PAG_COUNT; i++){
    PAG_ENTRY_MACRO(pag_tbl, i, i);
  }

}
