#include "bootpack.h"

void Main(void){
    struct BOOTINFO *binfo = (struct BOOTINFO *)ADR_BOOTINFO;
    putfonts8_asc(binfo->vram, binfo->scrnx, 8, 8, COL8_FFFFFF, "ABC 123");
    io_hlt();
}

