#include "shell.h"
#include "kernel.h"

// Fungsi dari kernel.asm
extern int interrupt(int number, int AX, int BX, int CX, int DX);
extern void putInMemory(int segment, int address, char character);
extern unsigned int getBiosTick();

int main() {
  clearScreen();
  shell();
  return 0;
}

void printString(char *str)
{
  while (*str != '\0') {
    interrupt(0x10, 0x0E00 + *str, 0, 0, 0); // Layanan BIOS: TTY output (int 0x10, AH=0x0E)
    str++;
  }
}

void readString(char *buf)
{
  int i = 0;
  char c = 0;
  char str[2];

  while (1) {
    c = interrupt(0x16, 0x0000, 0, 0, 0); // Layanan BIOS: Keyboard input (int 0x16, AH=0x00)
    if (c == '\r') { // Enter key
      buf[i] = '\0';
      printString("\r\n"); // Pindah baris
      break;
    } else if (c == '\b') { // Backspace
      if (i > 0) {
        i--;
        printString("\b \b"); // Hapus karakter dari layar
      }
    } else {
      buf[i++] = c;
      str[0]=c;
      str[1]='\0';
      printString(str);
    }
  }
}

void clearScreen()
{
  int i;
  for (i = 0; i < 80 * 25; i++) {
    putInMemory(0xB800, i * 2, ' ');     // karakter spasi
    putInMemory(0xB800, i * 2 + 1, 0x07); // atribut warna (abu-abu terang dengan latar belakang hitam)
  }

  // Atur kursor kembali ke kiri atas (0,0)
  interrupt(0x10, 0x0200, 0, 0, 0); // AH=0x02, DL=kolom=0, DH=baris=0
}
