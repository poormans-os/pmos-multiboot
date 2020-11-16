; /*A simple wrapper-file for the IDT*/
.intel_syntax noprefix

.global load_idt

load_idt:
    mov edx, [esp + 4]
    lidt [edx]
    sti
    ret
