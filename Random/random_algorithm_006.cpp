#include <iostream>
#include <string>
#include <chrono>
using namespace std::chrono;
using namespace std;

#define Main

int V1(int n)
{
    long p = 10;
    while(p <= n) {
        if(n / p % 10 == 2 && n / (p / 10) % 10 == 2)
            n -= 2 * p / 10;
        p *= 10;
    }
    return n;
}

int V2(int n)
{
    string s = to_string(n);
    n = s[0] - '0';
    for(int i = 1; i < s.size(); i++) {
        n *= 10;
        if(s[i] == s[i-1] && s[i] == '2')
            continue;
        n += s[i] - '0';
    }
    return n;
}

#ifdef Main
int main()
{
    auto start = high_resolution_clock::now();
        srand(time(NULL));
        size_t seed = rand();
        printf("%d\n%d\n", V1(22023422), V2(22023422));
        auto stop = high_resolution_clock::now();
        auto duration = duration_cast<nanoseconds>(stop - start);
        printf("%u\n", duration.count());
        auto t1 = duration.count();
        auto t2 = duration.count();
        size_t j = 110;

        size_t v1 = 0, v2 = 0;

    for(size_t i = 0; i < 100; i++) {
        seed = rand();

        srand(seed);
        start = high_resolution_clock::now();
        for(j = 0; j < 1000000000; j++)
            V1(rand());
        stop = high_resolution_clock::now();
        t1 = duration_cast<nanoseconds>(stop - start).count();

        srand(seed);
        start = high_resolution_clock::now();
        for(j = 0; j < 1000000000; j++)
            V2(rand());
        stop = high_resolution_clock::now();
        t2 = duration_cast<nanoseconds>(stop - start).count();

        //printf("%d\n%d ",t1,t2);
        if(t1 == t2) 
            continue;
        if(t1 < t2) {
            v1++;
        //    printf("DIFF:%d\n",t2-t1);
        } else {
            v2++;
        //    printf("DIFF:%d\n",t1-t2);
        }
    }
    printf("V1:%d V2:%d",v1,v2);
}
#endif
