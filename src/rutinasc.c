#include "isr.h"

void isr0(){
    int i,j,k = 0;
    char* codigo_error = "SEG FAULT";

    while(k < 2*VIDEO_COLS-9){
        print(codigo_error, j, i, C_FG_RED | C_BG_BLACK);
        i = (i+1) % VIDEO_FILS;
        j += k%2;
        k++;
    }
}