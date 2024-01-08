// luogu-judger-enable-o2
// =================================
//   author: memset0
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

const int N = 1e5 + 10;
int mod;

struct poly : std::vector <int> {
	using std::vector <int> ::vector;
	inline void in() { for (int i = 0; i < size(); i++) read(at(i)); }
	inline void out() const { for (int i = 0; i < size(); i++) print(at(i), " \n"[i == size() - 1]); }
};

namespace FFT {
	const int M = N << 2;
	const double pi = acos(-1);
	ll p30 = 1ll << 30, p15 = 1ll << 15;
	struct complex {
		double a, b;
		inline complex() {}
		inline complex(double x) { a = x, b = 0; }
		inline complex(double x, double y) { a = x, b = y; }
		inline complex operator + (const complex &other) const { return complex(a + other.a, b + other.b); }
		inline complex operator - (const complex &other) const { return complex(a - other.a, b - other.b); }
		inline complex operator * (const complex &other) const { return complex(a * other.a - b * other.b, a * other.b + b * other.a); }
	} w[M], iw[M], a[M], b[M], c[M], d[M], e[M], f[M], g[M], h[M];
	int lim, rev[M];
	inline int init(int len) {
		int lim = 1, k = 0; while (lim < len) lim <<= 1, ++k;
		for (int i = 0; i < lim; i++) rev[i] = (rev[i >> 1] >> 1) | ((i & 1) << (k - 1));
		len = lim >> 1;
		for (int i = 0; i < len; i++) w[i + len] = complex(cos(pi * i / len), sin(pi * i / len));
		for (int i = 0; i < len; i++) iw[i + len] = complex(cos(pi * i / len), -sin(pi * i / len));
		for (int i = len - 1; i >= 0; i--) w[i] = w[i << 1], iw[i] = iw[i << 1];
		return lim;
	}
	inline void fft(complex *a) {
		for (int i = 0; i < lim; i++) if (i < rev[i]) std::swap(a[i], a[rev[i]]);
		for (int len = 1; len < lim; len <<= 1)
			for (int i = 0; i < lim; i += (len << 1))
				for (int j = 0; j < len; j++) {
					complex x = a[i + j], y = a[i + j + len] * w[j + len];
					a[i + j] = x + y, a[i + j + len] = x - y;
				}
	}
	inline void ifft(complex *a) {
		for (int i = 0; i < lim; i++) if (i < rev[i]) std::swap(a[i], a[rev[i]]);
		for (int len = 1; len < lim; len <<= 1)
			for (int i = 0; i < lim; i += (len << 1))
				for (int j = 0; j < len; j++) {
					complex x = a[i + j], y = a[i + j + len] * iw[j + len];
					a[i + j] = x + y, a[i + j + len] = x - y;
				}
		for (int i = 0; i < lim; i++) a[i].a /= lim;
	}
	inline poly operator * (const poly &F, const poly &G) {
		poly H(F.size() + G.size() - 1); lim = init(H.size());
		for (int i = 0; i < F.size(); i++) a[i] = F[i] >> 15, b[i] = F[i] & 32767;
		for (int i = 0; i < G.size(); i++) c[i] = G[i] >> 15, d[i] = G[i] & 32767;
		for (int i = F.size(); i < lim; i++) a[i] = b[i] = 0;
		for (int i = G.size(); i < lim; i++) c[i] = d[i] = 0;
		fft(a), fft(b), fft(c), fft(d);
		for (int i = 0; i < lim; i++)
			e[i] = a[i] * c[i], f[i] = a[i] * d[i], g[i] = b[i] * c[i], h[i] = b[i] * d[i];
		ifft(e), ifft(f), ifft(g), ifft(h);
		p30 %= mod, p15 %= mod;
		for (int i = 0; i < H.size(); i++)
			H[i] = ((ll)(e[i].a + 0.5) % mod * p30 % mod + (ll)(f[i].a + 0.5) % mod * p15 % mod + (ll)(g[i].a + 0.5) % mod * p15 % mod + (ll)(h[i].a + 0.5)) % mod;
		return H;
	}
}
using FFT::operator *;


void main() {
	int n, m;
	read(n), read(m), read(mod);
	poly a(n + 1), b(m + 1);
	a.in(), b.in();
	for (int i = 0; i < a.size(); i++) a[i] %= mod;
	for (int i = 0; i < b.size(); i++) b[i] %= mod;
	(a * b).out();
}

} signed main() {
#ifdef MEMSET0_LOCAL_ENVIRONMENT
	freopen("1.in", "r", stdin);
#endif
	return ringo::main(), 0;
}