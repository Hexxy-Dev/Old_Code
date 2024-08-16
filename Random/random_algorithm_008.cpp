#include <iostream>

int main() {
    putchar('\n');
    size_t i, j, n = 4;
    scanf("%d\n%d", &i, &j);
    int x = (i + 1) * (n + 2) + j + 1;
    size_t x2 = (i + 1) * (n + 2) + j + 1;
    printf("%d %d %d %d %d\n",i,j,n,x,x2);
    std::cout << i << ' ' << j << ' '
    << n << ' ' << x << ' ' << x2 << '\n'
    << (int)i << ' ' << (int)j << ' ' << (int)n << ' '
    << (int)x << ' ' << (int)x2 << '\n';
    if(x != x2)
        puts("HMMMMMMMMMMM\n\n\n\n\n\n\n");
}