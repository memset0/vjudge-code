// luogu-judger-enable-o2

// =================================
//   author: memset0
//   date: 2019.05.07 09:11:45
//   website: https://memset0.cn/
// =================================
#include <bits/stdc++.h>
#define ll long long
#define debug(...) ((void)0)
#ifndef debug
#define debug(...) fprintf(stderr,__VA_ARGS__)
#endif
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
template <class T> inline void print(T a, int l, int r, std::string s = "") {
	if (s != "") std::cout << s << ": ";
	for (int i = l; i <= r; i++) print(a[i], " \n"[i == r]);
}

const int N = 5e3 + 10, M = 3e2 + 10;
int n, m;

struct treeClass {
	int n;
	std::vector<int> G[N];
	void init() {
		read(n);
		for (int u, v, i = 1; i < n; i++) {
			read(u), read(v);
			G[u].push_back(v);
			G[v].push_back(u);
		}
	}
	void merge(int u, int v) {
		for (int i = 1; i <= siz[u]; i++)
			for (int j = 1; j <= siz[v]; j++) {
				int all = sub(dp[v][j][0], sub(dp[v][j][1], dp[v][j][2]));
				tmp[i + j][0] = sub(tmp[i + j][0], mul(dp[u][i][0], all));
				tmp[i + j][1] = sub(tmp[i + j][1], mul(dp[u][i][1], all));
				tmp[i + j][2] = sub(tmp[i + j][2], mul(dp[u][i][2], all));
				tmp[i + j - 1][1] = sub(tmp[i + j - 1][1], mul(dp[u][i][0], ))
			}
		for (int i = 0; i <= siz[u] + siz[v]; i++) {
			dp[u][i][0] = tmp[i][0];
			dp[u][i][1] = tmp[i][1];
			dp[u][i][2] = tmp[i][2];
		}
	}
	void dfs(int u, int fa = 0) {
		siz[u] = dp[u][1] = 1;
		for (auto v : G[u]) if (v != fa) {
			dfs(v, u);
			merge(u, v);
			siz[u] += siz[v];
		}
	}
	void solve() {
		dfs(1);
		for (int i = 1; i <= n; i++) {
			f[i] = sub(dp[1][i][0], sub(dp[1][i][1], dp[1][i][2]));
		}
	}
} tree[M];

void main() {
	read(t);
	for (int i = 1; i <= n; i++) tree[i].init();

}

} signed main() {
#ifdef MEMSET0_LOCAL_ENVIRONMENT
	freopen("1.in", "r", stdin);
#endif
	return ringo::main(), 0;
}