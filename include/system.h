#include <stdint.h>

#ifndef __SYSTEM_H
#define __SYSTEM_H
typedef int size_t;

/* KERNEL.C */
extern unsigned char *memcpy(unsigned char *dest, const unsigned char *src, int count);
extern unsigned short *memcpyw(unsigned short *dest, const unsigned short *src, size_t count);
extern unsigned char *memset(unsigned char *dest, unsigned char val, int count);
extern unsigned short *memsetw(unsigned short *dest, unsigned short val, int count);
extern size_t strlen(const char *str);
extern unsigned char inportb (unsigned short _port);
extern void outportb (unsigned short _port, unsigned char _data);
extern unsigned short inw(unsigned short port);
extern void outw(unsigned short port, unsigned short data);

/* SCREEN.C */
extern void cls();
extern void put_char(unsigned char c);
extern void put_string(unsigned char *text);
extern void set_text_color(unsigned char forecolor, unsigned char backcolor);
extern void init_video();

/* GDT.C */
extern void _gdt_flush();
extern void gdt_set_gate(int num, unsigned long base, unsigned long limit, unsigned char access, unsigned char gran);
extern void gdt_install();

/* IDT.C */
extern void _idt_load();
extern void idt_set_gate(unsigned char num, unsigned long base, unsigned short sel, unsigned char flags);
extern void idt_install();

/* IRS.C */
/* This defines what the stack looks like after an ISR was running */
struct regs
{
    unsigned int gs, fs, es, ds;      /* pushed the segs last */
    unsigned int edi, esi, ebp, esp, ebx, edx, ecx, eax;  /* pushed by 'pusha' */
    unsigned int int_no, err_code;    /* our 'push byte #' and ecodes do this */
    unsigned int eip, cs, eflags, useresp, ss;   /* pushed by the processor automatically */ 
};
extern void isrs_install();
extern void _fault_handler(struct regs *r);

/* IRQ.C */
extern void _irq_handler(struct regs *r);
extern void irq_install_handler(int irq, void (*handler)(struct regs *r));
extern void irq_install();

/* TIMER.C */
extern void timer_install();
extern void timer_wait(int ticks);

/* KEYBOARD.C */
extern void keyboard_install();
extern void keyboard_handler(struct regs *r);

/* PAGING.C */
extern void enable_paging();

/* DISK.C */
extern char *ata_lba_read(unsigned int drive, unsigned int addr);
extern void ata_lba_write(unsigned char drive, unsigned int addr,char* buffer);

extern void _write_cr3(uint32_t);
extern uint32_t _read_cr0(void);
extern void _write_cr0(uint32_t);

#endif