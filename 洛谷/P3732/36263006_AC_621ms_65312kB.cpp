// luogu-judger-enable-o2
// =================================
//   author: memset0
//   date: 2019.03.13 19:01:09
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

const int N = 1e5 + 10, L = 60, M = N * (L + 1);
int n, m, rt, lim, rit, cnt;
int a[N], b[N], ans[N], out[N], dp[M], ch[M][2];
std::vector <std::pair <int, int> > Q[N];
char s[N];

void insert(int &u, int dep) {
	if (dep > lim) return;
	if (!u) u = ++cnt;
	// printf(">> insert %d %d => %d\n", u, dep, dp[u]);
	if (~dp[u]) ans[dep] = std::max(ans[dep], dp[u]);
	dp[u] = rit;
	insert(ch[u][b[dep + 1]], dep + 1);
}

void main() {
	memset(ans, -1, sizeof(ans)), memset(dp, -1, sizeof(dp));
	read(n), read(m), scanf("%s", s + 1);
	for (int i = 1; i <= n; i++) a[i] = s[i] - '0';
	for (int i = 1, l, r; i <= m; i++) read(l), read(r), Q[r].push_back(std::make_pair(l, i));
	for (int i = 1; i <= n; i++) {
		lim = std::min(n - i + 1, L), rit = i;
		for (int j = 1; j <= lim; j++) b[j] = a[i + j - 1];
		insert(rt, 0);
		// for (int i = 1; i <= L; i++) print(ans[i] > n ? -1 : ans[i], " \n"[i == L]);
		for (auto it : Q[i]) {
			for (int i = 1; i <= L; i++) if (~ans[i]) out[it.second] += std::max(0, ans[i] - it.first + 1);
		}
	}
	for (int i = 1; i <= m; i++) print(out[i], '\n');
}

} signed main() { return ringo::main(), 0; }