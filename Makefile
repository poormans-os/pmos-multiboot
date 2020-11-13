include GCC_PATH

.PHONY: all clean run

buildObj 	= @echo "\033[36m[Compiling]\033[0m $(if $(strip $(2)),$(2),$(1)).o" && $(CC) -c src/Kernel/$(1)/$(1).c -o build/$(if $(strip $(2)),$(2),$(1)).o $(CFLAGS)
buildLibObj	= @echo "\033[36m[Compiling]\033[0m $(if $(strip $(2)),$(2),$(1)).o" && $(CC) -c src/CLib/$(1)/$(1).c -o build/$(if $(strip $(2)),$(2),$(1)).o $(CFLAGS)
asmObj 		= @echo "\033[34m[Assembling]\033[0m $(1).o" && $(AS) src/kernel/$(1)/$(1).s -o build/$(1).o

CC			= $(CUSTOM_GCC)/bin/i686-elf-gcc
AS			= $(CUSTOM_GCC)/bin/i686-elf-as
CFLAGS		= -ffreestanding -O2 -Wall -Wextra -std=c18 -Isrc/include
LDFLAGS		= -ffreestanding -O2 -nostdlib -lgcc
OBJS 		+= stdio stdlib string tty kernel idt math io #Compiler objects
OBJS	 	+= boot interrupts #Assembler objects
OBJFILES	= $(foreach OBJ,$(OBJS),build/$(OBJ).o)
TARGET		= bin/pmos.bin

all: $(TARGET)

$(TARGET): build/ bin/ $(OBJFILES)
	@echo "\033[32m[Linking]\033[0m The Project"
	@$(CC) -T src/Kernel/static/linker.ld $(OBJFILES) $(LDFLAGS) -o $(TARGET)

bin/:
	@mkdir -p bin

build/:
	@mkdir -p build

build/kernel.o: src/Kernel/kernel.c
	@echo "\033[36m[Compiling]\033[0m kernel.o"
	@$(CC) -c src/kernel/kernel.c -o build/kernel.o $(CFLAGS)

build/boot.o: src/kernel/boot.s
	@echo "\033[34m[Assembling]\033[0m boot.o"
	@$(AS) src/kernel/boot.s -o build/boot.o

# FIXME - Renaming
build/interrupts.o: src/Kernel/interrupts/*.s
	$(call asmObj,interrupts)

# FIXME - Renaming
build/idt.o: src/Kernel/interrupts/*.c
	$(call buildObj,interrupts,idt)

build/io.o: src/Kernel/io/*.c
	$(call buildObj,io)

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
