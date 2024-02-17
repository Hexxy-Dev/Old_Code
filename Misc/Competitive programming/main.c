#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

int main()
{
    int n;
    scanf("%d", &n);
    int size = n * 2 - 1;
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            int iDist = (i / n) ? i - n + 2 : n - i;
            int jDist = (j / n) ? j - n + 2 : n - j;

            int max = (iDist > jDist) ? iDist : jDist;

            printf("%d ", max);
        }
        printf("\n");
    }
    return 0;
}