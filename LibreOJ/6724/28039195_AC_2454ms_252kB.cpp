#include <bits/stdc++.h>
template<class T> inline void read(T& x) {
	x = 0;
	register char c = getchar();
	register bool f = 0;
	while (!isdigit(c)) f ^= c == '-', c = getchar();
	while (isdigit(c)) x = x * 10 + c - '0', c = getchar();
	if (f) x = -x;
}
template<class T> inline void print(T x) {
	if (x < 0) putchar('-'), x = -x;
	if (x > 9) print(x / 10);
	putchar(x % 10 + '0');
}
template<class T> inline void print(T x, char c) { print(x), putchar(c); }
const int N = 1e4 + 10;
int T, p, x, cnt[N];
long long ans;
int f(int p, int x) {
	if (p % 4 == 1) {
		return x ? p - 1 : (p << 1) - 1;
	} else {
		return x ? p + 1 : 1;
	}
}
int main() {
#ifdef memset0
	freopen("C.in", "r", stdin);
#endif
	read(T);
	while (T--) {
		read(p), read(x), ans = 1;
		for (int i = 3; i * i <= p; i++)
			if (p % i == 0) { p /= i, ans = ans * f(i, x % i); }
		if (p > 1) ans = ans * f(p, x % p);
		print(ans, '\n');
	}
}
