// =================================
//   author: memset0
//   date: 2019.01.17 17:10:00
//   website: https://memset0.cn/
// =================================
#include <bits/stdc++.h>
#define pb push_back
#define rep(i, l, r) for (register int i = l; i <= r; i++)

namespace ringo {
typedef long long ll;
typedef unsigned long long ull;

inline char read() {
	static const int IN_LEN = 1000000; static char buf[IN_LEN], *s, *t;
	return (s == t ? t = (s = buf) + fread(buf, 1, IN_LEN, stdin), (s == t ? -1 : *s++) : *s++);
}
template <class T> inline void read(T &x) {
	static bool f; static char c;
	for (f = 0, c = read(); !isdigit(c); c = read()) { f ^= c == '-'; if (c == -1) return; }
	for (x = 0; isdigit(c); c = read()) x = ((x + (x << 2)) << 1) + (c ^ '0');
	if (f) x = -x;
}
const int OUT_LEN = 10000000; char obuf[OUT_LEN], *ooh = obuf;
inline void print(char c) {
	if (ooh == obuf + OUT_LEN) fwrite(obuf, 1, OUT_LEN, stdout), ooh = obuf;
	*ooh++ = c;
}
template<class T> inline void print(T x) {
	static int buf[30], cnt;
	if (!x) { print('0'); return; }
	if (x < 0) print('-'), x = -x;
	for (cnt = 0; x; x /= 10) buf[++cnt] = x % 10 + '0';
	while (cnt) print((char)buf[cnt--]);
}
inline void flush() { fwrite(obuf, 1, ooh - obuf, stdout); }
template <class T> inline void maxd(T &a, T b) { if (b > a) a = b; }
template <class T> inline void mind(T &a, T b) { if (b < a) a = b; }
template <class T> inline void print(T x, char c) { print(x), print(c); }
template <class T> inline T abs(const T &a) { if (a < 0) return -a; return a; }

const int N = 110, mod = 1e9 + 7;
int n, m, k, q;

struct pair {
	struct matrix {
		struct poly {
			int f[3];
			inline void inc() { ++f[0], ++f[1], ++f[2]; }
			inline void operator += (const poly &other) {
				f[0] += other.f[0]; if (f[0] >= mod) f[0] -= mod;
				f[1] += other.f[1]; if (f[1] >= mod) f[1] -= mod;
				f[2] += other.f[2]; if (f[2] >= mod) f[2] -= mod;
			}
			friend inline poly operator + (const poly &a, const poly &b) {
				static poly s;
				s.f[0] = a.f[0] + b.f[0]; if (s.f[0] >= mod) s.f[0] -= mod;
				s.f[1] = a.f[1] + b.f[1]; if (s.f[1] >= mod) s.f[1] -= mod;
				s.f[2] = a.f[2] + b.f[2]; if (s.f[2] >= mod) s.f[2] -= mod;
				return s;
			}
			friend inline poly operator * (const poly &a, const poly &b) {
				static poly s;
				s.f[0] = (ll)a.f[0] * b.f[0] % mod;
				s.f[1] = ((ll)a.f[0] * b.f[1] + (ll)a.f[1] * b.f[0]) % mod;
				s.f[2] = ((ll)a.f[2] * b.f[0] + (ll)a.f[0] * b.f[2] + 2LL * a.f[1] * b.f[1]) % mod;
				return s;
			}
		} a[100][100];
		inline void inc(int x, int y) { a[x][y].inc(); }
		inline int ask(int x, int y) { return a[x][y].f[2]; }
		inline void operator += (const matrix &other) {
			for (register int i = 0; i < n; i++)
				for (register int j = 0; j < n; j++)
					a[i][j] += other.a[i][j];
		}
		friend inline matrix operator + (const matrix &a, const matrix &b) {
			static matrix c;
			for (register int i = 0; i < n; i++)
				for (register int j = 0; j < n; j++)
					c.a[i][j] = a.a[i][j] + b.a[i][j];
			return c;
		}
		friend inline matrix operator * (const matrix &a, const matrix &b) {
			static matrix c;
			for (register int i = 0; i < n; i++)
 				for (register int j = 0; j < n; j++)
					c.a[i][j].f[0] = c.a[i][j].f[1] = c.a[i][j].f[2] = 0;
			for (register int i = 0; i < n; i++)
				for (register int k = 0; k < n; k++)
					for (register int j = 0; j < n; j++)
						c.a[i][j] += a.a[i][k] * b.a[k][j];
			return c;
		}
	} A, B;
	inline int ask(int x, int y) { return B.ask(x, y); }
	inline void inc(int x, int y) { A.inc(x, y), B.inc(x, y); }
	inline void operator *= (const pair &other) {
		A = A * other.A, B += A * other.B;
	}
	friend inline pair operator * (const pair &a, const pair &b) {
		return (pair){a.A * b.A, a.B + a.A * b.B};
	}
} a, s;

void main() {
	read(n), read(m), read(k), read(q);
	for (int i = 1, u, v; i <= m; i++) read(u), read(v), --u, --v, a.inc(u, v);
	for (s = a, --k; k; k >>= 1, a = a * a) if (k & 1) s = s * a;
	for (int i = 1, u, v; i <= q; i++) read(u), read(v), --u, --v, print(s.ask(u, v), '\n');
}

} signed main() { return ringo::main(), ringo::flush(), 0; }
