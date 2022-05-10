// luogu-judger-enable-o2
// =================================
//   author: memset0
//   date: 2019.08.06 11:19:18
//   website: https://memset0.cn/
// =================================
#include <bits/stdc++.h>
#define ll long long
#define rep(i, l, r) for (int i = (l), i##ed = (r); i <= i##ed; ++i)
#define for_each(i, a) for (size_t i = 0, i##ed = a.size(); i < i##ed; ++i)
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
template <class T> inline void print(T a, int l, int r) { for (int i = l; i <= r; i++) print(a[i], " \n"[i == r]); }

const int N = 5e6 + 10, mod = 998244353;
int f[N], g[N], fac[N], ifac[N];

int finv(int x) { return x < 2 ? 1 : (ll)(mod - mod / x) * finv(mod % x) % mod; }
int binom(int n, int m) { return n < m ? 0 : (ll)fac[n] * ifac[m] % mod * ifac[n - m] % mod; }
int fpow(int a, int b) { int s = 1; for (; b; b >>= 1, a = (ll)a * a % mod) if (b & 1) s = (ll)s * a % mod; return s; }

void solve(int n, int m, int l, int k) {
	// printf("solve %d %d %d %d\n", n, m, l, k);
	int lim = std::min(n, std::min(m, l));
	for (int i = 1; i <= lim; i++) {
		f[i] = (ll)f[i - 1] * (((ll)n * m % mod * l - (ll)(n - i) * (m - i) % mod * (l - i)) % mod + mod) % mod;
		g[i] = (ll)g[i - 1] * f[i] % mod;
	}
	// print(f, 1, lim);
	int s_inv = finv(g[lim]);
	for (int i = lim; i >= 1; i--) {
		g[i] = (ll)s_inv * g[i - 1] % mod;
		s_inv = (ll)s_inv * f[i] % mod;
	}
	// print(g, 1, lim);
	for (int i = 1; i <= lim; i++) {
		f[i] = (ll)g[i] * binom(n, i) % mod * binom(m, i) % mod * binom(l, i) % mod * fac[i] % mod * fac[i] % mod * fac[i] % mod;
	}
	// print(f, 1, lim);
	int ans = 0;
	for (int i = k; i <= lim; i++) {
		ans = (ans + (ll)f[i] * ((i - k) & 1 ? mod - 1 : 1) % mod * binom(i, k)) % mod;
	}
	print(ans, '\n');
}

void main() {
	f[0] = g[0] = 1;
	int T, max = 0; read(T);
	std::vector<std::tuple<int, int, int, int>> q;
	for (int i = 1, x, y, z, k; i <= T; i++) {
		read(x), read(y), read(z), read(k);
		q.push_back(std::make_tuple(x, y, z, k));
		max = std::max(max, std::max(std::max(x, y), std::max(z, k)));
	}
	fac[0] = ifac[0] = ifac[1] = 1;
	for (int i = 1; i <= max; i++) fac[i] = (ll)fac[i - 1] * i % mod;
	for (int i = 2; i <= max; i++) ifac[i] = (ll)(mod - mod / i) * ifac[mod % i] % mod;
	for (int i = 2; i <= max; i++) ifac[i] = (ll)ifac[i - 1] * ifac[i] % mod;
	for (auto it : q) solve(std::get<0>(it), std::get<1>(it), std::get<2>(it), std::get<3>(it));
}

} signed main() {
#ifdef memset0
	freopen("1.in", "r", stdin);
	// freopen("1.out", "w", stdout);
#endif
	ringo::main();
	std::cerr << "clock: " << clock() / double(CLOCKS_PER_SEC) << std::endl;
}