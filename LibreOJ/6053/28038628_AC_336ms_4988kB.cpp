// =================================
//   author: memset0
//   date: 2019.01.18 20:25:34
//   website: https://memset0.cn/
// =================================
#include <bits/stdc++.h>
#define int long long
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

const int N = 2e5 + 10, mod = 1e9 + 7;
ll n, sqr, sqn, a[N];
int pri, cnt, prime[N], h[N], g[N], sum[N];

inline int id(ll x) { return x <= sqn ? x : cnt - n / x + 1; }

int solve(ll a, int b) {
	if (a <= 1 || a < prime[b]) return 0;
	int ans = (g[id(a)] - sum[b - 1] + mod) % mod;
	for (int i = b; i <= pri && (ll)prime[i] * prime[i] <= a; i++) {
		ll x = prime[i];
		for (int j = 1; x * prime[i] <= a; j++, x *= prime[i])
			ans = (ans + (ll)(prime[i] ^ j) * solve(a / x, i + 1) + (prime[i] ^ (j + 1))) % mod;
	} return ans;
}

void main() {
	read(n), sqn = sqrt(n);
	for (ll i = 1; i <= n; i = a[cnt] + 1) a[++cnt] = n / (n / i);
	for (int i = 1; i <= cnt; i++) {
		ll tA = (a[i] & 1 ? a[i] : a[i] >> 1) % mod;
		ll tB = (a[i] & 1 ? (a[i] + 1) >> 1 : a[i] + 1) % mod;
		g[i] = (tA * tB + mod - 1) % mod;
		h[i] = (a[i] - 1 + mod) % mod;
	}
	for (int i = 2; i <= sqn; i++) if (h[i] != h[i - 1]) {
		prime[++pri] = i, sum[pri] = (sum[pri - 1] + i) % mod, sqr = (ll)i * i;
		for (int j = cnt; a[j] >= sqr; j--) {
			g[j] = (g[j] - (ll)i * (g[id(a[j] / i)] - sum[pri - 1]) % mod + mod) % mod;
			h[j] = (h[j] - h[id(a[j] / i)] + pri - 1 + mod) % mod;
		}
	}
	for (int i = 2; i <= cnt; i++) g[i] = (mod + g[i] - h[i] + 2) % mod;
	for (int i = 1; i <= pri; i++) sum[i] = (sum[i] + 2 - i + mod) % mod;
	print(solve(n, 1) + 1, '\n');
}

} signed main() { return ringo::main(), 0; }
