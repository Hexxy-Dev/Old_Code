#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

#include <chrono>

struct hmm {
    int l,r,s;
};

inline void printHMM(const hmm& a) {
    std::cout << a.l << ' ' << a.r << ' ' << a.s << '\n';
}

/*/
#define fin std::cin
#define fout std::cout
//*/

#define DEBUG

int main()
{
#ifdef DEBUG
auto start = std::chrono::high_resolution_clock::now();
#endif
#ifndef fin
    std::ifstream fin("sir.in");
#endif
#ifndef fout
    std::ofstream fout("sir.out");
#endif
    int n,q;
    fin>>n>>q;
    std::vector<int> v;
    v.reserve(100001);
    int mx = 0;
    int c = 0;

    for(int i = 0; i < n; i++) {
        int t;
        fin >> t;
        v.emplace_back(t);
        if(t) {
            c++;
            mx = t;
        }
    }
    std::vector<hmm> p;
    p.reserve(q);
    int MAX = 0;
    while(q--) {
        int l,r;
        fin>>l>>r;
        MAX = std::max(MAX, r);
        p.emplace_back(hmm{l,r,0});
    }
#ifndef fin
    fin.close();
#endif
/*/
    std::sort(p.begin(),p.end(),[](hmm a,hmm b){return a.r > b.r;});
    std::sort(p.begin(),p.end(),[](hmm a,hmm b){return a.l < b.l;});
//*/
#ifdef DEBUG2
MAX = 100000;
#endif
    int l = 0;
    for(int i = n; i <= MAX; i++) {
        if(c % 2 == 1) {
            mx++;
            c++;
            v.emplace_back(mx);
        } else
            v.emplace_back(0);
        if(v[l])
            c--;
        l++;
    }

    int k = 0;
    for(int i = 0; i < v.size(); i++)
        for(int j = k; j < p.size(); j++)
            if(p[j].l <= i+1)
                if(p[j].r>=i+1)
                    p[j].s+=v[i];
    /*/
                else
                    k++;
            else
                break;
    //*/

    for(int i = 0; i < p.size(); i++)
#ifndef fout
        fout << p[i].s << '\n';
#else
        printHMM(p[i]);
#endif
#ifndef fout
    fout.close();
#endif
#ifdef DEBUG
auto stop = std::chrono::high_resolution_clock::now();
auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);
std::cout << duration.count() << '\n';
#endif
}
/*
9 2
0 1 2 3 0 0 4 0 5
1 4
7 13

3 2
1 2 3
1 5
3 8
*/
