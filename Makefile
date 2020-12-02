.PHONY: all clean run iso

buildObj 	= @echo "\033[36m[Compiling]\033[0m $(if $(strip $(2)),$(2),$(1)).o" && $(CC) -c src/Kernel/$(1)/$(1).c -o build/$(if $(strip $(2)),$(2),$(1)).o $(CFLAGS)
buildLibObj	= @echo "\033[36m[Compiling]\033[0m $(if $(strip $(2)),$(2),$(1)).o" && $(CC) -c src/CLib/$(1)/$(1).c -o build/$(if $(strip $(2)),$(2),$(1)).o $(CFLAGS)
asmObj 		= @echo "\033[34m[Assembling]\033[0m $(1).o" && $(AS) $(ASFLAGS) $(ARCH_FLAGS) -o build/$(1).o src/kernel/$(1)/$(1).s

ARCH=i386
ARCH_FLAGS=-march=$(ARCH)

CC  		= clang-9
AS  		= as
CFLAGS		= $(ARCH_FLAGS) -m32 -W -Wall -O0 -std=c18 -fomit-frame-pointer -nodefaultlibs -nostdlib -finline-functions -fno-builtin -Isrc/include/
ASFLAGS		= --32
LDFLAGS		= -m elf_$(ARCH)
OBJS 		+= stdio stdlib string tty kernel idt math io gdt paging#Compiler objects
OBJS	 	+= boot interrupts mmu #Assembler objects
OBJFILES	= $(foreach OBJ,$(OBJS),build/$(OBJ).o)
TARGET		= bin/pmos.bin

all: $(TARGET)

remake: clean $(TARGET)

$(TARGET): build/ bin/ $(OBJFILES)
	@echo "\033[32m[Linking]\033[0m The Project"
	@ld $(LDFLAGS) -T src/Kernel/static/linker.ld $(OBJFILES) -o $(TARGET)

bin/:
	@mkdir -p bin

build/:
	@mkdir -p build

build/kernel.o: src/Kernel/kernel.c
	@echo "\033[36m[Compiling]\033[0m kernel.o"
	@$(CC) -c src/kernel/kernel.c -o build/kernel.o $(CFLAGS)

build/gdt.o: src/Kernel/gdt.c
	@echo "\033[36m[Compiling]\033[0m gdt.o"
	@$(CC) -c src/kernel/gdt.c -o build/gdt.o $(CFLAGS)

build/boot.o: src/kernel/boot.s
	@echo "\033[34m[Assembling]\033[0m boot.o"
	@$(AS) $(ASFLAGS) src/kernel/boot.s -o build/boot.o

# FIXME - Renaming
build/interrupts.o: src/Kernel/interrupts/*.s
	$(call asmObj,interrupts)

# FIXME - Renaming
build/idt.o: src/Kernel/interrupts/*.c
	$(call buildObj,interrupts,idt)

build/io.o: src/Kernel/io/*.c
	$(call buildObj,io)

build/paging.o: src/Kernel/mmu/*.c
	@echo "\033[36m[Compiling]\033[0m paging.o"
	@$(CC) -c src/kernel/mmu/paging.c -o build/paging.o $(CFLAGS)

build/mmu.o: src/Kernel/mmu/*.s
	@echo "\033[34m[Assembling]\033[0m mmu.o"
	@$(AS) $(ASFLAGS) src/kernel/mmu/paging.s -o build/mmu.o

build/tty.o: src/Kernel/tty/*.c
	$(call buildObj,tty)

build/stdio.o: src/CLib/stdio/*.c
	$(call buildLibObj,stdio)

build/math.o: src/CLib/math/*.c
	$(call buildLibObj,math)

build/stdlib.o: src/CLib/stdlib/*.c
	$(call buildLibObj,stdlib)

build/string.o: src/CLib/string/*.c
	$(call buildLibObj,string)

clean:
	@echo "\033[33m[Cleaning up!]\033[0m"
	@rm -rf build
	@rm -rf bin

run: $(TARGET)
	@echo "\033[36m[Runing on qemu]\033[0m"
	@qemu-system-i386 -kernel $(TARGET)

iso: $(TARGET)
	@echo "\033[36m[Runing on qemu ISO]\033[0m"
	@mkdir -p bin/iso/boot/grub
	@cp src/Kernel/static/grub.cfg bin/iso/boot/grub/grub.cfg
	@cp bin/pmos.bin bin/iso/boot/pmos.bin
	@grub-mkrescue -o bin/pmos.iso bin/iso
	@qemu-system-i386 -cdrom bin/pmos.iso
