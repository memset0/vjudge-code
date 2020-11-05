// =================================
//   author: memset0
//   date: 2018.12.27 13:10:21
//   website: https://memset0.cn/
// =================================
#include <bits/stdc++.h>
#define pb push_back
#define rep(i, l, r) for (register int i = l; i <= r; i++)

namespace ringo {
typedef long long ll;
typedef unsigned long long ull;

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
template <class T> inline void maxd(T &a, T b) { if (b > a) a = b; }
template <class T> inline void mind(T &a, T b) { if (b < a) a = b; }
template <class T> inline void print(T x, char c) { print(x), putchar(c); }
template <class T> inline T abs(const T &a) { if (a < 0) return -a; return a; }

const int N = 2e5 + 10, p = 998244353;
int n, m, k;
int a[N], fac[N], inv[N];

inline int C(int n, int m) { return (ll)fac[n] * inv[m] % p * inv[n - m] % p; }
int finv(int x) { return !x || x == 1 ? 1 : (ll)(p - p / x) * finv(p % x) % p; }

inline int fpow(int a, int b) {
	int s = 1;
	for (; b; b >>= 1, a = (ll)a * a % p)
		if (b & 1) s = (ll)s * a % p;
	return s;
}

inline void print_vector(std::vector <int> a) {
	for (size_t i = 0; i < a.size(); i++) print(a[i], " \n"[i == a.size() - 1]);
}

int _a[N << 2], _b[N << 2], _r[N << 2];
inline void ntt(int *a, int lim, int g) {
	for (int i = 0; i < lim; i++) if (i < _r[i]) std::swap(a[i], a[_r[i]]);
	for (int len = 1; len < lim; len <<= 1)
		for (int i = 0, wn = fpow(g, (p - 1) / (len << 1)); i < lim; i += (len << 1))
			for (int j = 0, w = 1; j < len; j++, w = (ll)w * wn % p) {
				int x = a[i + j], y = (ll)w * a[i + j + len] % p;
				a[i + j] = (x + y) % p, a[i + j + len] = (x - y + p) % p;
			}
}

inline std::vector <int> operator * (const std::vector <int> &a, const std::vector <int> &b) {
	int lim = 1, k = 0, a_size = (int)a.size(), b_size = (int)b.size();
	while (lim < a_size + b_size) lim <<= 1, ++k;
	for (int i = 0; i < a_size; i++) _a[i] = a[i];
	for (int i = 0; i < b_size; i++) _b[i] = b[i];
	for (int i = a_size; i < lim; i++) _a[i] = 0;
	for (int i = b_size; i < lim; i++) _b[i] = 0;
	for (int i = 0; i < lim; i++) _r[i] = (_r[i >> 1] >> 1) | ((i & 1) << (k - 1));
	ntt(_a, lim, 3), ntt(_b, lim, 3);
	for (int i = 0; i < lim; i++) _a[i] = (ll)_a[i] * _b[i] % p;
	ntt(_a, lim, 332748118), lim = finv(lim);
	std::vector <int> c(a_size + b_size - 1);
	for (int i = 0; i < a_size + b_size - 1; i++) c[i] = (ll)_a[i] * lim % p;
	// printf("  "), print_vector(a), printf("* "), print_vector(b), printf("= "), print_vector(c);
	return c;
}

std::vector <int> solve(int l, int r) {
	// printf("solve %d %d\n", l, r);
	if (l == r) {
		int u = l; std::vector <int> s;
		for (int i = 0; i < a[u]; i++)
			s.pb((ll)C(a[u], a[u] - i) * fac[a[u] - 1] % p * inv[a[u] - i - 1] % p);
		// printf(">> %d %d : ", u, a[u]), print_vector(s);
		return s;
	}
	int mid = (l + r) >> 1;
	std::vector <int> _l = solve(l, mid);
	std::vector <int> _r = solve(mid + 1, r);
	return _l * _r;
}

void main() {
	read(m), read(n), read(k);
	for (int i = 1; i <= m; i++) read(a[i]);
	fac[0] = fac[1] = inv[0] = inv[1] = 1;
	for (int i = 2; i <= n; i++) fac[i] = (ll)fac[i - 1] * i % p;
	for (int i = 2; i <= n; i++) inv[i] = (ll)(p - p / i) * inv[p % i] % p;
	for (int i = 2; i <= n; i++) inv[i] = (ll)inv[i] * inv[i - 1] % p;
	std::vector <int> v = solve(1, m);
	int ans = 0, mul = 1;
	for (int i = 1; i <= m; i++) mul = (ll)mul * fac[a[i]] % p;
	mul = finv(mul);
	for (size_t i = 0; i < v.size(); i++) v[i] = (ll)v[i] * fac[n - i] % p * mul % p;
	// printf(">>>> %d %d %d : %d\n", k, n, m, v.size());
	for (int i = k; i <= n - m; i++) ans = (ans + (ll)fpow(-1, i - k) * C(i, k) * v[i]) % p;
	// for (int i = k; i <= n - m; i++) {
	// 	printf("%d : %d %d %d\n", i, fpow(-1, i - k), C(i, k) , v[i]);
	// }
	print((ans + p) % p, '\n');
}

} signed main() { return ringo::main(), 0; }
