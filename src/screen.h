/* ** por compatibilidad se omiten tildes **
================================================================================
 TRABAJO PRACTICO 3 - System Programming - ORGANIZACION DE COMPUTADOR II - FCEN
================================================================================
  definicion de funciones del scheduler
*/

#ifndef __SCREEN_H__
#define __SCREEN_H__

/* Definicion de la pantalla */
#define VIDEO_FILS 50
#define VIDEO_COLS 80

#define SCORE_RESTANTES_FIL   47
#define SCORE_A_COL           (39 + 33) / 2
#define SCORE_B_COL           (44 + 38) / 2
#define RESTANTES_A_COL       30
#define RESTANTES_B_COL       48

#include "colors.h"
#include "defines.h"


/* Estructura de para acceder a memoria de video */
typedef struct ca_s {
    unsigned char c;
    unsigned char a;
} ca;


void print(const char * text, unsigned int x, unsigned int y, unsigned short attr);

void print_hex(unsigned int numero, int size, unsigned int x, unsigned int y, unsigned short attr);

void print_int(unsigned int n, unsigned int x, unsigned int y, unsigned short attr);

void print_ca(ca jug, unsigned int x, unsigned int y);

void init_board();

void fill(unsigned short s);

//Funciones para animaciones.h



#endif  /* !__SCREEN_H__ */
