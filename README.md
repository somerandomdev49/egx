# Embedded GraphX

2D (possibly 3D in the future) embedded
renderer written in C. Very WIP for now.

By embedded I mean:
* No dynamic allocation.
* No libc
* Renders to a user created buffer
* Small memory footprint

## API

Follows my C coding style (will be a link)

Types:
* `EgxFrame` - framebuffer object
  * `width` - width of the frame
  * `height` - height of the frame
  * `buffer` - pointer to a byte buffer width*height in length
* `EgxWindow` - TODO....



 
