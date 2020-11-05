// =================================
//   author: memset0
//   date: 2019.08.03 09:53:57
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
template <class T> inline void print(T a, int l, int r, std::string s = "") {
	if (s != "") std::cout << s << ": ";
	for (int i = l; i <= r; i++) print(a[i], " \n"[i == r]);
}

const int N = 3e5 + 10, mod = 1e9 + 7;
std::map<int, int> map;
int n, cnt, ans, nod, max, lim;
int a[N], s[N], pri[N], vis[N], fac[N], ifac[N], f[N], g[N], c[N][20];

inline int get_prime(int x) {
	auto it = map.find(x);
	return it == map.end() ? map[x] = ++nod : it->second;
}

void init_fac(int n) {
	g[0] = fac[0] = ifac[0] = ifac[1] = 1;
	for (int i = 1; i <= n; i++) fac[i] = (ll)fac[i - 1] * i % mod;
	for (int i = 2; i <= n; i++) ifac[i] = (ll)(mod - mod / i) * ifac[mod % i] % mod;
	for (int i = 1; i <= n; i++) ifac[i] = (ll)ifac[i - 1] * ifac[i] % mod;
	for (int i = 1; i <= n - 1; i++) g[i] = (g[i - 1] + (ll)fac[n - 1] * ifac[i] % mod * ifac[n - i - 1]) % mod;
	for (int i = 1; i <= n; i++) f[i] = ((ll)g[n - 1] - g[n - i] - g[n - i - 1] + mod + mod) % mod;
	for (int i = 1; i <= n; i++) s[i] = (s[i - 1] + f[i]) % mod;
}

void main() {
	read(n), init_fac(n);
	for (int i = 1; i <= n; i++) read(a[i]), max = std::max(max, a[i]);
	lim = sqrt(max);
	for (int i = 2; i <= lim; i++) {
		if (!vis[i]) pri[++cnt] = i;
		for (int j = 1; j <= cnt && i * pri[j] <= lim; j++) {
			vis[i * pri[j]] = 1; if (i % pri[j] == 0) break;
		}
	}
	nod = cnt;
	std::cerr << "clock: " << clock() / double(CLOCKS_PER_SEC) << std::endl;
 	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= cnt; j++) if (a[i] % pri[j] == 0) {
			int tik = 0;
			while (a[i] % pri[j] == 0) ++tik, a[i] /= pri[j];
			++c[j][tik];
		}
		if (a[i] != 1) { ++c[get_prime(a[i])][1]; }
	}
	std::cerr << "clock: " << clock() / double(CLOCKS_PER_SEC) << std::endl;
	for (int i = 1; i <= nod; i++) {
		int p = n;
		for (int j = 1; j < 20; j++) p -= c[i][j];
		for (int j = 1; j < 20; j++) {
			ans = (ans + (ll)j * (s[p + c[i][j]] - s[p] + mod)) % mod;
			p += c[i][j];
		}
	}
	std::cerr << "clock: " << clock() / double(CLOCKS_PER_SEC) << std::endl;
	print(ans, '\n');
}

} signed main() {
#ifdef memset0
	freopen("1.in", "r", stdin);
#endif
	return ringo::main(), 0;
}