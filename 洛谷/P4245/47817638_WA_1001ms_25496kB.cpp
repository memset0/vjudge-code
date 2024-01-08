// luogu-judger-enable-o2
// =================================
//   author: memset0
//   website: https://memset0.cn/
// =================================
#include <bits/stdc++.h>
#define ll long long
#define int long long
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
int n, m, mod;

inline int dec(int a, int b) { a -= b; return a < 0 ? a + mod : a; }
inline int sub(int a, int b) { a += b; return a >= mod ? a - mod : a; }
inline int mul(int a, int b) { return (ll)a * b  % mod;}
inline int inv(int x) { return x < 2 ? 1 : mul(mod - mod / x, inv(mod % x)); }
inline int fpow(int a, int b) { int s = 1; for (; b; b >>= 1, a = mul(a, a)) if (b & 1) s = mul(s, a); return s; }

namespace NTT {
	const int mod = 998244353;
	const ll p30 = 1 << 30, p15 = 1 << 15;
	int w[N << 2], rev[N << 2];
	inline int dec(int a, int b) { a -= b; return a < 0 ? a + mod : a; }
	inline int sub(int a, int b) { a += b; return a >= mod ? a - mod : a; }
	inline int mul(int a, int b) { return (ll)a * b - (ll)a * b / mod * mod; }
	inline int inv(int x) { return x < 2 ? 1 : mul(mod - mod / x, inv(mod % x)); }
	inline int fpow(int a, int b) { int s = 1; for (; b; b >>= 1, a = mul(a, a)) if (b & 1) s = mul(s, a); return s; }
	inline int init(int len) {
		int lim = 1, k = 0; while (lim < len) lim <<= 1, ++k;
		for (int i = 0; i < lim; i++) rev[i] = (rev[i >> 1] >> 1) | ((i & 1) << (k - 1));
		for (int wn, len = 1; len < lim; len <<= 1) {
			wn = fpow(3, (mod - 1) / (len << 1)), w[len] = 1;
			for (int i = 1; i < len; i++) w[i + len] = mul(w[i + len - 1], wn); 
		}
		return lim;
	}	
	inline void ntt(int *a, int lim) {
		for (int i = 0; i < lim; i++)
			if (i < rev[i]) std::swap(a[i], a[rev[i]]);
		for (int len = 1; len < lim; len <<= 1)
			for (int i = 0; i < lim; i += (len << 1))
				for (int j = 0; j < len; j++) {
					int x = a[i + j], y = mul(a[i + j + len], w[j + len]);
					a[i + j] = sub(x, y), a[i + j + len] = dec(x, y);
				}
	}
	inline void intt(int *a, int lim) {
		std::reverse(a + 1, a + lim);
		ntt(a, lim);
		int inv_lim = inv(lim);
		for (int i = 0; i < lim; i++)
			a[i] = mul(a[i], inv_lim);
	}
} // end namespace NTT 
using NTT::ntt;
using NTT::intt;

struct poly : std::vector <int> {
	using std::vector <int> ::vector;
	inline void in() {
		for (size_t i = 0; i < size(); i++)
			read(at(i)); 
	}
	inline void out() {
		for (size_t i = 0; i < size(); i++)
			print(at(i), " \n"[i == size() - 1]);
	}
};

inline poly operator * (const poly &F, const poly &G) {
	static int a[N << 2], b[N << 2], c[N << 2], d[N << 2], e[N << 2], f[N << 2], g[N << 2], h[N << 2];
	poly H(F.size() + G.size() - 1);
	int lim = NTT::init(H.size());
	for (int i = 0; i < lim; i++) {
		if (i < F.size()) {
			a[i] = F[i] >> 15, b[i] = F[i] & 32767;
		} else a[i] = b[i] = 0;
		if (i < G.size()) {
			c[i] = G[i] >> 15, d[i] = G[i] & 32767;
		} else c[i] = d[i] = 0;
	}
	ntt(a, lim), ntt(b, lim), ntt(c, lim), ntt(d, lim);
	for (int i = 0; i < lim; i++) {
		e[i] = (ll)a[i] * c[i] % 998244353;
		f[i] = (ll)a[i] * d[i] % 998244353;
		g[i] = (ll)b[i] * c[i] % 998244353;
		h[i] = (ll)b[i] * d[i] % 998244353;
	}
	intt(e, lim), intt(f, lim), intt(g, lim), intt(h, lim);
	for (int i = 0; i < H.size(); i++)
		H[i] = (e[i] * NTT::p30 % mod + f[i] * NTT::p15 % mod + g[i] * NTT::p15 % mod + h[i] % mod) % mod;
	return H;
}

void main() {
	int n, m;
	read(n), read(m), read(mod);
	poly a(n + 1), b(m + 1);
	a.in(), b.in();
	(a * b).out();
}

} signed main() {
#ifdef MEMSET0_LOCAL_ENVIRONMENT
	freopen("1.in", "r", stdin);
#endif
	return ringo::main(), 0;
}