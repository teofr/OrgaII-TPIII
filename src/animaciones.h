#ifndef __ANIMACIONES_H__
#define __ANIMACIONES_H__

#include "defines.h"
#include "colors.h"
#include "screen.h"

#define TAM_CASTILLO 1785

#define TAM_MENSAJE_F1 27
#define TAM_MENSAJE_F2 51
#define TAM_MENSAJE_F3 75
#define TAM_MENSAJE_F4 92
#define TAM_MENSAJE_F5 116
#define TAM_MENSAJE_F6 137
#define TAM_MENSAJE_F7 151
#define TAM_MENSAJE_F8 166

#define TAM_ESTRELLA_F1 5
#define TAM_ESTRELLA_F2 9
#define TAM_ESTRELLA_F3 25
#define TAM_ESTRELLA_F4 46
#define TAM_ESTRELLA_F5 66
#define TAM_ESTRELLA_F6 82
#define TAM_ESTRELLA_F7 93
#define TAM_ESTRELLA_F8 119

void print_frame(unsigned int filas[], unsigned int columnas[], ca color);


#endif
