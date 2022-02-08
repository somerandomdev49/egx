# Embedded GraphX

Fast 2D portable graphics layer written in C. Very WIP for now.

By portable I mean:
* No dynamic allocation. (no malloc, free, everything is supplied by the user)
* No stdlib
* Renders to a user created buffer
* Small memory footprint

## API

Follows my C coding style (will be a link)

Types:
* `EgxFrame` - framebuffer object
  * `width` - width of the frame
  * `height` - height of the frame
  * `buffer` - pointer to a byte buffer width*height in length (see [Color Format](#color-format))
* `EgxWindow` - TODO....

### Color Format

EGX has 8-bit pixels but doesn't define a specific color format. In most of
the backends (see [Backends](#backends)), the format is configurable. One might simulate 16-bit color
by for example two rectangles instead of one to achieve 16-bit color.
