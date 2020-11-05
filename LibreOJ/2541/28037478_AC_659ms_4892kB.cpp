// =================================
//   author: memset0
//   date: 2019.01.16 18:25:25
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

const int N = 8e5 + 10, mod = 998244353;
typedef std::vector <int> vector;

int n, ans, a[N];
int _f[N], _g[N], _r[N], _w[N];

int inv(int x) {
	if (!x || x == 1) return 1;
	return (ll)(mod - mod / x) * inv(mod % x) % mod;
}

int fpow(int a, int b) {
	int s = 1;
	for (; b; b >>= 1, a = (ll)a * a % mod)
		if (b & 1) s = (ll)s * a % mod;
	return s;
}

inline void ntt(int *a, int lim) {
	for (int i = 0; i < lim; i++) if (i < _r[i]) std::swap(a[i], a[_r[i]]);
	for (int len = 1; len < lim; len <<= 1)
		for (int i = 0; i < lim; i += (len << 1))
			for (int j = 0; j < len; j++) {
				int x = a[i + j], y = (ll)a[i + j + len] * _w[len + j] % mod;
				a[i + j] = (x + y) % mod, a[i + j + len] = (x - y + mod) % mod;
			}
}

inline vector operator * (const vector &f, const vector &g) {
	int lim = 1, k = 0, fs = f.size(), gs = g.size();
	while (lim <= (fs + gs - 1)) lim <<= 1, ++k;
	// for (auto i : f) print(i, ' '); puts("");
	// for (auto i : g) print(i, ' '); puts("");
	for (int i = 0; i < lim; i++) {
		_r[i] = (_r[i >> 1] >> 1) | ((i & 1) << (k - 1));
		_f[i] = i < fs ? f[i] : 0, _g[i] = i < gs ? g[i] : 0;
	} ntt(_f, lim), ntt(_g, lim);
	for (int i = 0; i < lim; i++) _f[i] = (ll)_f[i] * _g[i] % mod;
	std::reverse(_f + 1, _f + lim), ntt(_f, lim), lim = inv(lim); vector r(fs + gs - 1); 
	for (int i = 0; i < r.size(); i++) r[i] = (ll)_f[i] * lim % mod;
	return r;
}

vector solve(int l, int r) {
	if (l == r) { vector r(a[l] + 1); r[0] = 1, r[a[l]] = mod - 1; return r; }
	int mid = (l + r) >> 1; vector L = solve(l, mid), R = solve(mid + 1, r);
	return L * R;
}

void main() {
	for (int len = 1, wn; (len << 1) < N; len <<= 1) {
		_w[len] = 1, wn = fpow(3, (mod - 1) / (len << 1));
		for (int i = 1; i < len; i++) _w[i + len] = (ll)_w[i + len - 1] * wn % mod;
	}
	read(n);
	for (int i = 1; i <= n; i++) read(a[i]);
	vector vet = solve(2, n);
	// for (auto i : vet) print(i, ' '); puts("");
	for (int i = 0; i < vet.size(); i++) {
		ans = (ans + (ll)a[1] * inv(i + a[1]) % mod * vet[i]) % mod;
		// printf(">> %d %d\n", ans, (ll)i * vet[i] % mod);
	}
	print(ans, '\n');
 }

} signed main() { return ringo::main(), 0; }
