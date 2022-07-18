// =================================
//   author: memset0
//   date: 2019.03.06 08:31:24
//   website: https://memset0.cn/
// =================================
#include <bits/stdc++.h>
#define ll long long
namespace ringo {
template <class T> inline void read(T &x) {
	x = 0; register char c = getchar(); register bool f = 0;
	while (!isdigit(c)) f ^= c == '-', c = getchar();
	while (isdigit(c)) x = x * 10 + c - '0', c = getchar();
	if (f) x = -x;
}
template <class T> inline void print(T x) {
	if (x < 0) putchar('-'), x = -x;
	if (x > 9) print(x / 10);
	putchar('0' + x % 10);
}
template <class T> inline void print(T x, char c) { print(x), putchar(c); }

const int N = 1e5 + 10;
int n, k;
ll a[N], f[100];
__int128 ans;

void print_ans(__int128 ans, int cnt) {
	std::vector <int> decimal;
	for (int i = 0; i < cnt; i++) {
		decimal.push_back(ans * 5 % 10);
		ans /= 2;
	}
	std::reverse(decimal.begin(), decimal.end());
	while (decimal.size() && !*--decimal.end()) decimal.pop_back();
	print(ans);
	if (decimal.size()) {
		putchar('.');
		for (std::vector <int> ::iterator it = decimal.begin(); it != decimal.end(); it++)
			putchar(48 + *it);
	} putchar('\n');
}

void insert(ll x) {
	for (int i = 63; i >= 0; i--)
		if ((x >> i) & 1) {
			if (f[i]) x ^= f[i];
			else { f[i] = x; break; }
		}
}

void main() {
	read(n), read(k);
	for (int i = 1; i <= n; i++) read(a[i]);
	if (k == 1) {
		bool f0 = false, flag;
		for (int k = 0; k < 64; k++) {
			flag = 0;
			for (int i = 1; i <= n; i++)
				if ((a[i] >> k) & 1)
					flag = 1;
			if (flag) {
				if (k) ans += 1ll << (k - 1);
				else f0 = 1;
			}
		}
		print(ans), puts(f0 ? ".5" : "");
	} else if (k == 2) {
		ll tmp = 0;
		bool f0, f1, f2, f3;
		for (int i = 1; i <= n; i++) tmp |= a[i];
		for (int i = 0; i < 64; i++)
			for (int j = 0; j < 64; j++)
				if (((tmp >> i) & 1) && ((tmp >> j) & 1)) {
					f0 = true, f1 = f2 = f3 = false;
					for (int k = 1, v1, v2; k <= n; k++) {
						v1 = (a[k] >> i) & 1;
						v2 = (a[k] >> j) & 1;
						if (v1) f1 = true;
						if (v2) f2 = true;
						f3 |= v1 && v2;
						f0 &= (v1 && v2) || (!v1 && !v2);
					}
					// printf("%d %d => %d %d %d %d\n", i, j, f0, f1, f2, f3);
					if (f0) {
						if (f3) ans += 1ull << (i + j + 1);
					} else if (f1 && f2) ans += 1ull << (i + j);
				}
		print_ans(ans, 2);
	} else {
		int cnt = 0, todo[100];
		for (int i = 1; i <= n; i++) insert(a[i]);
		for (int i = 0; i < 100; i++)
			if (f[i]) todo[cnt++] = f[i];
		for (int x = 0, y; x < (1 << cnt); x++) {
			y = 0;
			for (int i = 0; i < cnt; i++)
				if ((x >> i) & 1)
					y ^= todo[i];
			if (k == 3) ans += (__int128)y * y * y;
			if (k == 4) ans += (__int128)y * y * y * y;
			if (k == 5) ans += (__int128)y * y * y * y * y;
		}
		print_ans(ans, cnt);
	}
}

} signed main() { return ringo::main(), 0; }////