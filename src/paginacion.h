/* ** por compatibilidad se omiten tildes **
================================================================================
 TRABAJO PRACTICO 3 - System Programming - ORGANIZACION DE COMPUTADOR II - FCEN
================================================================================
  definicion de la tabla de paginacion
*/

#ifndef __PAG_H__
#define __PAG_H__

#include "defines.h"

#define PAG_COUNT 1024
#define PAG_DIR 0x27000
#define PAG_TBL 0x28000

typedef struct str_pag_descriptor {
    unsigned int    pag_addr;
} __attribute__((__packed__)) pag_descriptor;

typedef struct str_pag_entry {
    unsigned char   present:1;
    unsigned char   write:1;
    unsigned char   supervisor:1;
    unsigned char   wthrough:1;
    unsigned char   cache_disabled:1;
    unsigned char   accesed:1;
    unsigned char   dirty:1;
    unsigned char   page_size:1;
    unsigned char   ignored:1;
    unsigned char   avl:3;
    unsigned int    addr:20;
} __attribute__((__packed__, aligned (4))) pag_entry;

void pag_init();

#endif
