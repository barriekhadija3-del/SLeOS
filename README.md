\# Sierra Leone OS (SLeOS)



A minimal bootable operating system prototype built by Limkwing University students.



\## About

SLeOS is a custom OS kernel built from scratch using C and Assembly,

emulated via QEMU. It addresses local computing challenges in Sierra Leone

such as low-resource computing, education access, and digital inclusion.



\## Features

\- Custom bootloader written in Assembly

\- Kernel written in C

\- Interactive shell with commands

\- Process Scheduler (FCFS + Round-Robin)

\- Memory Manager with memory map

\- Simple in-memory File System



\## Commands

\- `help`  - Show available commands

\- `ps`    - List running processes

\- `mem`   - Show memory information

\- `ls`    - List files

\- `about` - About SLeOS

\- `sdg`   - Show SDG goals addressed

\- `clear` - Clear the screen



\## Tools Used

\- QEMU (emulator)

\- NASM (assembler)

\- GCC (compiler)

\- GNU LD (linker)

\- GRUB (bootloader)



\## How to Build

```bash

nasm -f elf32 boot/boot.asm -o boot/boot.o

gcc -m32 -ffreestanding -fno-stack-protector -nostdlib -nostdinc -fno-builtin -Wall -c kernel/kernel.c -o kernel/kernel.o

gcc -m32 -ffreestanding -fno-stack-protector -nostdlib -nostdinc -fno-builtin -Wall -c kernel/shell.c -o kernel/shell.o

ld -m elf\_i386 -T linker.ld -o sleos.bin boot/boot.o kernel/kernel.o kernel/shell.o

```



\## How to Run

```bash

qemu-system-x86\_64 -cdrom sleos.iso

```



\## SDG Goals Addressed

\- SDG 4  - Quality Education

\- SDG 9  - Industry and Innovation

\- SDG 10 - Reduced Inequalities



\## License

MIT License - see LICENSE file



\## Author

Billoh Gassama - Limkwing University of Creative Technology

