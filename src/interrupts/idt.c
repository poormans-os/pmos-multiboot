#include "idt.h"

struct IDT_entry
{
    unsigned short int offset_lowerbits;
    unsigned short int selector;
    unsigned char zero;
    unsigned char type_attr;
    unsigned short int offset_higherbits;
};

struct IDT_entry IDT[256];

void idt_init(void)
{
    extern int load_idt();
    extern int irq0();
    extern int irq1();

    unsigned long irq0_address;
    unsigned long irq1_address;
    unsigned long idt_address;
    unsigned long idt_ptr[2];

    /* remapping the PIC */
    outb(0x20, 0x11);
    outb(0xA0, 0x11);
    outb(0x21, 0x20);
    outb(0xA1, 40);
    outb(0x21, 0x04);
    outb(0xA1, 0x02);
    outb(0x21, 0x01);
    outb(0xA1, 0x01);
    outb(0x21, 0x0);
    outb(0xA1, 0x0);

    irq0_address = (unsigned long)irq0;
    IDT[32].offset_lowerbits = irq0_address & 0xffff;
    IDT[32].selector = 0x08; /* KERNEL_CODE_SEGMENT_OFFSET */
    IDT[32].zero = 0;
    IDT[32].type_attr = 0x8e; /* INTERRUPT_GATE */
    IDT[32].offset_higherbits = (irq0_address & 0xffff0000) >> 16;

    irq1_address = (unsigned long)irq1;
    IDT[33].offset_lowerbits = irq1_address & 0xffff;
    IDT[33].selector = 0x08; /* KERNEL_CODE_SEGMENT_OFFSET */
    IDT[33].zero = 0;
    IDT[33].type_attr = 0x8e; /* INTERRUPT_GATE */
    IDT[33].offset_higherbits = (irq1_address & 0xffff0000) >> 16;

    /* fill the IDT descriptor */
    idt_address = (unsigned long)IDT;
    idt_ptr[0] = (sizeof(struct IDT_entry) * 256) + ((idt_address & 0xffff) << 16);
    idt_ptr[1] = idt_address >> 16;

    load_idt(idt_ptr);
}