/* ** por compatibilidad se omiten tildes **
================================================================================
 TRABAJO PRACTICO 3 - System Programming - ORGANIZACION DE COMPUTADOR II - FCEN
================================================================================
  definicion de funciones del scheduler
*/

#ifndef __SCHED_H__
#define __SCHED_H__

#include "tss.h"
//#include "screen.h"


unsigned int sched_insert_task(unsigned int jug);
unsigned short sched_proximo_indice();


#endif	/* !__SCHED_H__ */
