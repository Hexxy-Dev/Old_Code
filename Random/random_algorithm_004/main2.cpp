#include <iostream>
#include <fstream>
#include <time.h>
#include <random>

int main() {
    srand(time(NULL));
    std::ofstream fout("sir.in");
    //int n = rand() % 100000;
    int q = rand() % 100000;
    fout << 3 << ' ' << q << '\n'
    << 1 << ' ' << 2 << ' ' << 3 << '\n';
    for(int i = 0; i < q; i++) {
        int l = rand() % 2000000000;
        int r = rand() % (2000000000 - l) + l;
        fout << l << ' ' << r << '\n';
    }
}