#include "Main.h"

// This file is used to test the raytracer without OpenCL


const int Current_Scene = 6;

#define aspect_ratio (double)(1.0) // (double)(16.0/9.0)
#define image_width 100
#define image_height (int)(image_width/aspect_ratio)

const int max_depth = 50;
int samples_per_pixel = 100;

#define full_image_size image_height*image_width*4
unsigned char image[full_image_size];



#include <stdio.h>

int main(void) {
	for (int ix = 0; ix < image_height; ix++)
		for (int jy = 0; jy < image_height; jy++)
			Main(image, image_width, image_height, ix, jy);

	printf("P3\n%d %d\n255\n", image_width, image_height);
	for (int j = image_height - 1; j >= 0; --j) {
		for (int i = 0; i < image_width; ++i) {
			printf("%d %d %d\n", image[i * 4 + j * image_width * 4 + 0], image[i * 4 + j * image_width * 4 + 1], image[i * 4 + j * image_width * 4 + 2]);
		}
	}
}