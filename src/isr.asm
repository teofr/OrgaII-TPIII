; ** por compatibilidad se omiten tildes **
; ==============================================================================
; TRABAJO PRACTICO 3 - System Programming - ORGANIZACION DE COMPUTADOR II - FCEN
; ==============================================================================
; definicion de rutinas de atencion de interrupciones

%include "imprimir.mac"


BITS 32

sched_tarea_offset:     dd 0x00
sched_tarea_selector:   dw 0x00
;;Print
extern print_int

;; PIC
extern fin_intr_pic1

;; Sched
extern sched_proximo_indice

;;Rutinas de interrupcion (rutinasc.h)
extern isr
extern isr0
extern isr33
extern avanzar_reloj

;;
;; Definición de MACROS
;; -------------------------------------------------------------------------- ;;

%macro ISR 1
global _isr%1
;void print_int(unsigned int n, unsigned int x, unsigned int y, unsigned short attr);

_isr%1:
    pushfd
    pushad
    call fin_intr_pic1
    mov eax, %1
    push %1
    call isr
    popad
    popfd
    iret

%endmacro

%macro ISR2 1
global _isr%1

_isr%1:
  xchg bx, bx
    pushfd
    pushad
    call fin_intr_pic1
    mov eax, %1
    call isr%1
    popad
    popfd
    iret
%endmacro
;;
;; Datos
;; -------------------------------------------------------------------------- ;;
; Scheduler
isrnumero:           dd 0x00000000
isrClock:            db '|/-\'

;;
;; Rutina de atención de las EXCEPCIONES
;; -------------------------------------------------------------------------- ;;

ISR2 0
ISR 1
ISR 2
ISR 3
ISR 4
ISR 5
ISR 6
ISR 7
ISR 8
ISR 9
ISR 10
ISR 11
ISR 12
ISR 13
ISR 14
ISR 15
ISR 16
ISR 17
ISR 18
ISR 19

global _isr32
_isr32:

  pushad
  call avanzar_reloj

  call sched_proximo_indice
  cmp ax, 0
  je .nojump
  xchg bx, bx

  mov [sched_tarea_selector], ax

  call fin_intr_pic1
  xchg bx, bx
  jmp far [sched_tarea_offset]
  jmp .end

  .nojump:
    call fin_intr_pic1

  .end:
  popad
  iret

ISR2 33


global _isr102:
_isr102:
  jmp $
  iret

;;
;; Rutina de atención del RELOJ
;; -------------------------------------------------------------------------- ;;

;;
;; Rutina de atención del TECLADO
;; -------------------------------------------------------------------------- ;;

;;
;; Rutinas de atención de las SYSCALLS
;; -------------------------------------------------------------------------- ;;

%define IZQ 0xAAA
%define DER 0x441
%define ADE 0x83D
%define ATR 0x732


;; Funciones Auxiliares
;; -------------------------------------------------------------------------- ;;
proximo_reloj:
        pushad
        inc DWORD [isrnumero]
        mov ebx, [isrnumero]
        cmp ebx, 0x4
        jl .ok
                mov DWORD [isrnumero], 0x0
                mov ebx, 0
        .ok:
                add ebx, isrClock
                imprimir_texto_mp ebx, 1, 0x0f, 49, 79
                popad
        ret
