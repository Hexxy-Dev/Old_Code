#include <iostream>

using namespace std;

int main()
{
    int n,k,i,j;
    cin>>n; // size
    char f[n+1][n+1];
    cin>>k; // thickness

    for(i=0;i<=n;i++){
        for(j=0;j<=n;j++){
            f[i][j]=' ';
        }
    }

    for(i=0;i<=n/2+1;i++){
        for(j=0;j<=k;j++){
            f[i+j][i]='#';
            f[i][i+j]='#';

            f[i+j][n-1-i]='#';
            f[i][n-1-i-j]='#';

            f[n-1-i-j][i]='#';
            f[n-1-i][i+j]='#';

            f[n-1-i-j][n-1-i]='#';
            f[n-1-i][n-1-i-j]='#';
        }
    }

    for(i=0;i<n;i++){
        for(j=0;j<n;j++){
            cout<<f[i][j]<<" ";
        }
        cout<<endl;
    }
}
