// luogu-judger-enable-o2
// =================================
//   author: memset0
//   date: 2019.02.10 10:09:33
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

const int N = 60, mod = 1e9 + 7;
int T, n, m, l, ans, a[N], y[N], sum[N], prev[N], next[N], ifac[N];
std::set <int> set;

inline int fpow(int a, int b) {
	int s = 1;
	for (; b; b >>= 1, a = (ll)a * a % mod)
		if (b & 1) s = (ll)s * a % mod;
	return s;
}

int debug(int k) {
	int ans = 0;
	for (int i = 1; i <= k; i++)
		ans = (ans + fpow(i, m + 1)) % mod;
	return ans;
}

inline int calc(int k) {
	prev[0] = k, next[l] = k - l; int ans = 0;
	for (int i = 1; i <= l; i++) prev[i] = (ll)prev[i - 1] * (k - i) % mod;
	for (int i = l - 1; i >= 0; i--) next[i] = (ll)next[i + 1] * (k - i) % mod;
	for (int i = 0; i <= l; i++) ans = (ans + (ll)y[i] * (i ? prev[i - 1] : 1) % mod
		* (i != l ? next[i + 1] : 1) % mod * ifac[i] % mod * ifac[l - i] % mod * ((l - i) & 1 ? -1 : 1)) % mod;
	// for (int i = 0; i <= l; i++) printf("%d %d %d %d %d %d\n", y[i], (i ? prev[i - 1] : 1), (i != l ? next[i + 1] : 1), ifac[i], ifac[l - i], ((l - i) & 1 ? -1 : 1));
	// printf(">>> %d : %d %d\n", k, (ans + mod) % mod, (debug(k) + mod) % mod);
	return ans;
}

void main() {
	ifac[0] = ifac[1] = 1;
	for (int i = 2; i < N; i++) ifac[i] = (ll)(mod - mod / i) * ifac[mod % i] % mod;
	for (int i = 2; i < N; i++) ifac[i] = (ll)ifac[i - 1] * ifac[i] % mod;
	for (read(T); T--; ) {
		read(n), read(m), l = m + 2, set.clear();
		for (int x; m--; ) read(x), set.insert(x);
		for (int i = n; i >= 1; i--) if (set.count(i)) set.erase(i); else break;
		m = 0; for (auto i : set) a[++m] = i;
		// for (int i = 1; i <= m; i++) print(a[i], " \n"[i == m]);
		sum[m + 1] = ans = 0;
		for (int i = 1; i <= l; i++) y[i] = (y[i - 1] + fpow(i, m + 1)) % mod;
		for (int i = 0; i <= m; i++) {
			ans = (ans + calc(n - a[i])) % mod;
			for (int j = i + 1; j <= m; j++) ans = (ans - fpow(a[j] - a[i], m + 1)) % mod;
		} print((ans + mod) % mod, '\n');
	}
}

} signed main() { return ringo::main(), 0; }