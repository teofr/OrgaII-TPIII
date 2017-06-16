/* ** por compatibilidad se omiten tildes **
================================================================================
 TRABAJO PRACTICO 3 - System Programming - ORGANIZACION DE COMPUTADOR II - FCEN
================================================================================
  definicion de estructuras para administrar tareas
*/

#include "tss.h"

tss tss_inicial;
tss tss_idle;

tss tss_zombis[2][CANT_ZOMBIS];
//tss tss_zombisB[CANT_ZOMBIS];


void tss_inicializar() {
  tss template;
  // Tarea Inicial
  tss_inicial=template;
  init_tss_desc(GDT_IDX_TSS_INICIAL, (unsigned int) &tss_inicial, (unsigned int) sizeof(tss_inicial), 0);


  //Tarea Idle
  template.cr3=rcr3();
  template.eip=0x16000;
  template.eflags=0x202;
  template.esp=0x27000;
  template.ebp=0x27000;
  template.es=GDT_OFF_DS_K_DESC;
  template.cs=GDT_OFF_CS_K_DESC;
  template.ss=GDT_OFF_DS_K_DESC;
  template.ds=GDT_OFF_DS_K_DESC;
  template.fs=GDT_OFF_VIDEO_DESC;
  template.gs=GDT_OFF_DS_K_DESC;

  tss_idle=template;

  init_tss_desc(GDT_IDX_TSS_IDLE,(unsigned int) &tss_idle,(unsigned int) sizeof(tss_idle), 0);

  int i;
  for(i=0; i<2*CANT_ZOMBIS; i++){
    tss_zombis[i%2][i/2]=tss_idle;
  }



}

void tss_new_task(unsigned int jug, unsigned int libre){
   unsigned int tipo=1;  //LLENAR
   tss_zombis[jug][libre].cr3=mmu_inicializar_dir_zombi(jug, tipo);
   tss_zombis[jug][libre].eip=0x08000000;
   tss_zombis[jug][libre].eflags=0x202;
   tss_zombis[jug][libre].esp=0x08001000;
   tss_zombis[jug][libre].ebp=0x08001000;
   tss_zombis[jug][libre].es=GDT_OFF_DS_U_DESC;
   tss_zombis[jug][libre].cs=GDT_OFF_CS_U_DESC;
   tss_zombis[jug][libre].ss=GDT_OFF_DS_U_DESC;
   tss_zombis[jug][libre].ds=GDT_OFF_DS_U_DESC;
   tss_zombis[jug][libre].fs=GDT_OFF_DS_U_DESC;
   tss_zombis[jug][libre].gs=GDT_OFF_DS_U_DESC;
   tss_zombis[jug][libre].esp0=mmu_dameMem()+0x1000;
   tss_zombis[jug][libre].ss0=GDT_OFF_DS_K_DESC;
}

void tss_clean_zombie(unsigned int jug, unsigned int libre){
  tss_zombis[jug][libre]=tss_idle;
}
