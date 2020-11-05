#include <bits/stdc++.h>
#define LL long long
#define pb push_back
using namespace std;
inline int read() {
	int v = 0, f = 1;
	char c = getchar();
	while (c < '0' || c > '9') {
		if (c == '-') f = -1;
		c = getchar();
	}
	while (c >= '0' && c <= '9') {
		v = v * 10 + c - '0';
		c = getchar();
	}
	return v * f;
}
vector<string> ans;
int main() {
	LL a, b;
	cin >> a >> b;
	if (a == b) {
		puts("0");
		return 0;
	}
	while (1) {
		if (a == b) break;
		if (a % 2 == 0 && b % 2 == 0) {
			a >>= 1;
			b >>= 1;
			continue;
		}
		if (a % 2 == 0) {
			ans.pb("B+=B");
			a >>= 1;
			continue;
		}
		if (b % 2 == 0) {
			ans.pb("A+=A");
			b >>= 1;
			continue;
		}
		if (a == b && a == 1) break;
		if (a < b) {
			ans.pb("B+=A");
			b += a;
			continue;
		} else {
			ans.pb("A+=B");
			a += b;
		}
		continue;
	}
	printf("%d\n", ans.size());
	for (int i = 0; i < ans.size(); i++) { printf("%s\n", ans[i].c_str()); }
}