#include <egx/egx.h>

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

static void EgxBackend_IMG_Ext__WriteInt(EgxBackend_IMG_IO_Ext* io, void* fp, EGX_SZ k)
{
    if(k < 0) { io->write1_file(fp, '-'); k = -k; }
    if(k > 9) EgxBackend_IMG_Ext__WriteInt(io, fp, k/10);
    io->write1_file(fp, '0' + (k % 10));
}

static void EgxBackend_IMG_Ext__render(EgxBackend* b)
{
    EgxBackend_IMG_Ext* bb = (EgxBackend_IMG_Ext*)b;
    EgxWindow* w = b->bound;
    EgxFrame *f = w->frame;
    void* fp = bb->io->open_file("out.ppm");

    bb->io->writeN_file(fp, "P6 ", 3);
    EgxBackend_IMG_Ext__WriteInt(bb->io, fp, f->width);
    bb->io->write1_file(fp, ' ');
    EgxBackend_IMG_Ext__WriteInt(bb->io, fp, f->height);
    bb->io->write1_file(fp, ' ');
    EgxBackend_IMG_Ext__WriteInt(bb->io, fp, 255);
    bb->io->write1_file(fp, '\n');
    
    for(EGX_SZ y = 0; y < f->height; ++y)
        for(EGX_SZ x = 0; x < f->width; ++x)
        {
            Egx_RGB_Ext rgb = EgxBackend_IMG_Ext__RGB_From_8_3x3x2(f->buffer[y * f->width + x]);
            bb->io->writeN_file(fp, &rgb, sizeof(Egx_RGB_Ext));
        }
    
    bb->io->close_file(fp);
}

void EgxBackend_IMG_Ext_Init(EgxBackend_IMG_Ext* self, EgxWindow* window, EgxBackend_IMG_IO_Ext* io)
{
    self->base.render = &EgxBackend_IMG_Ext__render;
    self->base.bound = window;
    self->io = io;
    self->base.single = EGX_TRUE;
}

