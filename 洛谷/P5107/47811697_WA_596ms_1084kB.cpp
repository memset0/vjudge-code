// luogu-judger-enable-o2
// =================================
//   author: memset0
//   date: 2018.12.16 16:36:37
//   website: https://memset0.cn/
// =================================
#include <bits/stdc++.h>
#define int long long
namespace ringo {
typedef long long ll;

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

const int N = 50, M = 2510, Q = 1010, T = 5e5 + 10,  p = 998244353;
int n, m, u, v, q, limit;
int a[N], b[N], siz[N], qry[Q], ans[T];
int tot = 2, hed[N], to[M], nxt[M];

int inv(int x) {
	if (!x || x == 1) return 1;
	return (ll)(p - p / x) * inv(p % x) % p;
}

void solve(int tim) {
	for (int i = 1; i <= n; i++) {
		b[i] = a[i];
		a[i] = (ll)b[i] * siz[i] % p;
	}
	for (int u = 1; u <= n; u++)
		for (int i = hed[u], v = to[i]; i; i = nxt[i], v = to[i]) {
			a[v] = (a[v] + (ll)siz[u] * b[u]) % p;
	}
	for (int i = 1; i <= n; i++)
		ans[tim] ^= a[i];
	ans[tim] %= p;
}

void main() {
	read(n), read(m), read(q);
	for (int i = 1; i <= n; i++) read(a[i]), siz[i] = 1;
	for (int i = 1; i <= m; i++) {
		read(u), read(v), ++siz[u];
		nxt[tot] = hed[u], to[tot] = v, hed[u] = tot++;
	}
	for (int i = 1; i <= n; i++) siz[i] = inv(siz[i]);
	for (int i = 1; i <= q; i++) read(qry[i]), maxd(limit, qry[i]);
	for (int i = 1; i <= limit; i++) solve(i);
	for (int i = 1; i <= q; i++) print(ans[qry[i]], '\n');
}

} signed main() { return ringo::main(), 0; }