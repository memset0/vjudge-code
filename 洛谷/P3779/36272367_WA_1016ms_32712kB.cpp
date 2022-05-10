// luogu-judger-enable-o2
// =================================
//   author: memset0
//   date: 2019.06.23 19:15:25
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

const double eps = 1e-8, pi = acos(-1);
const int N = 2e5 + 10, M = 21, L = 8e5 + 10;
int T, n, m, rev[L];

struct complex {
	double x, y;
	inline complex operator+(const complex &o) { return { x + o.x, y + o.y }; }
	inline complex operator-(const complex &o) { return { x - o.x, y - o.y }; }
	inline complex operator*(const complex &o) { return { x * o.x - y * o.y, x * o.y + y * o.x }; }
} w1[L], w2[L];

struct poly {
	double a[L];
	int n, p;
	inline double get(int k) { k -= p; return k < 0 || k >= n ? 0 : a[k]; }
    inline void print() { for (int i = 0; i < n; i++) printf("%.2lf%c", a[i], " \n"[i == n - 1]); }
} f, g;

inline void fft(complex *a, int lim, complex *w) {
	for (int i = 0; i < lim; i++) if (i < rev[i]) std::swap(a[i], a[rev[i]]);
	for (int len = 1; len < lim; len <<= 1)
		for (int i = 0; i < lim; i += (len << 1))
			for (int j = 0; j < len; j++) {
				complex x = a[i + j], y = w[j + len] * a[i + j + len];
				a[i + j] = x + y, a[i + j + len] = x - y;
			}
}

inline void mul(poly &f, poly &g, poly &h) {
	static complex a[L], b[L];
	int len = (f.n + g.n - 1), lim = 1, k = 0;
	while (lim < len) lim <<= 1, ++k;
	for (int i = 0; i < lim; i++) rev[i] = (rev[i >> 1] >> 1) | ((i & 1) << (k - 1));
	for (int len = 1; len < lim; len <<= 1) {
		w1[len] = w2[len] = { 1, 0 };
		complex wn1 = { cos(pi / len),  sin(pi / len) };
		complex wn2 = { cos(pi / len), -sin(pi / len) };
		for (int i = 1; i < len; i++) {
			w1[i + len] = w1[i + len - 1] * wn1;
			w2[i + len] = w2[i + len - 1] * wn2;
		}
	}
	// printf(">> mul n=%d m=%d l=%d lim=%d k=%d | %u %u %u \n", f.n, g.n, len, lim, k, &f, &g, &h), f.print(), g.print();
	for (int i = 0; i < lim; i++) {
		a[i] = { i < f.n ? f.a[i] : 0, 0 };
		b[i] = { i < g.n ? g.a[i] : 0, 0 };
	}
	fft(a, lim, w1), fft(b, lim, w1);
	for (int i = 0; i < lim; i++) a[i] = a[i] * b[i];
	fft(a, lim, w2);
    int flag = false, first = 0, second = len;
    for (int i = 0; i < lim; i++) {
        a[i].x /= lim;
        if (!flag && a[i].x > eps) flag = true, first = i;
        if (flag && a[i].x <= eps) flag = false, second = i;
    }
	h.n = second - first, h.p = f.p + g.p + first;
    for (int i = 0; i < h.n; i++) h.a[i] = a[i + first].x;
    // h.print();
}

inline void fpow(poly &a, int b, poly &s) {
	s.n = s.a[0] = 1, s.p = 0;
	for (; b; b >>= 1, mul(a, a, a))
		if (b & 1) mul(s, a, s);
}

void main() {
	for (read(T); T--; ) {
		read(n), read(m);
        // memset(f.a, 0, sizeof(f.a));
        // memset(g.a, 0, sizeof(g.a)); 
        f.n = n, f.p = 0; for (int i = 0; i < n; i++) f.a[i] = 1.0 / n;
        // f.print();
		fpow(f, m, g);
        // g.print();
		for (int i = 1; i <= (n - 1) * m; i++) g.a[i] += g.a[i - 1];
		for (int i = 1, a, b; i <= 10; i++) read(a), read(b), printf("%.6lf\n", g.get(b) - g.get(a - 1));
	}
}

} signed main() {
#ifdef MEMSET0_LOCAL_ENVIRONMENT
	freopen("1.in", "r", stdin);
#endif
	return ringo::main(), 0;
}