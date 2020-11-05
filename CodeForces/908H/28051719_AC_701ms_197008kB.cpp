// =================================
//   author: memset0
//   date: 2019.05.08 13:55:10
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

const int N = 50, M = 1 << 23;
char c[N][N];
bool tag[N][N];
int n, m, cnt, ans, sum;
int id[N], fa[N], mrk[N];
unsigned ll f[M], g[M], s[M];

inline int find(int x) {
	if (fa[x] == x) return x;
	return fa[x] = find(fa[x]);
}

inline void fwt(unsigned ll *a, int lim) {
	for (int len = 1; len < lim; len <<= 1)
		for (int i = 0; i < lim; i += (len << 1))
			for (int j = 0; j < len; j++) {
				a[i + j + len] = a[i + j] + a[i + j + len];
			}
}

void main() {
	read(n);
	for (int i = 1; i <= n; i++)
		scanf("%s", c[i] + 1);
	for (int i = 1; i <= n; i++) fa[i] = i;
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= n; j++)
			if (c[i][j] == 'A') {
				fa[find(i)] = find(j);
			}
	for (int i = 1; i <= n; i++)
		if (find(i) == i) {
			std::vector<int> s;
			for (int j = 1; j <= n; j++)
				if (find(j) == i)
					s.push_back(j);
			++cnt;
			if (s.size() > 1) {
				++m, sum += s.size();
				for (auto x : s) id[x] = m;
			}
		}
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= n; j++)
			if (c[i][j] == 'X') {
				int f_i = find(i), f_j = find(j);
				if (f_i == f_j) {
					puts("-1"); return;
				} else {
					tag[id[f_i]][id[f_j]] = 1;
				}
			}
	for (int i = 1; i <= m; i++) {
		for (int j = 1; j <= m; j++)
			if (tag[i][j])
				mrk[i] |= 1 << (j - 1);
	}
	for (int x = 0; x < (1 << m); x++) {
		f[x] = 1;
		for (int i = 1; i <= m; i++)
			if (((x >> (i - 1)) & 1) && (x & mrk[i])) {
				f[x] = 0;
				break;
			}
	}
	// print(mrk, 1, m, "mrk");
	// print(f, 0, (1 << m) - 1, "F");
	if (f[(1 << m) - 1]) ans = 0;
	else {
		fwt(f, 1 << m);
		for (int x = 0, y = (1 << m) - 1; x < (1 << m); x++)
			g[x] = __builtin_popcount(x ^ y) & 1 ? -1 : 1;
		// print(f, 0, (1 << m) - 1, "F");
		// print(g, 0, (1 << m) - 1, "G");
		for (int x = 0; x < (1 << m); x++) s[x] = f[x];
		for (ans = 1; ; ans++) {
			for (int x = 0; x < (1 << m); x++) s[x] = s[x] * f[x];
			unsigned ll sum = 0;
			for (int x = 0; x < (1 << m); x++) sum += s[x] * g[x];
			// print(s, 0, (1 << m) - 1, "S");
			// printf(">> %d => %d\n", ans, sum);
			if (sum) break;
		}
		// printf(">> ans = %d\n", ans);
	}
	// printf("sum = %d cnt = %d m = %d ans = %d\n", sum, cnt, m, ans);
	print(sum + ans + (m ? cnt - m : cnt - m - 1), '\n');
}

} signed main() {
#ifdef MEMSET0_LOCAL_ENVIRONMENT
	freopen("1.in", "r", stdin);
#endif
	return ringo::main(), 0;
}