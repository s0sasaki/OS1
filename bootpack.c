#include "param.h"
#include "malloc.h"
#include "bootpack.h"

void Main(void)
{
    struct BOOTINFO *binfo = (struct BOOTINFO *)ADR_BOOTINFO;
    struct map coremap[CMAPSIZ];
    int a = 7;
    int b = 7;
    putfonts8_asc(binfo->vram, binfo->scrnx, 8, 8+32*0, COL8_FFFFFF, "ABC 123");
    putfonts8_dec(binfo->vram, binfo->scrnx, 8, 8+32*1, COL8_FFFFFF, 12345);
    putfonts8_dec(binfo->vram, binfo->scrnx, 8, 8+32*2, COL8_FFFFFF, 0);
    putfonts8_dec(binfo->vram, binfo->scrnx, 8, 8+32*3, COL8_FFFFFF, binfo->scrnx);
    putfonts8_hex(binfo->vram, binfo->scrnx, 8, 8+32*4, COL8_FFFFFF, 0x12ab);
    putfonts8_hex(binfo->vram, binfo->scrnx, 8, 8+32*5, COL8_FFFFFF, Main);
    putfonts8_hex(binfo->vram, binfo->scrnx, 8, 8+32*6, COL8_FFFFFF, &a);
    putfonts8_hex(binfo->vram, binfo->scrnx, 8, 8+32*7, COL8_FFFFFF, &b);

    void *p, *q;
    int i;
    for(i=0; i<100; i++)
        mfree(coremap, 64, (void *)0x00320000 + i * 64);
    p = smalloc(coremap, 8);
    q = smalloc(coremap, 64);
    putfonts8_hex(binfo->vram, binfo->scrnx, 8, 8+32*8, COL8_FFFFFF, p);
    putfonts8_hex(binfo->vram, binfo->scrnx, 8, 8+32*9, COL8_FFFFFF, q);

    i = fork();
    putfonts8_dec(binfo->vram, binfo->scrnx, 8, 8+32*10, COL8_FFFFFF, i);

    sleep();

    io_hlt();
}


