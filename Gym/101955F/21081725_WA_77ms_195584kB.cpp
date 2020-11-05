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

const int N = 1e4 + 10, W = 1210, mod = 1e9 + 7;
std::vector<int> G[N];
int n, m, w, l, r, lim;
int a[N], q[N], ind[N], ans[W], sum1[N][W], sum2[N][W], sum3[N][W], mat[W][W], dis[N][W];

inline void sub(int &a, int b) { a -= b; if (a < 0) a += mod; }
inline void add(int &a, int b) { a += b; if (a >= mod) a -= mod; }

inline int get_inv(int x) {
	if (x < 2) return 1;
	return (ll)(mod - mod / x) * get_inv(mod % x) % mod;
}

inline int fpow(int a, int b) {
	int s = 1;
	for (; b; b >>= 1, a = (ll)a * a % mod)
		if (b & 1) s = (ll)s * a % mod;
	return s;
}

void gauss(int a[W][W], int ans[W], int n) {
	for (int i = 1, j, d; i <= n; i++) {
		for (j = i; j <= n; j++) if (a[j]) break;
		if (j > n) { puts("Error!"); exit(0); } else if (i != j) std::swap(a[i], a[j]);
		d = get_inv(a[i][i]);
		for (int j = i; j <= n + 1; j++) a[i][j] = (ll)a[i][j] * d % mod;
		for (int j = i + 1; j <= n; j++) {
			d = a[j][i];
			for (int k = i; k <= n + 1; k++) sub(a[j][k], (ll)d * a[i][k] % mod);
		}
	}
	for (int i = n; i >= 1; i--) {
		ans[i] = a[i][n + 1];
		for (int j = 1; j < i; j++) sub(a[j][n + 1], (ll)a[j][i] * ans[i] % mod);
	}
}

void main(int CASE) {
	read(n), read(m), read(w);
	for (int i = 1; i <= n; i++) read(a[i]);
	for (int i = 1, u, v; i <= m; i++) {
		read(v), read(u);
		G[u].push_back(v), ind[v]++;
	}
	for (int i = 1; i <= n; i++) if (!ind[i]) q[r++] = i;
	lim = 3 * w + 1;
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= lim; j++) {
			sum1[i][j] = fpow(j, a[i]);
			if (a[i] * 2 < lim) sum2[i][j] = fpow(j, a[i] * 2);
			if (a[i] * 3 < lim) sum3[i][j] = fpow(j, a[i] * 3);
		}
	while (l < r) {
		int u = q[l++];
		for (auto v : G[u]) {
			for (int i = 1; i <= lim; i++) {
				add(sum1[v][i], sum1[u][i]);
				add(sum2[v][i], sum2[u][i]);
				add(sum3[v][i], sum3[u][i]);
			}
			if (!--ind[v]) q[r++] = v;
		}
	}
	for (int u = 1; u <= n; u++) {
		for (int i = 1, move; i <= lim; i++) {
			int s1 = sum1[u][i], s2 = sum2[u][i], s3 = sum3[u][i];
			move = ((ll)s1 * s1 * s1 - 3 * s1 * s2 + 2 * s3) % mod;
			// printf("%d > %d : %d\n", u, i, move < 0 ? move + mod : move);
			add(mat[i][lim + 1], move < 0 ? move + mod : move);
		}
	}
	for (int i = 1; i <= lim; i++)
		for (int j = 1, s = 1; j <= lim; j++, s = (ll)s * i % mod) {
			mat[i][j] = s;
		}
	// for (int i = 1; i <= n; i++) print(dis[i], 1, lim); puts("");
	// for (int i = 1; i <= lim; i++) print(mat[i], 1, lim + 1); puts("");
	// for (int i = 1; i <= lim; i++) print(mat[i][lim + 1], " \n"[i == lim]);
	gauss(mat, ans, lim);
	printf("Case #%d: ", CASE);
	for (int i = 2; i <= lim; i++) print((ll)ans[i] * get_inv(6) % mod, " \n"[i == lim]);
}

void clear() {
	for (int i = 1; i <= n; i++) G[i].clear();
	memset(mat, 0, sizeof(mat));
	memset(dis, 0, sizeof(dis));
	memset(sum1, 0, sizeof(sum1));
	memset(sum2, 0, sizeof(sum2));
	memset(sum3, 0, sizeof(sum3));
}

} signed main() {
#ifdef memset0
	freopen("1.in", "r", stdin);
	// freopen("1.out", "w", stdout);
#endif
	int T; ringo::read(T);
	for (int i = 1; i <= T; i++) ringo::main(i), ringo::clear();
}