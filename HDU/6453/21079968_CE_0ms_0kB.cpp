// =================================
//   author: memset0
//   date: 2019.08.05 13:28:53
//   website: https://memset0.cn/
// =================================
#include <bits/stdc++.h>
#define ll long long
#define rep(i, l, r) for (int i = (l), i##ed = (r); i <= i##ed; ++i)
#define for_each(i, a) for (size_t i = 0, i##ed = a.size(); i < i##ed; ++i)
namespace ringo {

template <class T> inline void read(T &x) {
	x = 0; char c = getchar(); bool f = 0;
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

const int N = 1e4 + 10, M = 3e4 + 10, W = 1210, mod = 1e9 + 7;
int n, m, w, l, r;
std::vector<int> G[N];
int a[N], q[N], ind[N], f[3][W], mat[W][W], sum[N][W], dis[N][W];

inline void sub(int &a, int b) { a -= b; if (a < 0) a += mod; }
inline void add(int &a, int b) { a += b; if (a >= mod) a -= mod; }

inline int get_inv(int x) {
	if (x < 2) return 1;
	return (ll)(mod - mod / x) * get_inv(mod % x) % mod;
}

void gauss(int a[W][W], int ans[W], int n) {
	for (int i = 1, j, d; i <= n; i++) {
		for (j = i; j <= n; j++) if (a[i] != a[j]) break;
		if (j > n) { puts("Error!"); exit(0); } else if (i != j) std::swap(a[i], a[j]);
		d = get_inv(a[i][i]);
		for (int j = i; j <= n + 1; j++) a[i][j] = (ll)a[i][j] * d % mod;
		for (int j = i + 1; j <= n; j++) {
			d = a[j][i];
			for (int k = i; k <= n + 1; k++) sub(a[j][k], (ll)d * a[i][k] % mod);
		}
	}
	for (int i = n; i >= 1; i--) {
		ans[i] = f[i][n + 1];
		for (int j = 1; j < i; j++) sub(a[j][n + 1], (ll)a[j][i] * ans[i] % mod);
	}
}

void main() {
	read(n), read(m), read(w);
	for (int i = 1; i <= n; i++) read(a[i]);
	for (int i = 1, u, v; i <= m; i++) {
		read(v), read(u);
		G[u].push_back(v), ind[v]++;
	}
	for (int i = 1; i <= n; i++) if (!ind[i]) q[r++] = i;
	while (l < r) {
		int u = q[l++];
		dis[u][a[u]] = 1;
		for (auto v : G[u]) {
			for (int i = 0; i <= w; i++) add(dis[u][i], dis[v][i]);
			if (!--ind[v]) q[r++] = v;
		}
	}
	for (int i = 0; i <= n; i++)
		for (int j = 1; j <= w * 3 + 1; j++)
			for (int k = 1, s = j; k <= 3 * w + 1; k++, s = (ll)s * j % mod) {
				sum[i][j] = (sum[i][j] + (ll)dis[i][k] * s) % mod;
			}
	for (int lim, flag = 1; flag <= 3; flag++) {
		lim = flag * w + 1;
		for (int i = 1; i <= lim; i++)
			for (int j = 1, s = 1; j <= lim; j++, s = (ll)s * i % mod) {
				mat[i][j] = s;
			}
		for (int i = 1; i <= lim; i++) {
			if (flag == 1) for (int j = 1; j <= n; j++) add(mat[i][lim + 1], sum[j][i]);
			if (flag == 2) for (int j = 1; j <= n; j++) mat[i][lim + 1] = (mat[i][lim + 1] + (ll)sum[j][i] * sum[j][i]) % mod;
			if (flag == 3) for (int j = 1; j <= n; j++) mat[i][lim + 1] = (mat[i][lim + 1] + (ll)sum[j][i] * sum[j][i] * sum[j][i]) % mod;
		}
		gauss(mat, f[flag - 1], lim);
		for (int i = 1; i <= lim; i++) f[flag - 1][i - 1] = f[flag - 1][i];
	}
	int lim = 3 * w;
	for (int i = 0; i <= lim; i++) {
		if (i * 2 <= lim) sub(f[1][i * 2], f[0][i]);
		if (i * 3 <= lim) sub(f[1][i * 3], f[0][i]);
	}
	for (int i = 0; i <= lim; i++) 
}

void clear() {
	for (int i = 1; i <= n; i++) G[i].clear();
}

} signed main() {
#ifdef memset0
	freopen("1.in", "r", stdin);
	// freopen("1.out", "w", stdout);
#endif
	int T; ringo::read(T);
	while (T--) ringo::main(), ringo::clear();
}