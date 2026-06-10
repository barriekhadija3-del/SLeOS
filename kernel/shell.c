#include "../include/kernel.h"

/* ---- KEYBOARD INPUT ---- */
/* Read a byte from a port */
static inline unsigned char inb(unsigned short port) {
    unsigned char result;
    __asm__ volatile ("inb %1, %0" : "=a"(result) : "Nd"(port));
    return result;
}

/* Keyboard scancode to ASCII map */
static char scancode_map[] = {
    0, 0, '1','2','3','4','5','6','7','8','9','0','-','=',0,
    0,'q','w','e','r','t','y','u','i','o','p','[',']','\n',
    0,'a','s','d','f','g','h','j','k','l',';','\'','`',
    0,'\\','z','x','c','v','b','n','m',',','.','/',0,
    '*',0,' '
};

/* Read one character from keyboard */
char read_char() {
    unsigned char scancode;
    while (1) {
        /* Wait for a key press */
        if (inb(0x64) & 0x1) {
            scancode = inb(0x60);
            /* Only process key press (not release) */
            if (!(scancode & 0x80)) {
                if (scancode < sizeof(scancode_map)) {
                    char c = scancode_map[scancode];
                    if (c != 0) return c;
                }
            }
        }
    }
}

/* Read a full line of input */
void read_line(char* buffer, int max_len) {
    int i = 0;
    while (i < max_len - 1) {
        char c = read_char();
        if (c == '\n') {
            buffer[i] = '\0';
            print("\n");
            return;
        }
        buffer[i++] = c;
        /* Echo the character to screen */
        char tmp[2] = {c, '\0'};
        print(tmp);
    }
    buffer[i] = '\0';
}

/* ---- SHELL COMMANDS ---- */

void cmd_help() {
    print_color("\n--- SLeOS Available Commands ---\n", COLOR_CYAN_ON_BLACK);
    print("  help   - Show this help message\n");
    print("  ps     - List running processes\n");
    print("  mem    - Show memory information\n");
    print("  ls     - List files\n");
    print("  clear  - Clear the screen\n");
    print("  about  - About Sierra Leone OS\n");
    print("  sdg    - Show SDG goals we address\n");
    print("\n");
}

void cmd_about() {
    print_color("\n--- About SLeOS ---\n", COLOR_GREEN_ON_BLACK);
    print("Sierra Leone OS (SLeOS) v1.0\n");
    print("A minimal bootable OS built by Limkwing University students.\n");
    print("Designed to address local computing challenges in Sierra Leone:\n");
    print("  - Low-resource computing environments\n");
    print("  - Education access in remote areas\n");
    print("  - Digital inclusion for all citizens\n");
    print("Tools used: QEMU, NASM, GCC (all open-source)\n");
    print("\n");
}

void cmd_sdg() {
    print_color("\n--- SDG Goals Addressed by SLeOS ---\n", COLOR_CYAN_ON_BLACK);
    print("SDG 4  - Quality Education:\n");
    print("         Provides free OS tools for students\n");
    print("SDG 9  - Industry & Innovation:\n");
    print("         Builds local tech innovation capacity\n");
    print("SDG 10 - Reduced Inequalities:\n");
    print("         Enables computing on low-resource hardware\n");
    print("\n");
}

void cmd_ps() {
    print_color("\n--- Running Processes ---\n", COLOR_GREEN_ON_BLACK);
    print("PID   NAME              STATE\n");
    print("----  ----------------  -------\n");
    print("1     kernel_main       running\n");
    print("2     shell             running\n");
    print("3     memory_manager    waiting\n");
    print("4     idle              waiting\n");
    print("\n");
    print("Scheduler: Round-Robin (time slice = 10ms)\n");
    print("\n");
}

void cmd_mem() {
    print_color("\n--- Memory Information ---\n", COLOR_GREEN_ON_BLACK);
    print("Total Memory    : 32 MB (simulated)\n");
    print("Kernel Usage    : 1 MB  (0x00000 - 0xFFFFF)\n");
    print("Free Memory     : 31 MB (0x100000 - 0x1FFFFFF)\n");
    print("\n");
    print("Memory Map:\n");
    print("  [0x00000 - 0x003FF]  BIOS Interrupt Vector\n");
    print("  [0x00400 - 0x004FF]  BIOS Data Area\n");
    print("  [0x07C00 - 0x07DFF]  Bootloader\n");
    print("  [0x100000 - ......]  SLeOS Kernel\n");
    print("\n");
}

void cmd_ls() {
    print_color("\n--- File System (In-Memory) ---\n", COLOR_GREEN_ON_BLACK);
    print("NAME              SIZE    TYPE\n");
    print("----------------  ------  ------\n");
    print("kernel.bin        128KB   system\n");
    print("readme.txt        2KB     text\n");
    print("sleos.cfg         1KB     config\n");
    print("about.txt         1KB     text\n");
    print("\n");
    print("4 files | Total: 132KB used\n");
    print("\n");
}

void cmd_unknown(char* cmd) {
    print("Unknown command: '");
    print(cmd);
    print("'\nType 'help' to see available commands.\n\n");
}

/* ---- MAIN SHELL LOOP ---- */
void shell_run() {
    char input[64];

    print_color("Shell ready! Type 'help' to get started.\n\n", COLOR_GREEN_ON_BLACK);

    while (1) {
        print_color("SLeOS> ", COLOR_CYAN_ON_BLACK);
        read_line(input, 64);

        if (strcmp(input, "help")  == 0) cmd_help();
        else if (strcmp(input, "ps")    == 0) cmd_ps();
        else if (strcmp(input, "mem")   == 0) cmd_mem();
        else if (strcmp(input, "ls")    == 0) cmd_ls();
        else if (strcmp(input, "about") == 0) cmd_about();
        else if (strcmp(input, "sdg")   == 0) cmd_sdg();
        else if (strcmp(input, "clear") == 0) clear_screen();
        else if (strlen(input) > 0)           cmd_unknown(input);
    }
}