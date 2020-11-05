// =================================
//   author: memset0
//   date: 2019.01.19 08:17:07
//   website: https://memset0.cn/
// =================================
#include <bits/stdc++.h>
#define ll unsigned long long
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

const int N = 1e6 + 10;
ll n, k = 3, sqr, a[N], g[N];
int T, cnt, sqn, pri, prime[N];

inline int id(ll x) { return x <= sqn ? x : cnt - n / x + 1; }

ll calcS(ll a, int b) {
	if (a <= 1 || a < prime[b]) return 0;
	ll ans = g[id(a)] - (b - 1) * (k + 1);
	for (int i = b; i <= pri && (ll)prime[i] * prime[i] <= a; i++) {
		int p = prime[i]; ll x = p, f = k + 1, nxt;
		for (int j = 1; x * p <= a; j++, x *= p, f = nxt) {
			nxt = (j + 1) * k + 1;
			ans += f * calcS(a / x, i + 1) + nxt;
		}
	} return ans;
}

void solve(ll n) {
	sqn = sqrt(n);
	for (ll i = 1; i <= n; i = a[cnt] + 1) a[++cnt] = n / (n / i);
	for (int i = 1; i <= cnt; i++) g[i] = a[i] - 1;
	for (int i = 2; i <= sqn; i++) if (g[i] != g[i - 1]) {
		prime[++pri] = i, sqr = (ll)i * i;
		for (int j = cnt; a[j] >= sqr; j--) g[j] -= g[id(a[j] / i)] - (pri - 1);
	}
	for (int i = 1; i <= cnt; i++) g[i] *= k + 1;
	print(calcS(n, 1) + 1, '\n');
}

void main() {
	for (read(T); T--; ) {
		pri = cnt = 0;
		read(n), solve(n);
	}
}

} signed main() { return ringo::main(), 0; }