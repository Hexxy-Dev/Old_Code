#include <iostream>

int GetMaxVolume(size_t n, size_t* h)
{
    size_t MV = 0;
    for (size_t i = 0; i < n; i++)
        for (size_t j = i + 1; j < n; j++)
            if (std::min(h[i], h[j]) * (j - i) > MV)
                MV = std::min(h[i], h[j]) * (j - i);
    return MV;
}

int main()
{
    size_t NrOfGates = 9;
    size_t GateHeights[] = { 1,8,6,2,5,4,8,3,7 };

    std::cout << GetMaxVolume(NrOfGates, GateHeights);
}