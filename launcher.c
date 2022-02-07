#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef unsigned char EGX_BYTE;
typedef unsigned short EGX_SZ;
typedef _Bool EGX_BOOL;
#define EGX_TRUE (1)
#define EGX_FALSE (0)

typedef struct {
    EGX_BYTE* buffer;
    EGX_SZ width, height;
} EgxFrame;

void EgxFrame_Init(EgxFrame* self, EGX_SZ w, EGX_SZ h, EGX_BYTE* buf)
{
    self->buffer = buf;
    self->width = w;
    self->height = h;
}

typedef struct EgxWindow EgxWindow;

typedef struct {
    EgxWindow* target;
} EgxCanvas;

void EgxCanvas_Init(EgxCanvas* self, EgxWindow* target)
{
    self->target = target;
}

void EgxCanvas_DeInit(EgxCanvas* self) {}

struct EgxWindow {
    EgxFrame* frame;
    EgxCanvas canvas;
};

void EgxWindow_Init(EgxWindow* self, EgxFrame* frame)
{
    self->frame = frame;
    EgxCanvas_Init(&self->canvas, self);
}

void EgxWindow_DeInit(EgxWindow* self)
{
    EgxCanvas_DeInit(&self->canvas);
}

typedef struct
{
    EGX_SZ x, y, w, h;
    EGX_BYTE fill, border;
} EgxCanvas_Rect;

void EgxCanvas_DrawRect(EgxCanvas* self, EgxCanvas_Rect* rect)
{
    EgxFrame* f = self->target->frame;

    const EGX_SZ rx = rect->x;
    const EGX_SZ rw = rect->w;
    const EGX_SZ fw = f->width;
    const EGX_SZ h1 = (rect->h + rect->y) * fw, w1 = rx+rw-1;
    const EGX_SZ of1y = rect->y * fw + rx,
                 of2y = (rect->y + rect->h) * fw + rx;

    for(EGX_SZ x = 0; x < rw; ++x)
        f->buffer[of1y + x] = f->buffer[of2y + x] = rect->border;
    
    for(EGX_SZ y = (rect->y+1)*fw; y < h1; y += fw)
        f->buffer[rx + y] = f->buffer[rx+rw-1 + y] = rect->border;

    for(EGX_SZ y = (rect->y+1)*fw; y < h1; y += fw)
        for(EGX_SZ x = rx+1; x < w1; ++x)
            f->buffer[y+x] = f->buffer[y+x] = rect->fill;
}

void EgxWindow_Display(EgxWindow* self)
{
    for(EGX_SZ y = 0; y < self->frame->height; ++y)
    {
        for(EGX_SZ x = 0; x < self->frame->width; ++x)
        {
            EGX_BYTE p = self->frame->buffer[x + y * self->frame->width];
            /**/ if(p == 0x80) putc('*', stdout);
            else if(p > 128)   putc('#', stdout);
            else               putc(' ', stdout);
        }
        putc('\n', stdout);
    }
}

int main()
{
    EGX_SZ W = 16, H = 16;
    EGX_BYTE* buffer = malloc(W * H);
    memset(buffer, 0, W * H);

    EgxFrame frame;
    EgxFrame_Init(&frame, W, H, buffer);

    EgxWindow window;    
    EgxWindow_Init(&window, &frame);

    EgxCanvas_Rect rect = {
        .border = 0xFF,
        .fill = 0x80,
        .x = 2,
        .y = 2,
        .w = W - 4,
        .h = H - 4,
    };
    EgxCanvas_DrawRect(&window.canvas, &rect);

    EgxWindow_Display(&window);

    EgxWindow_DeInit(&window);

    free(buffer);
}
