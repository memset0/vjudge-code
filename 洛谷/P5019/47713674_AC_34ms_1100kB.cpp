// luogu-judger-enable-o2
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#include <iostream>

void openFile() { freopen("road.in", "r", stdin); freopen("road.out", "w", stdout); }
void closeFile() { fclose(stdin); fclose(stdout); }

inline int read() {
	char c = getchar(); int n = 0;
	while (c < '0' || c > '9') { c = getchar(); }
	while (c >= '0' && c <= '9') { n = (n << 1) + (n << 3) + (c & 15); c = getchar(); }
	return n;
}

typedef long long lol;

const int maxN = 200005;

int n, a[maxN];
lol ans;

int main() {
	n = read();
	for (register int i = 1; i <= n; i++) { a[i] = read(); }
	ans = a[1];
	for (register int i = 2; i <= n; i++) {
		if (a[i - 1] < a[i]) { ans += a[i] - a[i - 1]; }
	}
	printf("%lld\n", ans);
	closeFile();
	return 0;
}
