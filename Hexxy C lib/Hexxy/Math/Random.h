#ifndef HEXXY_RANDOM_H
#define HEXXY_RANDOM_H

#include <time.h>
#define RAND_MAX 0x7fff

void random_init() {
	srand(time(NULL));
}

int random_int(int n) {
	int x;
	do {
		x = rand();
	} while (x >= (RAND_MAX - RAND_MAX % n));
	x = x % n;
	return x;
}

int random_int_range(int min, int max) {
	return min + random_int(max - min);
}

float random_float(float a) {
	float x;
	x = ((float)rand() / (float)(RAND_MAX)) * a;
	return x;
}

float random_float_range(float min, float max) {
	return min + random_float(max - min);
}

#endif