/* ** por compatibilidad se omiten tildes **
================================================================================
 TRABAJO PRACTICO 3 - System Programming - ORGANIZACION DE COMPUTADOR II - FCEN
================================================================================
  rutinas comunes para lectura y escritura de registros desde C
*/

#ifndef __i386_H__
#define __i386_H__

#define LS_INLINE static __inline __attribute__((always_inline))

LS_INLINE void lcr0(unsigned int val);
LS_INLINE unsigned int rcr0(void);
LS_INLINE void lcr1(unsigned int val);
LS_INLINE unsigned int rcr1(void);
LS_INLINE void lcr2(unsigned int val);
LS_INLINE unsigned int rcr2(void);
LS_INLINE void lcr3(unsigned int val);
LS_INLINE unsigned int rcr3(void);
LS_INLINE void lcr4(unsigned int val);
LS_INLINE unsigned int rcr4(void);
LS_INLINE void tlbflush(void);
LS_INLINE void ltr(unsigned short sel);
LS_INLINE unsigned short rtr(void);
LS_INLINE void hlt(void);
LS_INLINE void breakpoint(void);
LS_INLINE unsigned int resp(void);
LS_INLINE unsigned int rebp(void);
LS_INLINE unsigned short res(void);
LS_INLINE unsigned short rcs(void);
LS_INLINE unsigned short rss(void);
LS_INLINE unsigned short rds(void);
LS_INLINE unsigned short rfs(void);
LS_INLINE unsigned short rgs(void);

static inline char inb(unsigned short port);
static inline void outb(unsigned short port, char val);

/*
 * Implementaciones
 */

LS_INLINE void lcr0(unsigned int val) {
    __asm __volatile("movl %0,%%cr0" : : "r" (val));
}

LS_INLINE unsigned int rcr0(void) {
    unsigned int val;
    __asm __volatile("movl %%cr0,%0" : "=r" (val));
    return val;
}

LS_INLINE void lcr1(unsigned int val) {
    __asm __volatile("movl %0,%%cr1" : : "r" (val));
}

LS_INLINE unsigned int rcr1(void) {
    unsigned int val;
    __asm __volatile("movl %%cr1,%0" : "=r" (val));
    return val;
}

LS_INLINE void lcr2(unsigned int val) {
    __asm __volatile("movl %0,%%cr2" : : "r" (val));
}

LS_INLINE unsigned int rcr2(void) {
    unsigned int val;
    __asm __volatile("movl %%cr2,%0" : "=r" (val));
    return val;
}

LS_INLINE void lcr3(unsigned int val) {
    __asm __volatile("movl %0,%%cr3" : : "r" (val));
}

LS_INLINE unsigned int rcr3(void) {
    unsigned int val;
    __asm __volatile("movl %%cr3,%0" : "=r" (val));
    return val;
}

LS_INLINE void lcr4(unsigned int val) {
    __asm __volatile("movl %0,%%cr4" : : "r" (val));
}

LS_INLINE unsigned int rcr4(void) {
    unsigned int cr4;
    __asm __volatile("movl %%cr4,%0" : "=r" (cr4));
    return cr4;
}

 LS_INLINE void tlbflush(void) {
    unsigned int cr3;
    __asm __volatile("movl %%cr3,%0" : "=r" (cr3));
     __asm __volatile("movl %0,%%cr3" : : "r" (cr3));
}

LS_INLINE void ltr(unsigned short sel) {
    __asm __volatile("ltr %0" : : "r" (sel));
}

LS_INLINE unsigned short rtr(void) {
    unsigned short sel;
    __asm __volatile("str %0" : "=r" (sel) : );
    return sel;
}

LS_INLINE void hlt(void) {
    __asm __volatile("hlt" : : );
}

LS_INLINE void breakpoint(void) {
    __asm __volatile("xchg %%bx, %%bx" : :);
}

static inline char inb(unsigned short port)
{
    char ret;
    asm volatile ( "inb %1, %0"
                   : "=a"(ret)
                   : "Nd"(port) );
    return ret;
}

static inline void outb(unsigned short port, char val)
{
    asm volatile ( "outb %0, %1" : : "a"(val), "Nd"(port) );
    /* There's an outb %al, $imm8  encoding, for compile-time constant port numbers that fit in 8b.  (N constraint).
     * Wider immediate constants would be truncated at assemble-time (e.g. "i" constraint).
     * The  outb  %al, %dx  encoding is the only option for all other cases.
     * %1 expands to %dx because  port  is a unsigned short.  %w1 could be used if we had the port number a wider C type */
}

LS_INLINE unsigned int resp(void) {
    unsigned int val;
    __asm __volatile("movl %%esp,%0" : "=r" (val));
    return val;
}

LS_INLINE unsigned int rebp(void) {
    unsigned int val;
    __asm __volatile("movl %%ebp,%0" : "=r" (val));
    return val;
}

LS_INLINE unsigned short res(void) {
    unsigned short val;
    __asm __volatile("movl %%es,%0" : "=r" (val));
    return val;
}

LS_INLINE unsigned short rcs(void) {
    unsigned short val;
    __asm __volatile("movl %%cs,%0" : "=r" (val));
    return val;
}

LS_INLINE unsigned short rss(void) {
    unsigned short val;
    __asm __volatile("movl %%ss,%0" : "=r" (val));
    return val;
}

LS_INLINE unsigned short rds(void) {
    unsigned short val;
    __asm __volatile("movl %%ds,%0" : "=r" (val));
    return val;
}

LS_INLINE unsigned short rfs(void) {
    unsigned short val;
    __asm __volatile("movl %%fs,%0" : "=r" (val));
    return val;
}

LS_INLINE unsigned short rgs(void) {
    unsigned short val;
    __asm __volatile("movl %%gs,%0" : "=r" (val));
    return val;
}
#endif  /* !__i386_H__ */
