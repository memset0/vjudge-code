// =================================
//   author: memset0
//   date: 2019.01.14 10:09:31
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

const int N = 20, mod = 998244353;
int n, m, t, s, S, lim, f[N], k[N], b[N], a[1 << 18];
std::vector <int> G[N];

inline int sum(int a, int b) { return (a + b) % mod; }
inline int dec(int a, int b) { return (a - b + mod) % mod; }
int inv(int x) { return !x || x == 1 ? 1 : (ll)(mod - mod / x) * inv(mod % x) % mod; }

void dfs(int u, int father = 0) {
	for (auto v : G[u]) if (v != father) dfs(v, u);
	if ((1 << (u - 1)) & S) { k[u] = b[u] = 0; return; }
	int Sk = 0, Sb = 0, d = G[u].size();
	for (auto v : G[u]) if (v != father) (Sk += k[v]) %= mod, (Sb += b[v]) %= mod;
	k[u] = inv(dec(d, Sk)), b[u] = (ll)k[u] * sum(Sb, d) % mod;
}
void dfs2(int u, int father = 0) {
	f[u] = ((ll)k[u] * f[father] + b[u]) % mod;
	for (auto v : G[u]) if (v != father) dfs2(v, u);
}

int calc(int _S) {
	S = _S, dfs(s), dfs2(s);
	return f[s];
}

void fwt(int *a) {
	for (int len = 1; len < lim; len <<= 1)
		for (int i = 0; i < lim; i += (len << 1))
			for (int j = 0; j < len; j++) 
				(a[i + j + len] += a[i + j]) %= mod;
}

void main() {
	read(n), read(m), read(s), lim = 1 << n;
	for (int i = 1, u, v; i < n; i++) read(u), read(v), G[u].push_back(v), G[v].push_back(u);
	for (S = 1; S < lim; S++) a[S] = (ll)calc(S) * (__builtin_popcount(S) & 1 ? 1 : mod - 1) % mod;
	fwt(a);
	for (int i = 1; i <= m; i++) {
		int S = 0; read(t);
		for (int i = 1, x; i <= t; i++) read(x), S |= 1 << (x - 1);
		print(a[S], '\n');
	}
}

} signed main() { return ringo::main(), 0; }