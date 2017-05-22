/* ** por compatibilidad se omiten tildes **
================================================================================
 TRABAJO PRACTICO 3 - System Programming - ORGANIZACION DE COMPUTADOR II - FCEN
================================================================================

    Definiciones globales del sistema.
*/

#ifndef __DEFINES_H__
#define __DEFINES_H__

/* Bool */
/* -------------------------------------------------------------------------- */
#define TRUE                    0x00000001
#define FALSE                   0x00000000
#define ERROR                   1


/* Misc */
/* -------------------------------------------------------------------------- */
#define CANT_ZOMBIS             8

#define SIZE_W                  78
#define SIZE_H                  44


/* Indices en la gdt */
/* -------------------------------------------------------------------------- */
#define GDT_COUNT 30

#define GDT_IDX_NULL_DESC           0
#define GDT_IDX_CS_K_DESC           8
#define GDT_IDX_DS_K_DESC           9
#define GDT_IDX_CS_U_DESC           10
#define GDT_IDX_DS_U_DESC           11
#define GDT_IDX_VIDEO_DESC           12

/* Offsets en la gdt */
/* -------------------------------------------------------------------------- */
#define GDT_OFF_NULL_DESC           (GDT_IDX_NULL_DESC      << 3)
#define GDT_OFF_CS_K_DESC           (GDT_IDX_CS_K_DESC      << 3)
#define GDT_OFF_DS_K_DESC           (GDT_IDX_DS_K_DESC      << 3)
#define GDT_OFF_CS_U_DESC           (GDT_IDX_CS_U_DESC      << 3 | 3) // el | 3 es para setear el bit de privilegios
#define GDT_OFF_DS_U_DESC           (GDT_IDX_DS_U_DESC      << 3 | 3)
#define GDT_OFF_VIDEO_DESC          (GDT_IDX_VIDEO_DESC     << 3)

/* Direcciones de memoria */
/* -------------------------------------------------------------------------- */
#define VIDEO                   0x000B8000 /* direccion fisica del buffer de video */


#endif  /* !__DEFINES_H__ */
