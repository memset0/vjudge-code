#include <bits/stdc++.h>
using namespace std;
const int maxn = 80010;
set < int > a;
set < int > ::iterator it;
int n, x, y, mark;
int main() {
	scanf("%d", &n);
	int ans = 0;
	for (int i = 1; i <= n; i++) {
		scanf("%d%d", &x, &y);
		if (mark == x) a.insert(y);
		else if (a.size() == 0) {
			mark = x;
			a.insert(y);
		} else {
			it = a.lower_bound(y);
			if (it == a.end()) it--;
			else if (*it > y && it != a.begin()) it--;
//			printf("%d\n", *it);
			a.erase(it);
			ans = (ans + abs(*it - y)) % 1000000;
		}
	}
	printf("%d\n", ans);
	return 0;
}