#include "rutinasc.h"

void isr0(){

  imprimir_azul();
  print_gif(seg_fault_gif);

}

void isr32(){
  state++;
  state=state%diffStates;
  ca temp;
  temp.c=states[state];
  temp.a=C_BG_BLACK | C_FG_WHITE;
  print_ca(temp, 79, 49);
}

void isr33(){
  char c = 0;
  c = inb(0x60);
  game_keyboard_parser(c);
}




void init_board2();

void isr(unsigned int a){

    int i = 0;
    int j = 0;
    int k = 0;
    char* codigo_error;

    switch (a) {

      case 1:
        codigo_error ="   Debug   ";
        break;

      case 2:
        codigo_error ="   NMI Interrupt   ";
        break;

      case 3:
        codigo_error ="   Breakpoint   ";
        break;

      case 4:
        codigo_error ="   Overflow   ";
        break;

      case 5:
        codigo_error ="   BOUND Range Exceeded   ";
        break;

      case 6:
        codigo_error ="   Invalid Opcode   ";
        break;

      case 7:
        codigo_error ="   Device Not Available   ";
        break;

      case 8:
        codigo_error =" DT";
        break;

      case 9:
        codigo_error ="   CoProcessor Segment Overrun   ";
        break;

      case 10:
        codigo_error ="   Invalid TSS   ";
        break;

      case 11:
        codigo_error ="   Segment Not Present   ";
        break;

      case 12:
        codigo_error ="   Stack   ";
        break;

      case 13:
        codigo_error ="d";
        break;

      case 14:
        codigo_error ="   SEGFAULT   ";
        break;

      case 15:
        codigo_error ="   SEGFAULT   ";
        break;

      case 16:
        codigo_error ="   SEGFAULT   ";
        break;

      case 17:
        codigo_error ="   SEGFAULT   ";
        break;

      case 18:
        codigo_error ="   SEGFAULT   ";
        break;

      case 19:
        codigo_error ="   SEGFAULT   ";
        break;

      default:
        codigo_error ="  Ni idea   ";
    }

    int sentido = 1;
    int cambio = 0;
    int mult = 1;

    for (k = 0; 1 ; k++){

      int wait = 100000;
      while(wait > 0){
        wait--;
      }

      print(codigo_error, j, i,  ((C_FG_RED + i) | (C_BG_BLACK + j*i)) % C_BLINK);

      i = (i + sentido) % VIDEO_FILS;
      if (i == 49){
        sentido = -1;
        cambio += (49 - cambio) / 2;
      }

      if(i == cambio){
        sentido = 1;
      }

      j = (j + (k % 2));
      if (j >= VIDEO_COLS){
        j = (13 * mult) % VIDEO_COLS;
        i = 0;
        cambio = 0;
        sentido = 1;
        mult++;
        wait = 1000000;

        while(wait > 0){
          wait--;
        }
      }

      if (mult >= 30){
        mult = 1;
        init_board2();
      }
    }
}

void imprimir_negro2(){
  ca (*p)[VIDEO_COLS] = (ca (*)[VIDEO_COLS]) VIDEO;
  int i,j;

  for(i = 0; i < VIDEO_COLS; i++){
    for(j = 0; j < VIDEO_FILS; j++){

      p[j][i].c = 0x20;
      p[j][i].a = C_BG_BLACK;
    }
  }
}

void imprimir_verde2(){
  ca (*p)[VIDEO_COLS] = (ca (*)[VIDEO_COLS]) VIDEO;
  int i,j;

  for(j = 0; j < VIDEO_FILS; j++){
    for(i = 0; i < VIDEO_COLS; i++){
      p[j][i].c = 0x20;
      p[j][i].a = 0x22;
    }
  }
}

void imprimir_bordes2(){
  ca (*p)[VIDEO_COLS] = (ca (*)[VIDEO_COLS]) VIDEO;
  int i;
  for(i = 0; i < VIDEO_FILS; i++){
    p[i][0].c = 0x20;
    p[i][0].a = C_BG_RED;

    p[i][VIDEO_COLS-1].c = 0x20;
    p[i][VIDEO_COLS-1].a = C_BG_BLUE;
  }
}

void imprimir_info2(){
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

  //Printea score de cada jugador
  print_int(0, (39+33)/2, 47, C_BG_RED | C_FG_WHITE);
  print_int(0, (44+38)/2, 47, C_BG_BLUE | C_FG_WHITE);

  //Printea cantidad de zombies disponibles de cada jugador
  print_int(8, 30, 47, C_BG_RED | C_FG_WHITE);
  print_int(8, 47, 47, C_BG_BLUE | C_FG_WHITE);

  //Printea info de zombis de cada jugador
  for(i = 1; i < 9; i++){
    print_int(i,  4+i*2,46, C_BG_BLACK | C_FG_WHITE);//Printea numeros de jug rojo
    print("X", 4+i*2, 48, C_BG_BLACK | C_FG_RED );

    print_int(i,  54+4+i*2, 46, C_BG_BLACK | C_FG_WHITE);//Printea numeros de jug azul
    print("X", 54+4+i*2, 48, C_BG_BLACK | C_FG_BLUE );

  }
}

void init_board2(){
  imprimir_negro2();
  imprimir_verde2();
  imprimir_bordes2();
  imprimir_info2();
}
