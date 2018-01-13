//written by eric wills, cis314, UO

#include <stdio.h>

int main() {
  // Code to transform from 32-bit ARGB colors to 32-bit RGBA colors. 
  unsigned int x = 0xFFAA2211;

  printf("AARRGGBB: 0x%X\n", x);

  // AARRGGBB to 000000AA
  unsigned int a = x >> 24;

  // Use %08X to print 8 hex characters, even though only 2 are
  // significant.
  printf("000000AA: 0x%08X\n", a);

  // AARRGGBB to RRGGBB00
  unsigned int rgbx = x << 8;

  printf("RRGGBB00: 0x%X\n", rgbx);

  // RRGGBB00 | 000000AA to RRGGBBAA
  unsigned int rgba = rgbx | a;

  printf("RRGGBBAA: 0x%X\n", rgba);
}
