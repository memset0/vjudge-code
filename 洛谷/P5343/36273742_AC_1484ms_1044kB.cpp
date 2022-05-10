// luogu-judger-enable-o2
// luogu-judger-enable-o2
// =================================
//   author: memset0
//   date: 2019.05.04 13:29:22
//   website: https://memset0.cn/
// =================================
#include <bits/stdc++.h>
#define ll long long
#define debug(...) ((void)0)
#ifndef debug
#define debug(...) fprintf(stderr,__VA_ARGS__)
#endif
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
template <class T> inline void print(T *a, int l, int r, std::string s = "") {
	if (s != "") std::cout << s << ": ";
	for (int i = l; i <= r; i++) print(a[i], " \n"[i == r]);
}

const int N = 110, mod = 1e9 + 7;
ll n;
std::set<int> set;
int m, n1, n2, a[N];

struct matrix {
	int a[N][N];
	friend inline matrix operator*(const matrix &a, const matrix &b) {
		matrix c; memset(c.a, 0, sizeof c.a);
		for (int i = 0; i < N; i++)
			for (int j = 0; j < N; j++)
				for (int k = 0; k < N; k++) {
					c.a[i][j] = (c.a[i][j] + (ll)a.a[i][k] * b.a[k][j]) % mod;
				}
		return c;
	}
	template <class T> friend inline matrix fpow(matrix a, T b) {
		matrix s; memset(s.a, 0, sizeof s.a);
		for (int i = 0; i < N; i++) s.a[i][i] = 1;
		for (; b; b >>= 1, a = a * a) if (b & 1) s = s * a;
		return s;
	}
	void out() {
		for (int i = 0; i < N; i++)
			for (int j = 0; j < N; j++)
				if (a[i][j])
					printf("%d %d : %d\n", i, j, a[i][j]);
		// for (int i = 0; i < N; i++) {
		// 	for (int j = 0; j < N; j++)
		// 		print(a[i][j], ' ');
		// 	putchar('\n');
		// }
	}
} p, s, e;

void main() {
	read(n);
	read(n1);
	for (int x, i = 1; i <= n1; i++) {
		read(x);
		set.insert(x);
	}
	read(n2);
	for (int x, i = 1; i <= n2; i++) {
		read(x);
		if (set.count(x)) a[++m] = x;
	}
	s.a[0][0] = 1;
	for (int i = 1; i < N; i++)
		p.a[i][i - 1] = 1;
	for (int i = 1; i <= m; i++) {
		p.a[0][a[i] - 1] = 1;
	}
	e = fpow(p, n) * s;
	print(e.a[0][0], '\n');
}

} signed main() {
#ifdef MEMSET0_LOCAL_ENVIRONMENT
	freopen("1.in", "r", stdin);
#endif
	return ringo::main(), 0;
}