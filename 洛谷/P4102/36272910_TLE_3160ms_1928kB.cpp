// luogu-judger-enable-o2
// =================================
//   author: memset0
//   date: 2019.01.17 17:10:00
//   website: https://memset0.cn/
// =================================
#include <bits/stdc++.h>
#pragma GCC target("avx")
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

const int N = 110, mod = 1e9 + 7;
int n, m, k, q;

struct pair {
	struct matrix {
		struct poly {
			int f[3];
			inline void inc() { ++f[0], ++f[1], ++f[2]; }
			inline void operator += (const poly &other) {
				for (int i = 0; i < 3; i++) (f[i] += other.f[i]) %= mod;
			}
			friend inline poly operator + (const poly &a, const poly &b) {
				static poly s;
				for (int i = 0; i < 3; i++) s.f[i] = (a.f[i] + b.f[i]) % mod;
				return s;
			}
			friend inline poly operator * (const poly &a, const poly &b) {
				static poly s;
				s.f[0] = (ll)a.f[0] * b.f[0] % mod;
				s.f[1] = ((ll)a.f[0] * b.f[1] + (ll)a.f[1] * b.f[0]) % mod;
				s.f[2] = ((ll)a.f[2] * b.f[0] + (ll)a.f[0] * b.f[2]) % mod;
				s.f[2] = (s.f[2] + 2LL * a.f[1] * b.f[1] % mod) % mod;
				return s;
			}
		} a[N][N];
		inline void inc(int x, int y) { a[x][y].inc(); }
		inline int ask(int x, int y) { return a[x][y].f[2]; }
		inline void print() {
			for (int i = 1; i <= n; i++)
				for (int j = 1; j <= n; j++)
					printf("[%d %d %d]%c", a[i][j].f[0], a[i][j].f[1], a[i][j].f[2], " \n"[j == n]);
		}
		inline void operator += (const matrix &other) {
			for (int i = 1; i <= n; i++)
				for (int j = 1; j <= n; j++)
					a[i][j] += other.a[i][j];
		}
		friend inline matrix operator + (const matrix &a, const matrix &b) {
			static matrix c;
			for (int i = 1; i <= n; i++)
				for (int j = 1; j <= n; j++)
					c.a[i][j] = a.a[i][j] + b.a[i][j];
			return c;
		}
		friend inline matrix operator * (const matrix &a, const matrix &b) {
			static matrix c;
			for (int i = 1; i <= n; i++)
 				for (int j = 1; j <= n; j++)
					for (int k = 0; k < 3; k++)
						c.a[i][j].f[k] = 0;
			for (int i = 1; i <= n; i++)
				for (int j = 1; j <= n; j++)
					for (int k = 1; k <= n; k++)
						c.a[i][j] += a.a[i][k] * b.a[k][j];
			return c;
		}
	} A, B;
	inline int ask(int x, int y) { return B.ask(x, y); }
	inline void inc(int x, int y) { A.inc(x, y), B.inc(x, y); }
	friend inline pair operator * (const pair &a, const pair &b) {
		return (pair){a.A * b.A, a.B + a.A * b.B};
	}
} a, s;

void main() {
	read(n), read(m), read(k), read(q);
	for (int i = 1, u, v; i <= m; i++) read(u), read(v), a.inc(u, v);
	// a.A.print();
	s = a;
	for (--k; k; k >>= 1, a = a * a) if (k & 1) s = s * a;
	for (int i = 1, u, v; i <= q; i++) read(u), read(v), print(s.ask(u, v), '\n');
}

} signed main() { return ringo::main(), 0; }