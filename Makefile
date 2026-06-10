# SLeOS Build System
# Sierra Leone OS - Limkwing University

CC = gcc
AS = nasm
LD = ld

CFLAGS  = -m32 -ffreestanding -fno-stack-protector -nostdlib -nostdinc -fno-builtin -Wall
ASFLAGS = -f elf32
LDFLAGS = -m elf_i386 -T linker.ld

# All object files
OBJS = boot/boot.o kernel/kernel.o kernel/shell.o

# Final output
TARGET = sleos.bin

all: $(TARGET)

# Link everything into final binary
$(TARGET): $(OBJS)
	$(LD) $(LDFLAGS) -o $(TARGET) $(OBJS)
	@echo ">>> SLeOS kernel built successfully!"

# Compile bootloader
boot/boot.o: boot/boot.asm
	$(AS) $(ASFLAGS) boot/boot.asm -o boot/boot.o

# Compile kernel
kernel/kernel.o: kernel/kernel.c
	$(CC) $(CFLAGS) -c kernel/kernel.c -o kernel/kernel.o

# Compile shell
kernel/shell.o: kernel/shell.c
	$(CC) $(CFLAGS) -c kernel/shell.c -o kernel/shell.o

# Run in QEMU
run: $(TARGET)
	qemu-system-x86_64 -drive file=$(TARGET),format=raw

# Clean build files
clean:
	del /Q boot\boot.o kernel\kernel.o kernel\shell.o $(TARGET) 2>nul
	@echo ">>> Cleaned build files"