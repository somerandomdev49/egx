#include "egx.h"

void EgxFrame_Init(EgxFrame* self, EGX_SZ w, EGX_SZ h, EGX_BYTE* buf)
{
    self->buffer = buf;
    self->width = w;
    self->height = h;
}

void EgxCanvas_Init(EgxCanvas* self, EgxWindow* target)
{
    self->target = target;
}

void EgxCanvas_DeInit(EgxCanvas* self) {}


void EgxWindow_Init(EgxWindow* self, EgxFrame* frame)
{
    self->frame = frame;
    EgxCanvas_Init(&self->canvas, self);
}

void EgxWindow_DeInit(EgxWindow* self)
{
    EgxCanvas_DeInit(&self->canvas);
}

void EgxCanvas_DrawRect(EgxCanvas* self, EgxCanvas_Rect* rect)
{
    EgxFrame* f = self->target->frame;

    const EGX_SZ rx = rect->x;
    const EGX_SZ rw = rect->w;
    const EGX_SZ fw = f->width;
    const EGX_SZ h1 = (rect->h - 1 + rect->y) * fw + rx, w1 = rx+rw-1;
    const EGX_SZ of1y = rect->y * fw + rx,
                 of2y = (rect->y + rect->h - 1) * fw + rx;

    for(EGX_SZ x = 0; x < rw; ++x)
        f->buffer[of1y + x] = f->buffer[of2y + x] = rect->border;
    
    for(EGX_SZ y = (rect->y+1)*fw+rx; y < h1; y += fw)
        f->buffer[y] = f->buffer[rw-1 + y] = rect->border;

    for(EGX_SZ y = (rect->y+1)*fw; y < h1-rx; y += fw)
        for(EGX_SZ x = rx+1; x < w1; ++x)
            f->buffer[y+x] = f->buffer[y+x] = rect->fill;
}

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main()
{
    EGX_SZ W = 256, H = 256;
    EGX_BYTE* buffer = malloc(W * H);
    memset(buffer, 0, W * H);

    EgxFrame frame;
    EgxFrame_Init(&frame, W, H, buffer);

    EgxWindow window;    
    EgxWindow_Init(&window, &frame);

    for(EGX_SZ x = 0; x < W / (16 + 2); ++x)
    for(EGX_SZ y = 0; y < W / (16 + 2); ++y)
    {
        EgxCanvas_Rect rect = {
            .border = 0xFF,
            .fill = 0x80,
            .x = x * (16 + 2) + 1,
            .y = y * (16 + 2) + 1,
            .w = 16,
            .h = 16,
        };
        EgxCanvas_DrawRect(&window.canvas, &rect);
    }

    // extern Egx_RGB_Ext EgxBackend_IMG_Ext__RGB_From_8_3x3x2(EGX_BYTE c);
    // printf("0x%06x\n", EgxBackend_IMG_Ext__RGB_From_8_3x3x2(0b11100011));

    // for(EGX_SZ y = 0; y < H; ++y)
    //     for(EGX_SZ i = 0; i < 256; ++i)
    //         window.frame->buffer[y * W + i] = i;

    EgxBackend backend;
    EgxBackend_IMG_Ext_Init(&backend, &window);
    backend.render(&backend);

    EgxWindow_DeInit(&window);

    free(buffer);
}
