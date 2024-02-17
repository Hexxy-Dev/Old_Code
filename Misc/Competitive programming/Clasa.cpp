#include <iostream>

void putere(int n, int& d, int& p)
{
	d = 2;
	p = 0;
	while (n % 2 == 0) {
		p++;
		n = n / 2;
	}
	int c;
	for (int i = 3; i <= n; i += 2) {
		c = 0;
		while (n % i == 0) {
			c++;
			n = n / i;
		}
		if (c >= p) {
			p = c;
			d = i;
		}
	}
}

int main()
{
	int n = 10780, d, p;
	putere(n, d, p);
	std::cout << d << ' ' << p;
}