#include <Main.h>

__kernel void main(__global unsigned char* image, int image_width, int image_height)
{
	const int ix = get_global_id(0);
	const int jy = get_global_id(1);

	Main(image, image_width, image_height, ix, jy);
};
