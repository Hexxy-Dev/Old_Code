#ifdef V2
#include <iostream>
#include <vector>
#include <deque>
#include <algorithm>

int resultCount = 0;
int maxlen = 0;

void CheckWindowSubset(std::vector<int> windowSubset)
{
    std::sort(windowSubset.begin(), windowSubset.end());
    for(int i = 0; i < windowSubset.size() - 1; i++)
        if(windowSubset[i] + 1 != windowSubset[i + 1])
            return;
    if(maxlen < windowSubset.size()){
        maxlen = windowSubset.size();
        resultCount = 0;
    }
    if(maxlen == windowSubset.size())
        resultCount++;
}

void CheckWindow(const std::deque<int>& window)
{
    for(int i = 0; i < window.size(); i++)
        for(int j = 0; window.size() - i - j >= maxlen; j++)
            CheckWindowSubset({window.begin() + i, window.end() - j});
}

int main()
{
    int tmp;
    std::deque<int> window;
    while(std::cin >> tmp)
        if(std::find(window.begin(), window.end(), tmp) == window.end())
            window.push_back(tmp);
        else {
            CheckWindow(window);
            while(std::find(window.begin(), window.end(), tmp) != window.end())
                window.pop_front();
            window.push_back(tmp);
        }
    CheckWindow(window);
    std::cout << maxlen << ' ' << resultCount;
}
#endif

#ifdef V3
#include <iostream>
#include <vector>
#include <deque>
#include <algorithm>

int resultCount = 0;
int maxlen = 0;

void CheckWindowSubset(const std::vector<int>& windowSubset)
{
    int max,min;
    max = min = windowSubset[0];
    for(int i = 1; i < windowSubset.size(); i++){
        max = std::max(max,windowSubset[i]);
        min = std::min(min,windowSubset[i]);
        if(max - min > windowSubset.size())
            return;
    }
    if(max - min != windowSubset.size() - 1)
        return;

    if(maxlen < windowSubset.size()){
        maxlen = windowSubset.size();
        resultCount = 0;
    }
    if(maxlen == windowSubset.size())
        resultCount++;
}

void CheckWindow(const std::deque<int>& window)
{
    for(int i = 0; i < window.size(); i++)
        for(int j = 0; window.size() - i - j >= maxlen; j++)
            CheckWindowSubset({window.begin() + i, window.end() - j});
}

int main()
{
    int tmp;
    std::deque<int> window;
    while(std::cin >> tmp)
        if(std::find(window.begin(), window.end(), tmp) == window.end())
            window.push_back(tmp);
        else {
            CheckWindow(window);
            while(std::find(window.begin(), window.end(), tmp) != window.end())
                window.pop_front();
            window.push_back(tmp);
        }
    CheckWindow(window);
    std::cout << maxlen << ' ' << resultCount;
}
#endif

#ifdef V4
#include <iostream>
#include <deque>
#include <algorithm>

int resultCount = 0;
int maxlen = 0;

void CheckWindow(const std::deque<int>& window)
{
    for(int i = 0; window.size() - i >= maxlen; i++)
        for(int j = 0; window.size() - i - j >= maxlen; j++) {
            const int subsetSize = window.size() - i - j;
            int max,min;
            max = min = window[i];
            for(int k = i+1; k < window.size() - j; k++){
                max = std::max(max,window[k]);
                min = std::min(min,window[k]);
                if(max - min > subsetSize)
                    goto NEXT;
            }
            if(max - min != subsetSize - 1)
                goto NEXT;

            if(maxlen < subsetSize){
                maxlen = subsetSize;
                resultCount = 0;
            }
            if(maxlen == subsetSize)
                resultCount++;
            NEXT:;
        }
}

int main()
{
    int tmp;
    std::deque<int> window;
    while(std::cin >> tmp) {
        int it = std::find(window.begin(), window.end(), tmp) - window.begin();
        if(it == window.size())
            window.push_back(tmp);
        else {
            CheckWindow(window);
            window.pop_front();
            while(it--)
                window.pop_front();
            window.push_back(tmp);
        }
    }
    CheckWindow(window);
    std::cout << maxlen << ' ' << resultCount;
}
#endif

// FINAL
#ifdef V5
#include <iostream>
#include <deque>
#include <vector>
#include <algorithm>

int resultCount = 0;
int maxlen = 0;
std::vector<int> lastSubset;

void CheckWindow(const std::deque<int>& window)
{
    for (int i = 0; window.size() - i >= maxlen; i++)
        for (int j = 0; window.size() - i - j >= maxlen; j++) {
            const int subsetSize = window.size() - i - j;
            int max, min;
            max = min = window[i];
            for (int k = i + 1; k < window.size() - j; k++) {
                max = std::max(max, window[k]);
                min = std::min(min, window[k]);
                if (max - min > subsetSize)
                    goto NEXT;
            }
            if (max - min != subsetSize - 1)
                goto NEXT;

            if (maxlen < subsetSize) {
                maxlen = subsetSize;
                resultCount = 0;
            }
            if (maxlen == subsetSize) {
                if (!std::equal(window.begin() + i, window.end() - j,
                    lastSubset.begin(), lastSubset.end())) {
                    resultCount++;
                    lastSubset.clear();
                    lastSubset = { window.begin() + i, window.end() - j };
                }
            }
        NEXT:;
        }
}

int main()
{
    int tmp;
    std::deque<int> window;
    int iter = 0;
    while (std::cin >> tmp) {
        int it = std::find(window.begin(), window.end(), tmp) - window.begin();
        if (it == window.size())
            window.push_back(tmp);
        else {
            iter++;
            CheckWindow(window);
            window.pop_front();
            while (it--)
                window.pop_front();
            window.push_back(tmp);
            if (std::find(lastSubset.begin(), lastSubset.end(), tmp) != lastSubset.end()
                || iter >= lastSubset.size()) {
                lastSubset.clear();
                iter = 0;
            }
        }
    }
    CheckWindow(window);
    std::cout << maxlen << ' ' << resultCount;
}
#endif

//#1027 only part 2
#ifdef V5.5
#include <iostream>
#include <deque>
#include <vector>
#include <algorithm>

#include <fstream>

int resultCount = 0;
int maxlen = 0;
std::vector<int> lastSubset;

void CheckWindow(const std::deque<int>& window)
{
    for (int i = 0; window.size() - i >= maxlen; i++)
        for (int j = 0; window.size() - i - j >= maxlen; j++) {
            const int subsetSize = window.size() - i - j;
            int max, min;
            max = min = window[i];
            for (int k = i + 1; k < window.size() - j; k++) {
                max = std::max(max, window[k]);
                min = std::min(min, window[k]);
                if (max - min > subsetSize)
                    goto NEXT;
            }
            if (max - min != subsetSize - 1)
                goto NEXT;

            if (maxlen < subsetSize) {
                maxlen = subsetSize;
                resultCount = 0;
            }
            if (maxlen == subsetSize) {
                //if(!std::equal(window.begin()+i,window.end()-j,
                //lastSubset.begin(),lastSubset.end())) {
                if (std::vector<int>(window.begin() + i, window.end() - j) != lastSubset) {
                  resultCount++;
                    lastSubset.clear();
                    //lastSubset = {window.begin()+i,window.end()-j};
                    lastSubset = std::vector<int>(window.begin() + i, window.end() - j);
                }
            }
        NEXT:;
        }
}

int main()
{
    std::ifstream fin("cool.in");
    int tmp;
    fin >> tmp >> tmp >> tmp;
    std::deque<int> window;
    int iter = 0;
    while (fin >> tmp) {
        int it = std::find(window.begin(), window.end(), tmp) - window.begin();
        if (it == window.size())
            window.push_back(tmp);
        else {
            iter++;
            CheckWindow(window);
            window.pop_front();
            while (it--)
                window.pop_front();
            window.push_back(tmp);
            if (std::find(lastSubset.begin(), lastSubset.end(), tmp) != lastSubset.end()
                || iter >= lastSubset.size()) {
                lastSubset.clear();
                iter = 0;
            }
        }
    }
    fin.close();
    std::ofstream fout("cool.out");
    CheckWindow(window);
    fout << maxlen << '\n' << resultCount;
    fout.close();
}
#endif