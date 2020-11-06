.intel_syntax noprefix

.global load_idt

.global irq0
.global irq0_handler
.extern irq0_handler

irq0:
  pusha
  call irq0_handler
  popa
  iret

load_idt:
    mov edx, [esp + 4]
    lidt [edx]
    sti
    ret
