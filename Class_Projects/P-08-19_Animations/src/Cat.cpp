#include <iostream>
#include "Cat.h"

int main()
{
	for (size_t i = 0; i < 1000; i++) {
		puts(frames[i % 11]);
		_sleep(100);
	}
}