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
                    lastSubset = { window.begin() + i,window.end() - j };
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