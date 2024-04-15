// =================================
//   author: memset0
//   date: 2019.01.05 22:58:19
//   website: https://memset0.cn/
// =================================
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/hash_policy.hpp>
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

const int N = 5e3 + 10, M = 2e2 + 10;

int n, m, q, u, v, d, ans;
int fa[N][M], siz[N][M];
std::vector <int> son[N][M];

unsigned long long fac[M];
__gnu_pbds::cc_hash_table <unsigned long long, int> map;
// std::map <unsigned long long, int> map;

struct hash_struct {
	unsigned long long x;
	inline void init(unsigned long long v) {
		for (int i = m; i >= 1; i--)
			x = x * 13131 + v;
		map[x] = 1;
	}
	inline void modify(unsigned long long u, unsigned long long v, int d) {
		ans -= map[x] * 2 - 1, map[x] -= 1;
		x = x - u * fac[d] + v * fac[d];
		map[x] += 1, ans += map[x] * 2 - 1;
	}
} hsh[N];

void main() {
	read(m), read(n), read(q);
	fac[1] = 1;
	for (int i = 2; i <= m; i++) fac[i] = fac[i - 1] * 13131;
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
			fa[i][j] = i, siz[i][j] = 1;
			son[i][j].push_back(i);
		}
		hsh[i].init(i);
	}
	ans = n;
	for (int i = 1; i <= q; i++) {
		read(u), read(v), read(d);
		u = fa[u][d], v = fa[v][d];
		if (u != v) {
			if (siz[u][d] > siz[v][d]) std::swap(u, v);
			siz[v][d] += siz[u][d];
			for (std::vector <int> ::iterator it = son[u][d].begin(); it != son[u][d].end(); it++) {
				int i = *it;
				hsh[i].modify(fa[i][d], v, d);
				fa[i][d] = v;
				son[v][d].push_back(i);
			}
			son[u][d].clear();
		}
		print(ans, '\n');
	}
}

} signed main() { return ringo::main(), 0; }