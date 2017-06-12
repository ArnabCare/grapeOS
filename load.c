unsigned char *VGA = (unsigned char *)0xA0000000L;
unsigned char *dbl_buffer;

typedef struct tagBITMAP              /* the structure for a bitmap. */
{
    unsigned int width;
    unsigned int height;
    unsigned char *data;
} BITMAP;

typedef struct tagRECT
{
    long x1;
    long y1;
    long x2;
    long y2;
} RECT;

void init_dbl_buffer(void)
{
    dbl_buffer = (unsigned char *) malloc (SCREEN_WIDTH * SCREEN_HEIGHT);
    if (dbl_buffer == NULL)
    {
	printf("Not enough memory for double buffer.\n");
	getch();
	exit(1);
    }
}

void update_screen(void)
{
    #ifdef VERTICAL_RETRACE
      while ((inportb(0x3DA) & 0x08));
      while (!(inportb(0x3DA) & 0x08));
    #endif
    memcpy(VGA, dbl_buffer, (unsigned int)(SCREEN_WIDTH * SCREEN_HEIGHT));
}

void setpixel (BITMAP *bmp, int x, int y, unsigned char color)
{
    bmp->data[y * bmp->width + x];
}

/* Draws a filled in rectangle IN A BITMAP. To fill a full bitmap call as
drawrect (&bmp, 0, 0, bmp.width, bmp.height, color); */
void drawrect(BITMAP *bmp, unsigned short x, unsigned short y,
                     unsigned short x2, unsigned short y2,
                     unsigned char color)
{
    unsigned short tx, ty;
    for (ty = y; ty height; j++)
    {
	memcpy(&dbl_buffer[screen_offset], &bmp->data[bitmap_offset], bmp->width);

	bitmap_offset += bmp->width;
	screen_offset += SCREEN_WIDTH;
    }
}

void main()
{
    unsigned char key;
    do
    {
        key = 0;
        if (kbhit()) key = getch();

        /* You must clear the double buffer every time to avoid evil messes
            (go ahead and try without this, you will see) */
        memset (dbl_buffer, 0, SCREEN_WIDTH * SCREEN_HEIGHT);

        /* DRAW ALL BITMAPS AND DO GUI CODE HERE */

        /* Draws the double buffer */
        update_screen();

    } while (key != 27);	/* keep going until escape */
}
