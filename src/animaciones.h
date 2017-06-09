#include "defines.h"
#include "colors.h"

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

#define NEGRO 0x20

typedef struct patron_t{
    ca color;
    unsigned int filas[];
    unsigned int columnas[];
    unsigned int tam;
}__atribute__((__packed__)) patron;

patron patron_init(ca color, unsigned int f[], unsigned int c[], unsigned int t);

typedef struct frame_t {
    patron patrones[];
    unsigned int tam;

}__atribute__((__packed__)) frame; 

unsigned int castilloX[TAM_CASTILLO];
unsigned int castilloY[TAM_CASTILLO];

unsigned int mensajeX_f1[TAM_ESTRELLA_F1];
unsigned int mensajeY_f1[TAM_ESTRELLA_F1];

unsigned int mensajeX_f2[TAM_ESTRELLA_F2];
unsigned int mensajeY_f2[TAM_ESTRELLA_F2];

unsigned int mensajeX_f3[TAM_ESTRELLA_F3];
unsigned int mensajeY_f3[TAM_ESTRELLA_F3];

unsigned int mensajeX_f4[TAM_ESTRELLA_F4];
unsigned int mensajeY_f4[TAM_ESTRELLA_F4];

unsigned int mensajeX_f5[TAM_ESTRELLA_F5];
unsigned int mensajeY_f5[TAM_ESTRELLA_F5];

unsigned int mensajeX_f6[TAM_ESTRELLA_F6];
unsigned int mensajeY_f6[TAM_ESTRELLA_F6];

unsigned int mensajeX_f7[TAM_ESTRELLA_F7];
unsigned int mensajeY_f7[TAM_ESTRELLA_F7];

unsigned int mensajeX_f8[TAM_ESTRELLA_F8];
unsigned int mensajeY_f8[TAM_ESTRELLA_F8];


unsigned int estrellaX_f1[TAM_ESTRELLA_F1];
unsigned int estrellaY_f1[TAM_ESTRELLA_F1];

unsigned int estrellaX_f2[TAM_ESTRELLA_F2];
unsigned int estrellaY_f2[TAM_ESTRELLA_F2];

unsigned int estrellaX_f3[TAM_ESTRELLA_F3];
unsigned int estrellaY_f3[TAM_ESTRELLA_F3];

unsigned int estrellaX_f4[TAM_ESTRELLA_F4];
unsigned int estrellaY_f4[TAM_ESTRELLA_F4];

unsigned int estrellaX_f5[TAM_ESTRELLA_F5];
unsigned int estrellaY_f5[TAM_ESTRELLA_F5];

unsigned int estrellaX_f6[TAM_ESTRELLA_F6];
unsigned int estrellaY_f6[TAM_ESTRELLA_F6];

unsigned int estrellaX_f7[TAM_ESTRELLA_F7];
unsigned int estrellaY_f7[TAM_ESTRELLA_F7];

unsigned int estrellaX_f8[TAM_ESTRELLA_F8];
unsigned int estrellaY_f8[TAM_ESTRELLA_F8];