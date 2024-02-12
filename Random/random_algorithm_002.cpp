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