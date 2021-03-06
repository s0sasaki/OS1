#include "bootpack.h"

void putfont8(char *vram, int xsize, int x, int y, char c, char *font) {
  int i;
  char *p, d;
  for (i = 0; i < 16; i++) {
    p = vram + (y + i) * xsize + x;
    d = font[i];
    if ((d & 0x80) != 0)   p[0] = c;
    if ((d & 0x40) != 0)   p[1] = c;
    if ((d & 0x20) != 0)   p[2] = c;
    if ((d & 0x10) != 0)   p[3] = c;
    if ((d & 0x08) != 0)   p[4] = c;
    if ((d & 0x04) != 0)   p[5] = c;
    if ((d & 0x02) != 0)   p[6] = c;
    if ((d & 0x01) != 0)   p[7] = c;
  }
  return;
}

void putfonts8_asc(char *vram, int xsize, int x, int y, char c, unsigned char *s){
    extern char hankaku[4096];
    for(; *s != 0x00; s++){
        putfont8(vram, xsize, x, y, c, hankaku + *s * 16);
        x += 8;
    }
}

void putfonts8_dec(char *vram, int xsize, int x, int y, char c, unsigned int n){
    extern char hankaku[4096];
    int inverse_stack[32];
    int i;
    for(i = 0; n != 0; i++){
        inverse_stack[i] = n%10;
        n /= 10;
    }
    if(i==0){
        inverse_stack[0] = 0;
        i = 1;
    }
    for(i--; i >= 0; i--){
        putfont8(vram, xsize, x, y, c, hankaku + (inverse_stack[i] + '0') * 16);
        x += 8;
    }
}

void putfonts8_hex(char *vram, int xsize, int x, int y, char c, unsigned int n){
    extern char hankaku[4096];
    int inverse_stack[32];
    int i;
    for(i = 0; n != 0; i++){
        inverse_stack[i] = n%16;
        n /= 16;
    }
    if(i==0){
        inverse_stack[0] = 0;
        i = 1;
    }
    putfonts8_asc(vram, xsize, x, y, c, "0x");
    x += 16;
    for(i--; i >= 0; i--){
        if(inverse_stack[i] < 10)
            putfont8(vram, xsize, x, y, c, hankaku + (inverse_stack[i] + '0') * 16);
        else
            putfont8(vram, xsize, x, y, c, hankaku + (inverse_stack[i] + 'A' - 10) * 16);
        x += 8;
    }
}

