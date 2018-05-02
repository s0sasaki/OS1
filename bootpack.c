#include "param.h"
#include "text.h"
#include "proc.h"
#include "file.h"
#include "user.h"
#include "malloc.h"
#include "systm.h"
#include "bootpack.h"

void Main(void)
{
    struct BOOTINFO *binfo = (struct BOOTINFO *)ADR_BOOTINFO;
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
    mfree(coremap, 0x40000, (void *)0x00320000);
    p = smalloc(coremap, 8);
    q = smalloc(coremap, 64);
    putfonts8_hex(binfo->vram, binfo->scrnx, 8, 8+32*8, COL8_FFFFFF, p);
    putfonts8_hex(binfo->vram, binfo->scrnx, 8, 8+32*9, COL8_FFFFFF, q);

    for(i=0; i<10000; i++)
        copyseg(binfo->vram+i+640*8, binfo->vram+i+40000);
    
	/*
	 * set up system process
	 */
	proc[0].p_addr = (void *)0x00300000;
	proc[0].p_size = 0x20000;
	proc[0].p_stat = SRUN;
	proc[0].p_flag |= SLOAD|SSYS;
	u.u_procp = &proc[0];

    i = fork();
    putfonts8_dec(binfo->vram, binfo->scrnx, 8, 8+32*10, COL8_FFFFFF, i);

    sleep();

    io_hlt();
}


