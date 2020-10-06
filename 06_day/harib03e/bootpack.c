#include "bootpack.h"
// #include <stdio.h>

extern void sprintf(char *str, char *fmt, ...);

void HariMain(void)
{
	struct BOOTINFO *binfo = (struct BOOTINFO *) ADR_BOOTINFO;
	char s[40], mcursor[256];
	int mx, my;

	// init_gdtidt();
	// init_pic();
	// io_sti(); /* IDT/PIC */

	// 调色板
	init_palette();
	init_screen8(binfo->vram, binfo->scrnx, binfo->scrny);
	mx = (binfo->scrnx - 16) / 2; /* */
	my = (binfo->scrny - 28 - 16) / 2;
	init_mouse_cursor8(mcursor, COL8_008484);
	putblock8_8(binfo->vram, binfo->scrnx, 16, 16, mx, my, mcursor, 16);
	sprintf(s, "(%d, %d)", mx, my);
	putfonts8_asc(binfo->vram, binfo->scrnx, 0, 0, COL8_FFFFFF, s);

	io_out8(PIC0_IMR, 0xf9); /* PIC (11111001) */
	io_out8(PIC1_IMR, 0xef); /* 11101111) */

	for (;;) {
		io_hlt();
	}
}
