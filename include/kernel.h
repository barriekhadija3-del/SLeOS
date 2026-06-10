#ifndef KERNEL_H
#define KERNEL_H

/* VGA Text Mode Address */
#define VGA_ADDRESS 0xB8000
#define VGA_WIDTH   80
#define VGA_HEIGHT  25

/* Colors */
#define COLOR_WHITE_ON_BLACK  0x07
#define COLOR_GREEN_ON_BLACK  0x02
#define COLOR_CYAN_ON_BLACK   0x03

/* Function declarations */
void clear_screen();
void print(const char* str);
void print_color(const char* str, unsigned char color);
void newline();
void kernel_main();
void shell_run();

/* String utilities */
int strcmp(const char* a, const char* b);
int strlen(const char* str);
void strcpy(char* dest, const char* src);

#endif