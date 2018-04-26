objs = bootpack.o func.o graphic.o font.o

img = sys.img

CC = gcc
CFLAGS = -m32 -nostdlib
LD = ld
LDFLAGS = -m elf_i386
AS = as
ASFLAGS = --32

$(img): ipl.bin head.bin bootpack.bin 
	cat head.bin bootpack.bin > sys.bin
	mformat -f 1440 -C -B ipl.bin -i $@
	mcopy sys.bin -i $@ ::

bootpack.bin: $(objs) bootpack.ld
	$(LD) -v $(LDFLAGS) -Map bootpack.map -T bootpack.ld -o $@ $(objs)

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $*.c

%.bin: %.s %.ld
	$(AS) $(ASFLAGS) -o $*.o $*.s
	$(LD) $(LDFLAGS) -T $*.ld -o $@ $*.o

func.o: func.s
	$(AS) $(ASFLAGS) --32 -o $@ $*.s

font.c: hankaku.txt
	./make_font.py hankaku.txt > $@

run: $(img)
	qemu-system-i386 -fda $(img) -monitor stdio

.PHONY: clean
clean:
	rm *.o *.img *.bin font.c *.map *.hrb *.a

