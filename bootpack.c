#include "bootpack.h"

void Main(void){
    struct BOOTINFO *binfo = (struct BOOTINFO *)ADR_BOOTINFO;
    putfonts8_asc(binfo->vram, binfo->scrnx, 8, 8, COL8_FFFFFF, "ABC 123");
    putfonts8_dec(binfo->vram, binfo->scrnx, 8, 32, COL8_FFFFFF, 12345);
    putfonts8_dec(binfo->vram, binfo->scrnx, 8, 64, COL8_FFFFFF, 0);
    putfonts8_dec(binfo->vram, binfo->scrnx, 8, 96, COL8_FFFFFF, binfo->scrnx);
    putfonts8_hex(binfo->vram, binfo->scrnx, 8, 128, COL8_FFFFFF, Main);
    putfonts8_hex(binfo->vram, binfo->scrnx, 8, 160, COL8_FFFFFF, 0x12ab);
    io_hlt();
}

