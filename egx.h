#ifndef EGX_HEADER_
#define EGX_HEADER_

typedef unsigned char EGX_BYTE;
typedef unsigned short EGX_SZ;
typedef _Bool EGX_BOOL;
#define EGX_TRUE (1)
#define EGX_FALSE (0)

typedef struct
{
    EGX_BYTE* buffer;
    EGX_SZ width, height;
} EgxFrame;

typedef struct EgxWindow EgxWindow;

typedef struct
{
    EgxWindow* target;
} EgxCanvas;

struct EgxWindow
{
    EgxFrame* frame;
    EgxCanvas canvas;
    const char* title;
};

typedef struct
{
    EGX_SZ x, y, w, h;
    EGX_BYTE fill, border;
} EgxCanvas_Rect;

typedef struct EgxBackend EgxBackend;

struct EgxBackend
{
    /** @brief If true, no rendering loop should be started.
     *         and render() should be called only once.
     * If this is true, calling any of begin(), end(), next() is UB.
     */
    EGX_BOOL single;

    /**
     * @brief Window bound to the backend implementation instance.
     */
    EgxWindow* bound;

    /**
     * @brief Signifies the start of a frame.
     */
    void (*begin)(EgxBackend* self);

    /**
     * @brief Renders the contents of the framebuffer to it's target.
     */
    void (*render)(EgxBackend* self);

    /**
     * @brief Signifies the end of a frame.
     */
    void (*end)(EgxBackend* self);

    /**
     * @brief Waits for next frame and returns the time spent waiting.
     * @returns the time spent blocking (in ns?).
     */
    EGX_SZ (*next)(EgxBackend* self);
};

typedef struct { EGX_BYTE r, g, b, a; } Egx_RGBA_Ext;
typedef struct { EGX_BYTE r, g, b; } Egx_RGB_Ext;

void EgxFrame_Init(EgxFrame* self, EGX_SZ w, EGX_SZ h, EGX_BYTE* buf);
void EgxCanvas_Init(EgxCanvas* self, EgxWindow* target);
void EgxCanvas_DeInit(EgxCanvas* self);
void EgxWindow_Init(EgxWindow* self, EgxFrame* frame);
void EgxWindow_DeInit(EgxWindow* self);
void EgxCanvas_DrawRect(EgxCanvas* self, EgxCanvas_Rect* rect);
void EgxWindow_SetBackend(EgxWindow* self, EgxBackend* back);
void EgxWindow_Display(EgxWindow* self);
void EgxBackend_IMG_Ext_Init(EgxBackend* self, EgxWindow* window);

#endif
