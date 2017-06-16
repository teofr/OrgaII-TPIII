#ifndef __RUTINASC_H__
#define __RUTINASC_H__

#include "colors.h"
#include "screen.h"
#include "i386.h"
#include "isr.h"
#include "game.h"

#define diffStates 4
char* states;
unsigned int state;

void isr0();
void isr33();
void isr();

extern void print_gif_seg_fault();
#endif
