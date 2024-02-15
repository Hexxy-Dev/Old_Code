// ...
#include "Globals.h"

void write_color(color pixel_color, int samples_per_pixel, size_t texture_index_H, size_t texture_index_W)
{
    // ...

    image[texture_index_H][texture_index_W][0] = static_cast<GLubyte>(static_cast<int>(256 * clamp(r, 0.0, 0.999)));
    image[texture_index_H][texture_index_W][1] = static_cast<GLubyte>(static_cast<int>(256 * clamp(g, 0.0, 0.999)));
    image[texture_index_H][texture_index_W][2] = static_cast<GLubyte>(static_cast<int>(256 * clamp(b, 0.0, 0.999)));
    image[texture_index_H][texture_index_W][3] = static_cast<GLubyte>(255);
}
// ...