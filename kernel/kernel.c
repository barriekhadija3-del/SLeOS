#include "../include/kernel.h"

/* VGA buffer pointer */
static unsigned short* vga = (unsigned short*)VGA_ADDRESS;
static int cursor_x = 0;
static int cursor_y = 0;

/* Clear the entire screen */
void clear_screen() {
    for (int i = 0; i < VGA_WIDTH * VGA_HEIGHT; i++) {
        vga[i] = (COLOR_WHITE_ON_BLACK << 8) | ' ';
    }
    cursor_x = 0;
    cursor_y = 0;
}

/* Print a single character */
void putchar(char c) {
    if (c == '\n') {
        cursor_x = 0;
        cursor_y++;
        return;
    }
    int index = cursor_y * VGA_WIDTH + cursor_x;
    vga[index] = (COLOR_WHITE_ON_BLACK << 8) | c;
    cursor_x++;
    if (cursor_x >= VGA_WIDTH) {
        cursor_x = 0;
        cursor_y++;
    }
}

/* Print a colored character */
void putchar_color(char c, unsigned char color) {
    if (c == '\n') {
        cursor_x = 0;
        cursor_y++;
        return;
    }
    int index = cursor_y * VGA_WIDTH + cursor_x;
    vga[index] = (color << 8) | c;
    cursor_x++;
    if (cursor_x >= VGA_WIDTH) {
        cursor_x = 0;
        cursor_y++;
    }
}

/* Print a string */
void print(const char* str) {
    while (*str) {
        putchar(*str++);
    }
}

/* Print a colored string */
void print_color(const char* str, unsigned char color) {
    while (*str) {
        putchar_color(*str++, color);
    }
}

/* New line */
void newline() {
    cursor_x = 0;
    cursor_y++;
}

/* String compare */
int strcmp(const char* a, const char* b) {
    while (*a && *b && *a == *b) { a++; b++; }
    return *a - *b;
}

/* String length */
int strlen(const char* str) {
    int len = 0;
    while (*str++) len++;
    return len;
}

/* String copy */
void strcpy(char* dest, const char* src) {
    while ((*dest++ = *src++));
}

/* ---- KERNEL MAIN ENTRY POINT ---- */
void kernel_main() {
    clear_screen();

    print_color("========================================\n", COLOR_CYAN_ON_BLACK);
    print_color("   Welcome to Sierra Leone OS (SLeOS)  \n", COLOR_GREEN_ON_BLACK);
    print_color("   Built by Limkwing Students - 2026   \n", COLOR_GREEN_ON_BLACK);
    print_color("   Addressing Local Computing Challenges\n", COLOR_CYAN_ON_BLACK);
    print_color("========================================\n", COLOR_CYAN_ON_BLACK);
    print("\n");
    print("SLeOS is booting...\n");
    print("Initializing kernel components...\n");
    print("\n");

    shell_run();
}