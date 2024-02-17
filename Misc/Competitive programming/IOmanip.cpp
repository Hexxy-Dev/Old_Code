#include <iostream>
#include <iomanip> 
using namespace std;
/*
1  
100.345 2006.008 2331.41592653498
//*/
int main() {
	int T; cin >> T;
	cout << setiosflags(ios::uppercase);
	cout << setw(0xf) << internal;
	while (T--) {
		double A; cin >> A;
		double B; cin >> B;
		double C; cin >> C;

		cout << resetiosflags(ios::uppercase) << setw(0x0) << setiosflags(ios::showbase) << hex
			<< (long long)A << endl;
		cout << resetiosflags(ios::showbase) << dec << fixed << setprecision(2) << setiosflags(ios::showpos)
			<< setiosflags(ios::left) << setfill('_') << setw(0xf)
			<< B << endl;
		cout << resetiosflags(ios::showpos) << resetiosflags(ios::left) << setiosflags(ios::uppercase)
			<< setw(0x0) << scientific << setprecision(9)
			<< C << endl;
	}
	return 0;

}