.PHONY: all clean run bootloader

buildObj 	= @echo "\033[36m[Compiling]\033[0m $(if $(strip $(2)),$(2),$(1)).o" && $(CC) -c src/Kernel/$(1)/$(1).c -o build/$(if $(strip $(2)),$(2),$(1)).o $(CFLAGS)
buildLibObj	= @echo "\033[36m[Compiling]\033[0m $(if $(strip $(2)),$(2),$(1)).o" && $(CC) -c src/CLib/$(1)/$(1).c -o build/$(if $(strip $(2)),$(2),$(1)).o $(CFLAGS)
asmObj 		= @echo "\033[34m[Assembling]\033[0m $(1).o" && $(AS) $(ASFLAGS) -o build/$(1).o src/kernel/$(1)/$(1).asm

CC  		= clang-9
AS  		= nasm
ASFLAGS		= -felf64

CFLAGS := \
    -target amd64-unknown-elf \
    -mcmodel=kernel \
    -masm=intel \
    -Wall \
	-std=c11 \
    -ffreestanding \
    -nostdlib \
    -mno-red-zone \
    -fshort-wchar \
    -static \
    -O3 \
    -flto \
    -g \
	-I src/include

LDFLAGS := \
    --oformat elf_amd64 \
    --Bstatic \
    --nostdlib \
	-T src/Kernel/static/amd64.ld

OBJS 		+= stdio stdlib string tty kernel idt math io gdt paging#Compiler objects
OBJS	 	+= interrupts #Assembler objects
OBJFILES	= $(foreach OBJ,$(OBJS),build/$(OBJ).o)
TARGET		= bin/pmos.bin
BOOTLAODER  = bin/efi/boot/BOOTX64.EFI

all: $(TARGET)

remake: clean $(TARGET)

$(TARGET): build/ bin/ $(BOOTLAODER) $(OBJFILES)
	@echo "\033[32m[Linking]\033[0m The Project"
	@ld.lld-9 $(LDFLAGS) $(OBJFILES) -o $(TARGET)

bin/:
	@mkdir -p bin

build/:
	@mkdir -p build

$(BOOTLAODER): $(shell find bootloader/src/ -name '*.c')
	@cd bootloader && make --no-print-directory
	@cp bootloader/externals/zap-light16.psf bin/zap-light16.psf

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
build/interrupts.o: src/Kernel/interrupts/*.asm
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

bootloader:
	@echo "\033[33m[Cleaning up!]\033[0m"
	@cd bootloader && make --no-print-directory clean
	@cd bootloader && make --no-print-directory

clean:
	@echo "\033[33m[Cleaning up!]\033[0m"
	@cd bootloader && make --no-print-directory clean
	@rm -rf build
	@rm -rf bin

run: $(TARGET)
	@echo "\033[36m[Runing on qemu]\033[0m"
	@qemu-system-x86_64.exe -L externals -bios bootloader/externals/OVMF.fd -hdd fat:rw:bin
