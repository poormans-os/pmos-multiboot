/*A simple wrapper-file for the interrupts*/
.intel_syntax noprefix

.global load_idt

.global irq0
.global irq1

.global irq0_handler
.global irq1_handler

.extern irq0_handler
.extern irq1_handler

irq0:
  pusha
  call irq0_handler
  popa
  iret

irq1:
  pusha
  call irq1_handler
  popa
  iret


load_idt:
    mov edx, [esp + 4]
    lidt [edx]
    sti
    ret
