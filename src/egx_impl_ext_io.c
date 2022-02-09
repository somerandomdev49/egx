#include <egx/egx.h>

#ifdef EGX_BACKEND_IMG_IO_USE_LIBC

#ifndef EGX_BACKEND_IMG_IO_STDIO_HEADER
#define EGX_BACKEND_IMG_IO_STDIO_HEADER <stdio.h>
#endif

#include EGX_BACKEND_IMG_IO_STDIO_HEADER

static void* EgxBackend_IMG_IO_Ext_LibC__open_file(const char* fname)
{
  return fopen(fname, "wb");
}

static void EgxBackend_IMG_IO_Ext_LibC__close_file(void* ptr)
{
    fclose((FILE*)ptr);
}

static void EgxBackend_IMG_IO_Ext_LibC__write1_file(void* ptr, EGX_BYTE c)
{
    fputc(c, (FILE*)ptr);
}

static void EgxBackend_IMG_IO_Ext_LibC__writeN_file(void* ptr, void* data, EGX_SZ sz)
{
    fwrite(data, sz, 1, (FILE*)ptr);
}

void EgxBackend_IMG_IO_Ext_SetLibC(EgxBackend_IMG_IO_Ext* io)
{
    // TODO
    io->open_file = &EgxBackend_IMG_IO_Ext_LibC__open_file;
    io->close_file = &EgxBackend_IMG_IO_Ext_LibC__close_file;
    io->write1_file = &EgxBackend_IMG_IO_Ext_LibC__write1_file;
    io->writeN_file = &EgxBackend_IMG_IO_Ext_LibC__writeN_file;
}

#endif


