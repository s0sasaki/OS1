
#include "bootpack.h"

void panic(char *s)
{
    struct BOOTINFO *binfo = (struct BOOTINFO *)ADR_BOOTINFO;
    putfonts8_asc(binfo->vram, binfo->scrnx, 0, 0, COL8_FFFFFF, s);
    io_hlt();
}


