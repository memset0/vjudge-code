#include <bits/stdc++.h>
template<class T> inline void read(T& x) {
	x = 0;
	register char c = getchar();
	register bool f = 0;
	while (!isdigit(c)) f ^= c == '-', c = getchar();
	while (isdigit(c)) x = x * 10 + c - '0', c = getchar();
	if (f) x = -x;
}

inline void check(int x, int l, int r) {
	// printf("check %d %d %d\n",x,l,r);
	assert(l <= x && x <= r);
}

int main() {
	int n, m, a, o, x, y;
	read(n), read(m);
	check(n, 1, 1e5);
	check(m, 1, 1e5);
	for (int i = 1; i <= n; i++) {
		read(a);
		check(a, 1, 1e4);
	}
	for (int i = 1; i < n; i++) { read(x), read(y); }
	for (int i = 1; i <= m; i++) {
		read(o), read(x), read(y);
		if (o) {
			check(x, 1, n);
			check(y, 1, 1e4);
		} else {
			check(x, 1, n);
			check(y, 0, n - 1);
		}
	}
}