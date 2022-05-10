// luogu-judger-enable-o2
// =================================
//   author: memset0
//   date: 2019.01.11 18:20:48
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

const size_t N = 1010;
int n, m, q, t, limit[N];
bool vis[N];
std::bitset <N> ans, bit[N][N];
std::vector <int> now[2], G[N];

void main() {
	read(n), read(m), read(q);
	for (int i = 1, u, v; i <= m; i++) {
		read(u), read(v);
		G[u].push_back(v);
		G[v].push_back(u);
	}
	for (int s = 1; s <= n; ++s) {
		memset(vis, 0, sizeof(vis));
		now[0].clear(), now[1].clear();
		bit[s][0].set(s), now[1].push_back(s), vis[s] = 1;
		for (int i = 1; now[i & 1].size(); ++i) {
			// printf("%d => %d\n", s, i);
			bit[s][i] = bit[s][i - 1];
			for (auto u : now[i & 1])
				for (auto v : G[u])
					if (!vis[v]) {
						vis[v] = 1, bit[s][i].set(v);
						now[i & 1 ^ 1].push_back(v);
					}
			now[i & 1].clear(), limit[s] = i;
		}
	}
	for (int i = 1, x, y; i <= q; i++) {
		ans.reset();
		for (read(t); t--; ) {
			read(x), read(y);
			ans |= bit[x][std::min(y, limit[x])];
		}
		print(ans.count(), '\n');
	}
}

} signed main() { return ringo::main(), 0; }