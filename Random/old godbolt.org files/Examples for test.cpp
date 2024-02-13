/*
#include <iostream>

template<typename T>
void printArray(T arr, size_t size)
{ for (size_t i = 0; i < size; i++) std::cout << arr[i] << ' '; puts(""); }



template<typename T>
void merge(T* arr, T* tmp, size_t s, size_t t1, size_t t2)
{
    size_t i = 0;
    size_t j = t1;
    size_t k = s;

    while (i < t1 - s && j < t2 - s) {
        if (tmp[i] <= tmp[j])
            arr[k] = tmp[i++];
        else
            arr[k] = tmp[j++];
        k++;
    }

    while (i < t1 - s)
        arr[k++] = tmp[i++];

    while (j < t2 - s)
        arr[k++] = tmp[j++];
}

template<typename T>
void mergeSort(T* arr, size_t r, size_t l = 0)
{
    if (l >= r)
        return;

    printf("%u %u -%u-  ", l + 1, r, r - l);

    //std::cout << '\n' << typeid(T).name() << '\n';

    size_t m = l + (r - l) / 2;
    printf("%u\n", m + 1);
    mergeSort(arr, m, l);
    mergeSort(arr, r, m + 1);

    //T* tmp = new T[r - l];
    //for (size_t i = 0; i < r - l - 1; i++) {
    //    printf("%d ", arr[l + i]);
    //    tmp[i] = arr[l + i];
    //}
    //printf("\n%u %u %u\n", l, m, r);
    //
    //merge<T>(arr, tmp, l, m, r);
    //
    //delete[] tmp;
}
//                              l r
//12 11 13 5 6 7 8  // 1-7      0 7      0 1 2 3 4 5 6
//12 11 13          // 1-3      0 3      0 1 2
//5 6 7 8           // 4-7      3 7      3 4 5 6

//12 11 13          // 1-3      0 3      0 1 2
//12                // 1-1      0 1      0
//11 13             // 2-3      1 3      1 2

//5 6 7 8           // 4-7      3 7      3 4 5 6
//5 6               // 4-5      3 5      3 4
//7 8               // 6-7      5 7      5 6


int main()
{
#define TYPE int
    size_t arr_size = 6;
    TYPE* arr = new TYPE[arr_size]{12, 11, 13, 5, 6, 7};
    //size_t arr_size = sizeof(arr) / sizeof(arr[0]);

    printArray(arr, arr_size);
    mergeSort(arr, arr_size);
    printArray(arr, arr_size);
    return 0;
}
//*/

/*
#include <iostream>
using namespace std;

int x[10] , n , p;

void Afis(int k)
{
    for(int j = 1 ; j <= k ; j ++)
        cout << x[j] << " ";
    cout << endl;
}

bool OK(int k){
    for(int i = 1 ; i < k ; ++ i)
        if(x[k] == x[i])
            return false;
    if(k > 1)
        if(x[k] <= x[k-1])
            return false;
    return true;
}

bool Solutie(int k)
{
    return k == p;
}

void back(int k){
    for(int i = 1 ; i <= n ; ++ i)
    {
        x[k] = i;
        if(OK(k))
            if(Solutie(k))
                Afis(k);
            else
                back(k + 1);
    }
}
int main(){
    cin >> n >> p;
    back(1);
    return 0;
}
//*/

/*
#include <iostream>
using namespace std;

int x[10] , n , p;

void Afis(int k)
{
    for(int j = 1 ; j <= k ; j ++)
        cout << x[j] << " ";
    cout << endl;
}

void back(int k){
    for(int i = x[k-1] + 1 ; i <= n ; ++ i)
    {
        x[k] = i;
        if(k == p)
            Afis(k);
        else
            back(k + 1);
    }
}
int main(){
    cin >> n >> p;
    x[0] = 0;
    back(1);
    return 0;
}
//*/

/*
#include <iostream>
using namespace std;

int x[10], n;

void Afis()
{
    for (int j = 1; j <= n; j++)
        cout << x[j] << " ";
    cout << endl;
}

bool OK(int k) {
    for (int i = 1; i < k; ++i)
        if (x[k] == x[i])
            return false;
    return true;
}

bool Solutie(int k)
{
    return k == n;
}

void back(int k) {
    for (int i = 1; i <= n; ++i)
    {
        x[k] = i;
        if (OK(k))
            if (Solutie(k))
                Afis();
            else
                back(k + 1);
    }
}
int main() {
    cin >> n;
    back(1);
    return 0;
}
//*/

/*
#include <iostream>
using namespace std;

int x[10], n;

void afis(int k) {
    for (int i = 1; i <= k; ++i)
        cout << x[i] << " ";
    cout << endl;
}
bool valid(int k) {
    if (k == 1)
        return true;
    if (x[k] > x[k - 1])
        return true;
    return false;
}
void back(int k) {
    for (int i = 1; i <= n; ++i)
    {
        x[k] = i;
        if (valid(k))
        {
            afis(k);
            back(k + 1);
        }
    }
}
int main() {
    cin >> n;
    back(1);
    return 0;
}
//*/

/*
#include <iostream>
using namespace std;

int x[10], n;

void afis(int k) {
    for (int i = 1; i <= k; ++i)
        cout << x[i] << " ";
    cout << endl;
}

void back(int k) {
    for (int i = x[k - 1] + 1; i <= n; ++i)
    {
        x[k] = i;
        afis(k);
        back(k + 1);
    }
}
int main() {
    cin >> n;
    back(1);
    return 0;
}
//*/

/*
#include <iostream>
using namespace std;

int tmp[100];

void MergeSort(int v[], int st, int dr)
{
    if (st < dr)
    {
        int m = (st + dr) / 2;
        MergeSort(v, st, m);
        MergeSort(v, m + 1, dr);
        //Interclasare
        int i = st, j = m + 1, k = 0;
        while (i <= m && j <= dr)
            if (v[i] < v[j])
                tmp[++k] = v[i++];
            else
                tmp[++k] = v[j++];
        while (i <= m)
            tmp[++k] = v[i++];
        while (j <= dr)
            tmp[++k] = v[j++];
        for (i = st, j = 1; i <= dr; i++, j++)
            v[i] = tmp[j];
    }
}

int main()
{
    int v[] = { 5, 8, 4, 8, 9, 11 };
    MergeSort(v, 0, 5);
    for (size_t i = 0; i < 6; i++)
        printf("%d ", v[i]);
}

//*/

#include <iostream>

struct Combinations {
    typedef size_t T;
    typedef size_t I;
    Combinations(I N, I K)
        : n(N), k(K)
    {
        s = new T[K + 1];
        B(1);
        delete[] s;
    }
private:
    T* s;
    I n, k;

    void D(I l)
    {
        for (I j = 1; j <= l; j++)
            std::cout << s[j] << ' ';
        puts("");
    }

    bool V(I l)
    {
        //for (int i = 1; i < l; ++i)
        //    if (s[l] == s[i])   return 0;
        if (l > 1)
            if (s[l] <= s[l - 1])
                return 0;
        return 1;
    }

    bool S(I l)
    { return l == k; }

    void B(I l)
    {
        for (T i = 1; i <= n; ++i) {
            s[l] = i;
            if (V(l))
                if (S(l))
                    D(l);
                else
                    B(l + 1);
        }
    }
};

template<typename T>
struct MergeSort {
    typedef size_t I;
    MergeSort(T* arr, I size)
        : a(arr)
    {
        t = new T[size / 2 + (size % 2)];
        S(0, size - 1);
        delete[] t;
    }
private:
    T *a, *t;
    void S(I l, I r)
    {
        if (l >= r)
            return;
        I m = (l + r) / 2;
        S(l, m);
        S(m + 1, r);

        for (I i = 0; i <= (r - l) / 2; i++)
            t[i] = a[l + i];//copy bottom half

        I i = 0, j = m + 1, k = l;
        m -= l;
        while (i <= m && j <= r)
            a[k++] = (t[i] < a[j] ? t[i++] : a[j++]);
        while (i <= m)
            a[k++] = t[i++];
        while (j <= r)
            a[k++] = a[j++];
    }
};

int main()
{
    srand(time(NULL));
    {   int* v = new int[11];
        for (size_t i = 0; i < 6; i++)
            v[i] = rand() % 100;
        MergeSort(v, 6);
        for (size_t i = 0; i < 6; i++)
            printf("%d ", v[i]);
        puts("\n");

        for (size_t i = 0; i < 11; i++)
            v[i] = rand() % 100;

        MergeSort(v, 11);
        for (size_t i = 0; i < 11; i++)
            printf("%d ", v[i]);
        puts("\n");
        delete[] v;
        puts("\n");
    }


    float* v = new float[100];
    for(size_t k = 0; k < 1000; k++)
    {
        for (size_t i = 0; i < 100; i++)
            v[i] = rand() % 1000 - 500.0f;

        MergeSort(v, 100);
        for (size_t i = 1; i < 100; i++)
            if (v[i - 1] > v[i])
                puts("ITS FUCKED!!!!");
    }
    delete[] v;
    puts("\n");

    Combinations(5, 3);
}

template<typename T>
struct MergeSort2 {
    typedef size_t I;
    MergeSort2(T* arr, I size)
    {
        a = arr;
        t = new T[size];
        S(0, size - 1);
        delete[] t;
    }
private:
    T* a, * t;
    void S(I l, I r)
    {
        if (l >= r - 1)
            return;
        I m = (l + r) / 2;
        S(l, m);
        S(m + 1, r);

        I i = l, j = m + 1, k = 0;
        while (i <= m && j <= r)
            t[k++] = (a[i] < a[j] ? a[i++] : a[j++]);
        while (i <= m)
            t[k++] = a[i++];
        while (j <= r)
            t[k++] = a[j++];
        for (i = l, j = 0; i <= r; i++, j++)
            a[i] = t[j];
    }
};

struct Combinations2 {
    typedef size_t T;
    typedef size_t I;
    Combinations2(I N, I K)
    {
        n = N;
        k = K;
        s = new T[K + 1];
        s[0] = 0;
        B(1);
        delete[] s;
    }
private:
    T* s;
    I n, k;

    void D(I l)
    {
        for (I j = 1; j <= l; j++)
            std::cout << s[j] << ' ';
        puts("");
    }

    void B(I l) {
        for (T i = s[l - 1] + 1; i <= n; ++i) {
            s[l] = i;
            if (l == k)
                D(l);
            else
                B(l + 1);
        }
    }
};