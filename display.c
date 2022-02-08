#include "egx.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static void EgxBackend_TTY_Ext__render(EgxBackend* b)
{
    EgxFrame* frame = b->bound->frame;

    for(EGX_SZ x = 0; x < frame->width; ++x)
        putc('-', stdout);
    putc('\n', stdout);
    
    for(EGX_SZ y = 0; y < frame->height; ++y)
    {
        for(EGX_SZ x = 0; x < frame->width; ++x)
        {
            EGX_BYTE p = frame->buffer[x + y * frame->width];
            /**/ if(p == 0x80) putc('*', stdout);
            else if(p > 128)   putc('#', stdout);
            else               putc(' ', stdout);
        }
        putc('\n', stdout);
    }

    for(EGX_SZ x = 0; x < frame->width; ++x)
        putc('-', stdout);
    putc('\n', stdout);
}

static EGX_SZ EgxImpl_Ext__strlen(const char* s)
{
    EGX_SZ i = 0;
    for(; *s; ++s) i += 1;
    return i;
}

Egx_RGB_Ext EgxBackend_IMG_Ext__RGB_From_8_3x3x2(EGX_BYTE c)
{
    return (Egx_RGB_Ext){
        32 * ((c & 0b11100000) >> 5),
        32 * ((c & 0b00011100) >> 2),
        64 * ((c & 0b00000011) >> 0) };
}

static void EgxBackend_IMG_Ext__render(EgxBackend* b)
{

    EgxWindow* w = b->bound;
    EgxFrame *f = w->frame;
    FILE* fp = fopen("out.ppm", "wb");
    /* write header to the file */
    fprintf(fp, "P6 %d %d %d\n", f->width, f->height, 255);
    
    for(EGX_SZ y = 0; y < f->height; ++y)
        for(EGX_SZ x = 0; x < f->width; ++x)
        {
            Egx_RGB_Ext rgba = EgxBackend_IMG_Ext__RGB_From_8_3x3x2(f->buffer[y * f->width + x]);
            fwrite(&rgba, sizeof(Egx_RGB_Ext), 1, fp);
        }
    
    fclose(fp);
}

void EgxBackend_IMG_Ext_Init(EgxBackend* self, EgxWindow* window)
{
    self->render = &EgxBackend_IMG_Ext__render;
    self->bound = window;
    self->single = EGX_TRUE;
}
