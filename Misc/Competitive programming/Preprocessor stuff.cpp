/* Enter your macros here */
#include <string>

#define INF 10000000

#define toStr(x) toStrFunc(#x)

std::string toStrFunc(std::string x) { return std::move(x); }

#define io(x) cin >> x

#define foreach(v, i) for(int i = 0; i < v.size(); i++)

#define FUNCTION(name, condition) void name(int& value, const int& comp) { if(!(value condition comp)) value = comp; }

#include <iostream>
#include <vector>
using namespace std;

#if !defined toStr || !defined io || !defined FUNCTION || !defined INF
#error Missing preprocessor definitions
#endif 

FUNCTION(minimum, < )
FUNCTION(maximum, > )

int main() {
	int n; cin >> n;
	vector<int> v(n);
	foreach(v, i) {
		io(v)[i];
	}
	int mn = INF;
	int mx = -INF;
	foreach(v, i) {
		minimum(mn, v[i]);
		maximum(mx, v[i]);
	}
	int ans = mx - mn;
	cout << toStr(Result = ) << ' ' << ans;
	return 0;

}