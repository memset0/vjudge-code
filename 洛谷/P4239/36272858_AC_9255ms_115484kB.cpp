// luogu-judger-enable-o2
// =================================
//   author: memset0
//   website: https://memset0.cn/
// =================================
#include <bits/stdc++.h>
#define int long long
#define double long double
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

const int N = 1e5 + 10, M = N << 2, mod = 1e9 + 7;
const double pi = acos(-1);
int n, rev[M];

inline int dec(int a, int b) { a -= b; return a < 0 ? a + mod : a; }
inline int sub(int a, int b) { a += b; return a >= mod ? a - mod : a; }
inline int mul(int a, int b) { return (ll)a * b - (ll)a * b / mod * mod; }
inline int inv(int x) { return x < 2 ? 1 : mul(mod - mod / x, inv(mod % x)); }
inline int fpow(int a, int b) { int s = 1; for (; b; b >>= 1, a = mul(a, a)) if (b & 1) s = mul(s, a); return s; }

struct complex {
	double x, y;
	inline complex() {}
	inline complex(double a, double b) { x = a, y = b; }
} w[M], iw[M];
inline complex operator + (const complex &a, const complex &b) { return complex(a.x + b.x, a.y + b.y); }
inline complex operator - (const complex &a, const complex &b) { return complex(a.x - b.x, a.y - b.y); }
inline complex operator * (const complex &a, const complex &b) { return complex(a.x * b.x - a.y * b.y, a.x * b.y + a.y * b.x); }

struct poly : std::vector <int> {
	using std::vector <int> ::vector;
	inline void in() { for (size_t i = 0; i < size(); i++) read(at(i)); }
	inline void out() { for (size_t i = 0; i < size(); i++) print(at(i), " \n"[i == size() - 1]); }
} a, b;

inline int init(int len) {
	int lim = 1, k = 0; while (lim < len) lim <<= 1, ++k;
	for (int i = 0; i < lim; i++) rev[i] = (rev[i >> 1] >> 1) | ((i & 1) << (k - 1));
	len = lim >> 1; 
	for (int i = 0; i < len; i++) w[i + len] = complex(cos(pi * i / len), sin(pi * i / len));
	for (int i = 0; i < len; i++) iw[i + len] = complex(cos(pi * i / len), -sin(pi * i / len));
	for (int i = len - 1; i >= 0; i--) w[i] = w[i << 1], iw[i] = iw[i << 1];
	return lim;
}

inline void fft(complex *a, int lim) {
	for (int i = 0; i < lim; i++) if (i < rev[i]) std::swap(a[i], a[rev[i]]);
	for (int len = 1; len < lim; len <<= 1)
		for (int i = 0; i < lim; i += (len << 1))
			for (int j = 0; j < len; j++) {
				complex x = a[i + j], y = w[j + len] * a[i + j + len];
				a[i + j] = x + y, a[i + j + len] = x - y;
			}
}

inline void ifft(complex *a, int lim) {
	for (int i = 0; i < lim; i++) if (i < rev[i]) std::swap(a[i], a[rev[i]]);
	for (int len = 1; len < lim; len <<= 1)
		for (int i = 0; i < lim; i += (len << 1))
			for (int j = 0; j < len; j++) {
				complex x = a[i + j], y = iw[j + len] * a[i + j + len];
				a[i + j] = x + y, a[i + j + len] = x - y;
			}
}

inline poly operator * (poly F, poly G) {
	static complex a[M], b[M], c[M], d[M], e[M], f[M], g[M], h[M];
	poly H(F.size() + G.size() - 1); int lim = init(H.size());
	for (int i = 0; i < lim; i++) {
		a[i].x = a[i].y = 0;
		b[i].x = b[i].y = 0;
		c[i].x = c[i].y = 0;
		d[i].x = d[i].y = 0;
		e[i].x = e[i].y = 0;
		f[i].x = f[i].y = 0;
		g[i].x = g[i].y = 0;
		h[i].x = h[i].y = 0;
	}
	for (int i = 0; i < F.size(); i++) a[i].x = F[i] >> 15, c[i].x = F[i] & 32767;
	for (int i = 0; i < G.size(); i++) b[i].x = G[i] >> 15, d[i].x = G[i] & 32767;
//	for (int i = 0; i < lim; i++) printf("%.2Lf %.2Lf %.2Lf %.2Lf\n", a[i].x, b[i].x, c[i].x, d[i].x);
	fft(a, lim), fft(b, lim), fft(c, lim), fft(d, lim);
	for (int i = 0; i < lim; i++) e[i] = a[i] * b[i], f[i] = b[i] * c[i], g[i] = a[i] * d[i], h[i] = c[i] * d[i];
	ifft(e, lim), ifft(f, lim), ifft(g, lim), ifft(h, lim);
	int p30 = (1ll << 30) % mod, p15 = (1ll << 15) % mod;
	for (int i = 0; i < H.size(); i++) {
		H[i] = (
			(ll)(e[i].x / lim + 0.5) % mod * p30 % mod +
			(ll)(f[i].x / lim + 0.5) % mod * p15 % mod +
			(ll)(g[i].x / lim + 0.5) % mod * p15 % mod +
			(ll)(h[i].x / lim + 0.5) % mod
		) % mod;
	} return H;
//	poly H(F.size() + G.size() - 1);
//	for (int i = 0; i < F.size(); i++)
//		for (int j = 0; j < G.size(); j++)
//			H[i + j] = (H[i + j] + (ll)F[i] * G[j]) % mod;
//	return H;
}

inline poly inv(const poly &f) {
    static int a[N << 2], b[N << 2];
    poly g(1, inv(f[0]));
    for (int len = 2; (len >> 1) < f.size(); len <<= 1) {
    	poly F, G;
    	for (int i = 0; i < len; i++) F.push_back(i < f.size() ? f[i] : 0);
    	for (int i = 0; i < len; i++) G.push_back(i < g.size() ? g[i] : 0);
//    	for (int i = 0; i < len; i++) print(F[i], " \n"[i == len - 1]);
//    	for (int i = 0; i < len; i++) print(G[i], " \n"[i == len - 1]);
    	F = F * G, F.resize(len);
//    	for (int i = 0; i < len; i++) print(F[i], " \n"[i == len - 1]);
		F = F * G, F.resize(len);
//    	for (int i = 0; i < len; i++) print(F[i], " \n"[i == len - 1]);
        for (int i = len >> 1; i < len; i++) g.push_back(dec(0, F[i]));
    } g.resize(f.size()); return g;
}

void main() { int n; read(n); poly f(n); f.in(), inv(f).out(); }

} signed main() {
#ifdef MEMSET0_LOCAL_ENVIRONMENT
	freopen("1.in", "r", stdin);
#endif
	return ringo::main(), 0;
}