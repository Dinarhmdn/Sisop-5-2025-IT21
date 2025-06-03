// #include "std_lib.h"

// int div(int a, int b)
// {
//   //TODO: Implementasi pembagian
//   //NOTE: HARUS BISA ANGKA NEGATIF
// }

// int mod(int a, int b)
// {
//   //TODO: Implementasi modulus
// }

// bool strcmp(char *str1, char *str2)
// {
//   //TODO: Implementasi perbandingan string
// }

// void strcpy(char *dst, char *src)
// {
//   //TODO: Implementasi penyalinan string
// }

// void clear(byte *buf, unsigned int size)
// {
//   //TODO: Implementasi pembersihan buffer
// }

// void atoi(char *str, int *num)
// {
//   //TODO: Implementasi konversi string ke integer
//   //NOTE: HARUS BISA ANGKA NEGATIF
// }

// void itoa(int num, char *str)
// {
//   //TODO: Implementasi konversi integer ke string
//   //NOTE: HARUS BISA ANGKA NEGATIF
// }

#include "std_lib.h"

int div(int a, int b)
{
  int quotient = 0;
  int sign = 1;
  if (b == 0) return 0; // avoid division by zero

  if (a < 0) {
    a = -a;
    sign = -sign;
  }

  if (b < 0) {
    b = -b;
    sign = -sign;
  }

  while (a >= b) {
    a -= b;
    quotient++;
  }

  return sign * quotient;
}

int mod(int a, int b)
{
  int sign = 1;
  if (b == 0) return 0;

  if (a < 0) {
    a = -a;
    sign = -1;
  }

  if (b < 0)
    b = -b;

  while (a >= b) {
    a -= b;
  }

  return sign * a;
}

bool strcmp(char *str1, char *str2)
{
  int i = 0;
  while (str1[i] != '\0' && str2[i] != '\0') {
    if (str1[i] != str2[i])
      return false;
    i++;
  }
  return str1[i] == str2[i];
}

void strcpy(char *dst, char *src)
{
  int i = 0;
  while (src[i] != '\0') {
    dst[i] = src[i];
    i++;
  }
  dst[i] = '\0';
}

void clear(byte *buf, unsigned int size)
{
  unsigned int i;
  for (i = 0; i < size; i++) {
    buf[i] = 0;
  }
}

void atoi(char *str, int *num)
{
  int i = 0;
  int result = 0;
  int sign = 1;

  if (str[0] == '-') {
    sign = -1;
    i++;
  }

  while (str[i] >= '0' && str[i] <= '9') {
    result = result * 10 + (str[i] - '0');
    i++;
  }

  *num = result * sign;
}

void itoa(int num, char *str)
{
  int i = 0,j;
  int isNegative = 0;
  char temp[16];
  int digit;

  if (num == 0) {
    str[0] = '0';
    str[1] = '\0';
    return;
  }

  if (num < 0) {
    isNegative = 1;
    num = -num;
  }

  while (num > 0) {
    digit = mod(num, 10);
    temp[i++] = digit + '0';
    num = div(num, 10);
  }

  if (isNegative) {
    temp[i++] = '-';
  }

  // reverse temp into str
  j = 0;
  while (i > 0) {
    str[j++] = temp[--i];
  }
  str[j] = '\0';
}
