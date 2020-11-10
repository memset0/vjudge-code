#include <bits/stdc++.h>
using namespace std;
 
const int inf = 1e9;
const string target = "atcoder";
 
int T;
string a;
 
int calc(int k, char c) {
	for (int i = 0; i + k < a.length(); i++) {
		if (a[i + k] > c) { return i; }
	}
	return inf;
}
 
int move(int k, char c) {
	for (int i = 0; i + k < a.length(); i++) {
		if (a[i + k] == c) {
			for (int j = 1; j <= i; j++) { a[j + k] = a[j + k - 1]; }
			a[k] = c;
			return i;
		}
	}
	return -1;
}
 
int main() {
#ifdef local
	freopen("1.in", "r", stdin);
#endif
	ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
 
	cin >> T;
	while (T--) {
		cin >> a;
 
		int ans = inf;
		int sum = 0;
 
		if (a > target) {
			cout << 0 << endl;
			goto next;
		}
		for (int i = 0; i < target.length() && i < a.length(); i++) {
			ans = min(ans, sum + calc(i, target[i]));
 
			int mov = move(i, target[i]);
			if (mov == -1) {
				break;
			} else {
				sum += mov;
			}
		}
		cout << (ans >= inf ? -1 : ans) << endl;
 
	next:
		continue;
	}
 
	return 0;
}