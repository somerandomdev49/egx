#include <egx/egx.h>
#include <egx/egx_ext.h>
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
    
    EgxBackend_IMG_Ext backend;
    EgxBackend_IMG_IO_Ext backend_io;
    EgxBackend_IMG_IO_Ext_SetLibC(&backend_io);
    
    EgxBackend_IMG_Ext_Init(&backend, &window, &backend_io);
    backend.base.render((EgxBackend*)&backend);

    EgxWindow_DeInit(&window);

    free(buffer);
}
