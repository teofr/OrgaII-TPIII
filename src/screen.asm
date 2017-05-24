
%define VERDE (0x2 << 4) | 0x2
%define PANTALLA_SIZE 2*80*50-1
%define CHAR_VACIO 0x20

section .text
BITS 32

llenar_verde:

  mov ebx, PANTALLA_SIZE

  .ciclo:
    mov byte [fs:ebx], VERDE

    dec ebx
    mov byte [fs:ebx], CHAR_VACIO
    dec ebx

    cmp ebx, 0
    jge .ciclo

ret
