/* ** por compatibilidad se omiten tildes **
================================================================================
 TRABAJO PRACTICO 3 - System Programming - ORGANIZACION DE COMPUTADOR II - FCEN
================================================================================
  definicion de funciones del scheduler
*/

#include "screen.h"

void print(const char * text, unsigned int x, unsigned int y, unsigned short attr) {
    ca (*p)[VIDEO_COLS] = (ca (*)[VIDEO_COLS]) VIDEO;
    int i;
    for (i = 0; text[i] != 0; i++) {
        p[y][x].c = (unsigned char) text[i];
        p[y][x].a = (unsigned char) attr;
        x++;
        if (x == VIDEO_COLS) {
            x = 0;
            y++;
        }
    }
}

void print_hex(unsigned int numero, int size, unsigned int x, unsigned int y, unsigned short attr) {
    ca (*p)[VIDEO_COLS] = (ca (*)[VIDEO_COLS]) VIDEO; // magia
    int i;
    char hexa[8];
    char letras[16] = "0123456789ABCDEF";
    hexa[0] = letras[ ( numero & 0x0000000F ) >> 0  ];
    hexa[1] = letras[ ( numero & 0x000000F0 ) >> 4  ];
    hexa[2] = letras[ ( numero & 0x00000F00 ) >> 8  ];
    hexa[3] = letras[ ( numero & 0x0000F000 ) >> 12 ];
    hexa[4] = letras[ ( numero & 0x000F0000 ) >> 16 ];
    hexa[5] = letras[ ( numero & 0x00F00000 ) >> 20 ];
    hexa[6] = letras[ ( numero & 0x0F000000 ) >> 24 ];
    hexa[7] = letras[ ( numero & 0xF0000000 ) >> 28 ];
    for(i = 0; i < size; i++) {
        p[y][x + size - i - 1].c = hexa[i];
        p[y][x + size - i - 1].a = attr;
    }
}

void print_int(unsigned int n, unsigned int x, unsigned int y, unsigned short attr) {
    ca (*p)[VIDEO_COLS] = (ca (*)[VIDEO_COLS]) VIDEO; // magia
    if( n > 9 ) {
      int a = n / 10;
      n -= 10 * a;
      print_int(a,x-1,y,attr);
    }
    p[y][x].c = '0'+n;
    p[y][x].a = attr;
}

void print_ca(ca jug, unsigned int x, unsigned int y){
  ca (*p)[VIDEO_COLS] = (ca (*)[VIDEO_COLS]) VIDEO;

  p[y][x].c = (unsigned char) jug.c;
  p[y][x].a = (unsigned char) jug.a;

}

void imprimir_negro(){
  ca (*p)[VIDEO_COLS] = (ca (*)[VIDEO_COLS]) VIDEO;
  int i,j;

  for(i = 0; i < VIDEO_COLS; i++){
    for(j = 0; j < VIDEO_FILS; j++){

      p[j][i].c = 0x20;
      p[j][i].a = C_BG_BLACK;
    }
  }
}

void imprimir_verde(){
  ca (*p)[VIDEO_COLS] = (ca (*)[VIDEO_COLS]) VIDEO;
  int i,j;

  for(j = 0; j < VIDEO_FILS; j++){
    for(i = 0; i < VIDEO_COLS; i++){
      p[j][i].c = 0x20;
      p[j][i].a = C_BG_GREEN | C_FG_GREEN;
    }
  }
}

void imprimir_azul(){
  ca (*p)[VIDEO_COLS] = (ca (*)[VIDEO_COLS]) VIDEO;
  int i,j;

  for(j = 0; j < VIDEO_FILS; j++){
    for(i = 0; i < VIDEO_COLS; i++){
      p[j][i].c = 0x20;
      p[j][i].a = C_BG_BLUE | C_FG_BLUE;
    }
  }
}

void imprimir_bordes(){
  ca (*p)[VIDEO_COLS] = (ca (*)[VIDEO_COLS]) VIDEO;
  int i;
  for(i = 0; i < VIDEO_FILS; i++){
    p[i][0].c = 0x20;
    p[i][0].a = C_BG_RED;

    p[i][VIDEO_COLS-1].c = 0x20;
    p[i][VIDEO_COLS-1].a = C_BG_BLUE;
  }
}

void imprimir_info(){
  ca (*p)[VIDEO_COLS] = (ca (*)[VIDEO_COLS]) VIDEO;
  int i,j;

  for(i = 45; i < VIDEO_FILS; i++){
    for(j = 0; j < VIDEO_COLS; j++){

      if(j > 33 && j < 39){
        p[i][j].c = 0x20;
        p[i][j].a = C_BG_RED;
      } else if (j > 38 && j < 44){
        p[i][j].c = 0x20;
        p[i][j].a = C_BG_BLUE;
      } else {
        p[i][j].c = 0x20;
        p[i][j].a = C_BG_BLACK;
      }

    }

  }

  for(i = 0; i < VIDEO_COLS; i++){
    p[0][i].c = 0x20;
    p[0][i].a = C_BG_BLACK;
  }
  //Printea score de cada jugador
  print_int(0, (39 + 33) / 2, 47, C_BG_RED | C_FG_WHITE);
  print_int(0, (44 + 38) / 2, 47, C_BG_BLUE | C_FG_WHITE);

  //Printea cantidad de zombies disponibles de cada jugador
  print_int(8, 30, 47, C_BG_RED | C_FG_WHITE);
  print_int(8, 47, 47, C_BG_BLUE | C_FG_WHITE);

  //Printea info de zombis de cada jugador
  for(i = 1; i < 9; i++){
    print_int(i,  4 + i*2, 46, C_BG_BLACK | C_FG_WHITE);//Printea numeros de jug rojo
    print("X", 4 + i*2, 48, C_BG_BLACK | C_FG_RED );

    print_int(i,  54 + 4 + i*2, 46, C_BG_BLACK | C_FG_WHITE);//Printea numeros de jug azul
    print("X", 54 + 4 + i*2, 48, C_BG_BLACK | C_FG_BLUE );

  }
}

void init_board(){
  imprimir_negro();
  imprimir_verde();
  imprimir_bordes();
  imprimir_info();
}


void print_patron(patron p){
  int i;
  for(i = 0; i < p.tam; i++){
    print_ca(p.color, p.columnas[i], p.filas[i]);
  }
}

void print_frame(frame f){
  int i;
  for(i = 0; i < f.tam; i++){
    print_patron(f.patrones[i]);
  }
}

void print_gif(gif g){
  int i;
  for(i = 0; i < g.tam; i++){
    print_frame(g.frames[i]);
    WAIT(10000)
  }
}