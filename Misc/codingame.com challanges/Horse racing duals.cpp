#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

int main()
{
    int N;
    cin >> N;

    int arr[N];
    for (int i = 0; i < N; i++) {
        int Pi;
        cin >> Pi;
        arr[i]=Pi;
    }

    std::vector<int> vect (arr,arr+N);
    std::sort(vect.begin(), vect.begin()+N);
    int k=0;
    for (std::vector<int>::iterator it=vect.begin(); it!=vect.end(); ++it){
        arr[k]=*it;
        k++;
    }

    int diff[N-1];
    for (int i = 0; i < N-1; i++) {
        diff[i]=arr[i+1]-arr[i];
    }

    int mini=0;
    for (int i = 0; i < N-1; i++) {
        if(diff[mini]>diff[i])
            mini=i;
    }

    cout<<diff[mini];
}