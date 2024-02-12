#include <iostream>

using namespace std;

int main()
{
    int W;
    int H;
    cin >> W >> H;
    char arr[H][W];

    for(int i=-1;i<H+1;i++) {
        string line;
        getline(cin, line);
        cerr<<line<<endl;
            for(int j=0;j<line.length();j++){
                arr[i][j]=line[j];
            }
    }
    cerr<<endl;

    for(int i=0; i<H; i++) {
            for(int j=0;j<W;j++){
                cerr<<arr[i][j]<<" ";
            }
            cerr<<endl;
    }

    int j;
    for(int k=0;k<W;k+=3) {
        j=k;
        cerr<<endl;
        cout<<arr[0][j];
        for (int i=0;i<H;i++) {
            
            cerr<<arr[i][j]<<" .";
            if(arr[i][j-1]=='-'){
                j-=3;
                cerr<<"left!";
            } else if(arr[i][j+1]=='-'){
                j+=3;
                cerr<<"right!";
            }
            cerr<<endl;
        }
        cout<<arr[H-1][j]<<endl;
    }
}