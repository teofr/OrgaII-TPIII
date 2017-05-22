; ** por compatibilidad se omiten tildes **
; ==============================================================================
; TRABAJO PRACTICO 3 - System Programming - ORGANIZACION DE COMPUTADOR II - FCEN
; ==============================================================================

%include "imprimir.mac"
%define GDT_IDX_CS_K_DESC 0x40
%define GDT_OFF_DS_K_DESC 0x48
%define GDT_OFF_VIDEO_DESC 0x60
extern GDT_DESC
extern paint
; PREGUNTAR SI SE PUEDE ACCEDER DESDE C

global start


;; Saltear seccion de datos
jmp start

;;
;; Seccion de datos.
;; -------------------------------------------------------------------------- ;;
iniciando_mr_msg db     'Iniciando kernel (Modo Real)...'
iniciando_mr_len equ    $ - iniciando_mr_msg

iniciando_mp_msg db     'Iniciando kernel (Modo Protegido)...'
iniciando_mp_len equ    $ - iniciando_mp_msg

;;
;; Seccion de código.
;; -------------------------------------------------------------------------- ;;

;; Punto de entrada del kernel.
BITS 16
start:
    ; Deshabilitar interrupciones
    cli

    ; Cambiar modo de video a 80 X 50
    mov ax, 0003h
    int 10h ; set mode 03h
    xor bx, bx
    mov ax, 1112h
    int 10h ; load 8x8 font

    ; Imprimir mensaje de bienvenida
    imprimir_texto_mr iniciando_mr_msg, iniciando_mr_len, 0x07, 0, 0


    ; Habilitar A20
    call habilitar_A20
    cli
    ; Cargar la GDT
    lgdt [GDT_DESC]

    ; Setear el bit PE del registro CR0 TODO: Porque puedo usar eax, modo real no es 16bit?
    mov eax, cr0
    or eax, 1
    mov cr0, eax
    ; Saltar a modo protegido

    jmp GDT_IDX_CS_K_DESC:modoprotegido

BITS 32
    modoprotegido:
    ; Establecer selectores de segmentos
    xor eax, eax
    mov ax, GDT_OFF_DS_K_DESC
    mov ds, ax
    mov es, ax
    mov gs, ax
    mov ss, ax

    mov ax, GDT_OFF_VIDEO_DESC
    mov fs, ax



    ; Establecer la base de la pila

    mov ebp, 0x27000
    mov esp, ebp

    ; Imprimir mensaje de bienvenida

    imprimir_texto_mp iniciando_mp_msg, iniciando_mp_len, 0x07, 2, 0

    ; Inicializar pantalla

    mov word [fs:0], 0x0700

    mov ebx, 80
    .cicloCol:
      mov eax, 50
      .cicloFil:

        imprimir_texto_mp 65, 1, 0x8 << 4 | 0x2 << 4 | 0x1, eax, ebx

        dec eax
        cmp eax, 0
        jge .cicloFil

      dec ebx
      cmp ebx, 0
      jge .cicloCol


    ;mov edi, 0xb8000
    ;call paint

    ; Inicializar el manejador de memoria

    ; Inicializar el directorio de paginas

    ; Cargar directorio de paginas

    ; Habilitar paginacion

    ; Inicializar tss

    ; Inicializar tss de la tarea Idle

    ; Inicializar el scheduler

    ; Inicializar la IDT

    ; Cargar IDT

    ; Configurar controlador de interrupciones

    ; Cargar tarea inicial

    ; Habilitar interrupciones

    ; Saltar a la primera tarea: Idle

    ; Ciclar infinitamente (por si algo sale mal...)
    mov eax, 0xFFFF
    mov ebx, 0xFFFF
    mov ecx, 0xFFFF
    mov edx, 0xFFFF
    jmp $
    jmp $

;; -------------------------------------------------------------------------- ;;

%include "a20.asm"
