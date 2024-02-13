#include <iostream>
#include <deque>
#include <vector>
#include <algorithm>
#include <cstring>
#include <cmath>
#include <string>
#include <chrono>

int cmmdc(int a, int b) {
    if (b == 0)
        return a;
    return cmmdc(b, a % b);
}
int gcd(int a, int b)
{
    while (b) b ^= a ^= b ^= a %= b;
    return a;
}

int gcd2(int a, int b)
{
    if (a == 0)
        return b;
    if (b == 0)
        return a;
    int k;
    for (k = 0; ((a | b) & 1) == 0; ++k) {
        a >>= 1;
        b >>= 1;
    }
    while ((a & 1) == 0)
        a >>= 1;
    do {
        while ((b & 1) == 0)
            b >>= 1;
        if (a > b)
            std::swap(a, b);
        b = (b - a);
    } while (b != 0);
    return a << k;
}



int main()
{
    int iter = 100000000;
    int bigiter = 1;
    for (int j = 0; j < bigiter; j++) {
        uint64_t v1 = 0;
        uint32_t v1mx = 0;
        uint32_t v1mn = -1;
        uint64_t v2 = 0;
        uint32_t v2mx = 0;
        uint32_t v2mn = -1;
        uint64_t v3 = 0;
        uint32_t v3mx = 0;
        uint32_t v3mn = -1;
        
        for (int i = 0; i < iter; i++) {
            int a = rand();
            int b = rand();
            {
                auto start = std::chrono::high_resolution_clock::now();
                int r = cmmdc(a, b);
                auto stop = std::chrono::high_resolution_clock::now();
                auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(stop - start);
                v1 += duration.count();
                v1mx = std::max(v1mx, (uint32_t)duration.count());
                v1mn = std::min(v1mn, (uint32_t)duration.count());
            }
            {
                auto start = std::chrono::high_resolution_clock::now();
                int r = gcd(a, b);
                auto stop = std::chrono::high_resolution_clock::now();
                auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(stop - start);
                v2 += duration.count();
                v2mx = std::max(v2mx, (uint32_t)duration.count());
                v2mn = std::min(v2mn, (uint32_t)duration.count());
            }
            {
                auto start = std::chrono::high_resolution_clock::now();
                int r = gcd2(a, b);
                auto stop = std::chrono::high_resolution_clock::now();
                auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(stop - start);
                v3 += duration.count();
                v3mx = std::max(v3mx, (uint32_t)duration.count());
                v3mn = std::min(v3mn, (uint32_t)duration.count());
            }
        }
        printf("%llu\n%f %u %u\n%llu\n%f %u %u\n%llu\n%f %u %u\n\n",
            v1, (long double)v1 / iter, v1mn, v1mx,
            v2, (long double)v2 / iter, v2mn, v2mx, 
            v3, (long double)v3 / iter, v3mn, v3mx);
    }
    for (int j = 0; j < bigiter; j++) {
        uint64_t v1 = 0;
        uint32_t v1mx = 0;
        uint32_t v1mn = -1;
        uint64_t v2 = 0;
        uint32_t v2mx = 0;
        uint32_t v2mn = -1;
        uint64_t v3 = 0;
        uint32_t v3mx = 0;
        uint32_t v3mn = -1;
        
        for (int i = 0; i < iter; i++) {
            int a = rand();
            int b = rand();
            auto start = std::chrono::high_resolution_clock::now();
            int r = cmmdc(a, b);
            auto stop = std::chrono::high_resolution_clock::now();
            auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(stop - start);
            v1 += duration.count();
            v1mx = std::max(v1mx, (uint32_t)duration.count());
            v1mn = std::min(v1mn, (uint32_t)duration.count());
        }
        for (int i = 0; i < iter; i++) {
            int a = rand();
            int b = rand();
            auto start = std::chrono::high_resolution_clock::now();
            int r = gcd(a, b);
            auto stop = std::chrono::high_resolution_clock::now();
            auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(stop - start);
            v2 += duration.count();
            v2mx = std::max(v2mx, (uint32_t)duration.count());
            v2mn = std::min(v2mn, (uint32_t)duration.count());
        }
        for (int i = 0; i < iter; i++) {
            int a = rand();
            int b = rand();
            auto start = std::chrono::high_resolution_clock::now();
            int r = gcd2(a, b);
            auto stop = std::chrono::high_resolution_clock::now();
            auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(stop - start);
            v3 += duration.count();
            v3mx = std::max(v3mx, (uint32_t)duration.count());
            v3mn = std::min(v3mn, (uint32_t)duration.count());
        }
        printf("%llu\n%f %u %u\n%llu\n%f %u %u\n%llu\n%f %u %u\n\n",
            v1, (long double)v1 / iter, v1mn, v1mx,
            v2, (long double)v2 / iter, v2mn, v2mx,
            v3, (long double)v3 / iter, v3mn, v3mx);
    }

    int predetermined = 2;

    for (int j = 0; j < bigiter; j++) {
        uint64_t v1 = 0;
        uint32_t v1mx = 0;
        uint32_t v1mn = -1;
        uint64_t v2 = 0;
        uint32_t v2mx = 0;
        uint32_t v2mn = -1;
        uint64_t v3 = 0;
        uint32_t v3mx = 0;
        uint32_t v3mn = -1;

        for (int i = 0; i < iter; i++) {
            int a = rand();
            int b = predetermined;
            {
                auto start = std::chrono::high_resolution_clock::now();
                int r = cmmdc(a, b);
                auto stop = std::chrono::high_resolution_clock::now();
                auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(stop - start);
                v1 += duration.count();
                v1mx = std::max(v1mx, (uint32_t)duration.count());
                v1mn = std::min(v1mn, (uint32_t)duration.count());
            }
            {
                auto start = std::chrono::high_resolution_clock::now();
                int r = gcd(a, b);
                auto stop = std::chrono::high_resolution_clock::now();
                auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(stop - start);
                v2 += duration.count();
                v2mx = std::max(v2mx, (uint32_t)duration.count());
                v2mn = std::min(v2mn, (uint32_t)duration.count());
            }
            {
                auto start = std::chrono::high_resolution_clock::now();
                int r = gcd2(a, b);
                auto stop = std::chrono::high_resolution_clock::now();
                auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(stop - start);
                v3 += duration.count();
                v3mx = std::max(v3mx, (uint32_t)duration.count());
                v3mn = std::min(v3mn, (uint32_t)duration.count());
            }
        }
        printf("%llu\n%f %u %u\n%llu\n%f %u %u\n%llu\n%f %u %u\n\n",
            v1, (long double)v1 / iter, v1mn, v1mx,
            v2, (long double)v2 / iter, v2mn, v2mx,
            v3, (long double)v3 / iter, v3mn, v3mx);
    }
    for (int j = 0; j < bigiter; j++) {
        uint64_t v1 = 0;
        uint32_t v1mx = 0;
        uint32_t v1mn = -1;
        uint64_t v2 = 0;
        uint32_t v2mx = 0;
        uint32_t v2mn = -1;
        uint64_t v3 = 0;
        uint32_t v3mx = 0;
        uint32_t v3mn = -1;

        for (int i = 0; i < iter; i++) {
            int a = rand();
            int b = predetermined;
            auto start = std::chrono::high_resolution_clock::now();
            int r = cmmdc(a, b);
            auto stop = std::chrono::high_resolution_clock::now();
            auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(stop - start);
            v1 += duration.count();
            v1mx = std::max(v1mx, (uint32_t)duration.count());
            v1mn = std::min(v1mn, (uint32_t)duration.count());
        }
        for (int i = 0; i < iter; i++) {
            int a = rand();
            int b = predetermined;
            auto start = std::chrono::high_resolution_clock::now();
            int r = gcd(a, b);
            auto stop = std::chrono::high_resolution_clock::now();
            auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(stop - start);
            v2 += duration.count();
            v2mx = std::max(v2mx, (uint32_t)duration.count());
            v2mn = std::min(v2mn, (uint32_t)duration.count());
        }
        for (int i = 0; i < iter; i++) {
            int a = rand();
            int b = predetermined;
            auto start = std::chrono::high_resolution_clock::now();
            int r = gcd2(a, b);
            auto stop = std::chrono::high_resolution_clock::now();
            auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(stop - start);
            v3 += duration.count();
            v3mx = std::max(v3mx, (uint32_t)duration.count());
            v3mn = std::min(v3mn, (uint32_t)duration.count());
        }
        printf("%llu\n%f %u %u\n%llu\n%f %u %u\n%llu\n%f %u %u\n\n",
            v1, (long double)v1 / iter, v1mn, v1mx,
            v2, (long double)v2 / iter, v2mn, v2mx,
            v3, (long double)v3 / iter, v3mn, v3mx);
    }
}