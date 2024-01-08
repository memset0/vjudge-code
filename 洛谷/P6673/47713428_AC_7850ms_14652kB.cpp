// =================================
//   author: memset0
//   date: 2019.06.30 17:44:08
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
	x = 0; char c = getchar(); bool f = 0;
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
template <class T> inline void print(T a, int l, int r, std::string s = "") {
	if (s != "") std::cout << s << ": ";
	for (int i = l; i <= r; i++) print(a[i], " \n"[i == r]);
}

const int N = 6e5 + 10, M = 15;
int n, m, t, mod, b[M][M];

inline int dec(int a, int b) { a -= b; return a < 0 ? a + mod : a; }
inline int inc(int a, int b) { a += b; return a >= mod ? a - mod : a; }
inline int mul(int a, int b) { return (ll)a * b - (ll)a * b / mod * mod; }
inline int fpow(int a, int b) { int s = 1; for (; b; b >>= 1, a = mul(a, a)) if (b & 1) s = mul(s, a); return s; }

struct poly {
	int w0, w1, w2;
	inline int to_int() { return dec(w0, w1); }
	inline poly operator+(const poly &other) { return {inc(w0, other.w0), inc(w1, other.w1), inc(w2, other.w2)}; }
	inline poly operator*(const poly &other) {
		return {
			inc(mul(w0, other.w0), inc(mul(w1, other.w2), mul(w2, other.w1))),
			inc(mul(w0, other.w1), inc(mul(w1, other.w0), mul(w2, other.w2))),
			inc(mul(w0, other.w2), inc(mul(w1, other.w1), mul(w2, other.w0)))
		};
	}
} f[N], g[N];

inline poly fpow(poly a, int b) {
	poly s{1, 0, 0};
	for (; b; b >>= 1, a = a * a) if (b & 1) s = s * a;
	return s;
}

inline int get_inv(int x) {
	for (ll res = 1; ; res += mod) if (res % x == 0) return (res / x) % mod;
}

void fwt(poly *a, int flag) {
	for (int len = 1; len < n; len *= 3)
		for (int i = 0; i < n; i += len * 3)
			for (int j = 0; j < len; j++) {
				// printf(">> %d %d %d\n", i + j, i + j + len, i + j + len + len);
				poly x = a[i + j], y = a[i + j + len], z = a[i + j + len * 2];
				// printf("   (%d %d %d) (%d %d %d) (%d %d %d)\n", x.w0, x.w1, x.w2, y.w0, y.w1, y.w2, z.w0, z.w1, z.w2);
				if (flag == 1) {
					a[i + j] = x + y + z;
					a[i + j + len] = x + poly{y.w2, y.w0, y.w1} + poly{z.w1, z.w2, z.w0};
					a[i + j + len * 2] = x + poly{y.w1, y.w2, y.w0} + poly{z.w2, z.w0, z.w1};
				} else {
					a[i + j] = x + y + z;
					a[i + j + len] = x + poly{y.w1, y.w2, y.w0} + poly{z.w2, z.w0, z.w1};
					a[i + j + len * 2] = x + poly{y.w2, y.w0, y.w1} + poly{z.w1, z.w2, z.w0};
				}
				x = a[i + j], y = a[i + j + len], z = a[i + j + len * 2];
				// printf("   (%d %d %d) (%d %d %d) (%d %d %d)\n", x.w0, x.w1, x.w2, y.w0, y.w1, y.w2, z.w0, z.w1, z.w2);
			}
}

void main() {
	read(m), read(t), read(mod), n = 1;
	for (int i = 1; i <= m; i++) n *= 3;
	for (int i = 0; i < n; i++) read(f[i].w0);
	for (int i = 0; i <= m; i++)
		for (int j = 0; i + j <= m; j++)
			read(b[i][j]);
	for (int i = 0; i < n; i++) {
		static int cnt[3];
		cnt[0] = cnt[1] = cnt[2] = 0;
		for (int t = i; t; t /= 3) cnt[t % 3]++;
		g[i].w0 = b[cnt[1]][cnt[2]];
	}
	fwt(f, 1), fwt(g, 1);
	// for (int i = 0; i < n; i++) printf("{ %d %d %d }\n", f[i].w0, f[i].w1, f[i].w2);
	for (int i = 0; i < n; i++) f[i] = f[i] * fpow(g[i], t);
	fwt(f, -1);
	int inv_3 = get_inv(3), inv_n = fpow(inv_3, m);
	for (int i = 0; i < n; i++) print(mul(f[i].to_int(), inv_n), '\n');
	// for (int i = 0; i < n; i++) printf("{ %d %d %d }\n", f[i].w0, f[i].w1, f[i].w2);
}

} signed main() {
#ifdef MEMSET0_LOCAL_ENVIRONMENT
	freopen("1.in", "r", stdin);
#endif
	return ringo::main(), 0;
}