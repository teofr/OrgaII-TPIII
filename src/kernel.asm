; ** por compatibilidad se omiten tildes **
; ==============================================================================
; TRABAJO PRACTICO 3 - System Programming - ORGANIZACION DE COMPUTADOR II - FCEN
; ==============================================================================

%include "imprimir.mac"
%define GDT_OFF_CS_K_DESC 0x40
%define GDT_OFF_DS_K_DESC 0x48
%define GDT_OFF_VIDEO_DESC 0x60
%define PAG_DIR_ADDR 0x27000
%define GDT_OFF_INICIAL_DESC 13*8
%define GDT_OFF_IDLE_DESC 14*8

extern GDT_DESC
extern IDT_DESC
extern print_int
extern idt_inicializar
extern init_board
extern pag_init
extern mmu_inicializar
extern mmu_inicializar_dir_zombi
extern game_init
extern tss_inicializar

;;PIC
extern resetear_pic
extern habilitar_pic

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

    ; Setear el bit PE del registro CR0
    mov eax, cr0
    or eax, 1
    mov cr0, eax

    ; Saltar a modo protegido
    jmp GDT_OFF_CS_K_DESC:modoprotegido

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
    call llenar_verde

    ; Inicializar el manejador de memoria
    call mmu_inicializar

    ; Inicializar el directorio de paginas
    call pag_init

    ; Cargar directorio de paginas
    mov eax, PAG_DIR_ADDR
    mov cr3, eax

    ; Habilitar paginacion
    mov eax, cr0
    or eax, 0x80000001
    mov cr0, eax

    ; Inicializar tss

    ; Inicializar tss de la tarea Idle

    ; Inicializar el scheduler

    ; Inicializar la IDT
    call idt_inicializar

    ; Cargar IDT
    lidt [IDT_DESC]


    ; Configurar controlador de interrupciones
    call resetear_pic
    call habilitar_pic

    ; Cargar tarea inicial
    call init_board
    call game_init

    call tss_inicializar
    mov ax, GDT_OFF_INICIAL_DESC
    ltr ax
    jmp GDT_OFF_IDLE_DESC:0
    ; Habilitar interrupciones
    sti




    ; Saltar a la primera tarea: Idle

    ; Ciclar infinitamente (por si algo sale mal...)
    ciclo:
    mov eax, 0xFFFF
    mov ebx, 0xFFFF
    mov ecx, 0xFFFF
    mov edx, 0xFFFF

    jmp ciclo
    jmp ciclo

;; -------------------------------------------------------------------------- ;;

%include "a20.asm"
%include "screen.asm"
