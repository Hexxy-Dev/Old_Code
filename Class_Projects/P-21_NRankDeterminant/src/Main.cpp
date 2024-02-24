#include <iostream>
using namespace std;

// Bareiss algorithm
#define N 12
//accurate up to N = 12  (values from +-10)
//after N = 12 accuracy of least significant digits drops by N - 12

int main()
{
    srand(time(NULL));

    long double mat[N + 1][N + 1];
    mat[0][0] = 1.0;
    for (size_t i = 1; i < N + 1; i++)
        for (size_t j = 1; j < N + 1; j++)
            mat[i][j] = rand() % 20 - 10 + 0.0;

    for (size_t i = 1; i < N + 1; i++) {
        for (size_t j = 1; j < N + 1; j++)
            printf("%.0f ", mat[i][j]);
        puts("");
    }
    for (size_t k = 1; k < N; k++)
        for (size_t i = k + 1; i < N + 1; i++)
            for (size_t j = k + 1; j < N + 1; j++)
                mat[i][j] = (mat[i][j] * mat[k][k] - mat[i][k] * mat[k][j]) / mat[k - 1][k - 1];
    
    printf("%.0f ", mat[N][N]);
    return 0;
}