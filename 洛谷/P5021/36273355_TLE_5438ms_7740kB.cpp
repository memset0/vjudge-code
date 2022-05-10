#include <bits/stdc++.h>
#define il inline
#define rg register
#define ll long long
#define getc getchar
#define putc putchar
#define rep(i,l,r) for (register int i = l; i <= r; ++i)
namespace ringo {

template < class T >
il void read(T &x) {
	x = 0; rg char c = getc(); rg bool f = 0;
	while (!isdigit(c)) f ^= c == '-', c = getc();
	while (isdigit(c)) x = x * 10 + c - '0', c = getc();
	if (f) x = -x;
}

template < class T >
il void print(T x) {
	if (x < 0) putc('-'), x = -x;
	if (x > 9) print(x / 10);
	putc(x % 10 + '0');
}

const int maxn = 50010, inf = 500000000;
int n, m, u, v, w, l, r, mid, ans, limit;
bool flag1, flag2, find_ans;
int deg[maxn];
int fa[maxn], fae[maxn], fav[maxn], dep[maxn], f[maxn][20];
bool tag[maxn];
int tot = 2, hed[maxn], to[maxn << 1], nxt[maxn << 1], val[maxn << 1];

// solve1 for (m == 1)
int mx1[maxn], mx2[maxn];
void solve0_dfs(int u) {
	for (int i = hed[u], v = to[i]; i; i = nxt[i], v = to[i])
		if (v != fa[u]) {
			solve0_dfs(v);
			if (mx1[v] + val[i] > mx1[u]) {
				mx2[u] = mx1[u];
				mx1[u] = mx1[v] + val[i];
			} else if (mx1[v] + val[i] > mx2[u]) {
				mx2[u] = mx1[v] + val[i];
			}
		}
	ans = std::max(ans, mx1[u] + mx2[u]);
}
void solve0() {
//	printf("solve0\n");
	solve0_dfs(1);
//	for (int i = 1; i <= n; i++)
//		printf("(%d %d) ", mx1[i], mx2[i] < 0 ? -1 : mx2[i]);
//	puts("");
	print(ans), putc('\n');
}
// end solve0

// solve1 a[i] == 1
int arr[maxn << 1];
bool solve1_check(int x, int cnt) {
	std::sort(arr + 1, arr + cnt + 1);
	int l = 1, r = cnt, now = 0;
	while (l < r) {
		while (l < r && arr[l] + arr[r] < x)
			l++;
		if (l < r && arr[l] + arr[r] >= x) {
			++now;
			if (now >= m)
				return true;
			++l, --r;
		}
	}
	return false;
}
void solve1() {
//	printf("solve1\n");
	int cnt = 0;
	for (int i = hed[1]; i; i = nxt[i])
		arr[++cnt] = val[i];
	for (int i = 1; i <= n; i++)
		arr[++cnt] = 0;
	l = 0, r = inf;
	while (l <= r) {
		mid = (l + r) >> 1;
		if (solve1_check(mid, cnt)) {
			l = mid + 1;
			ans = mid;
		} else {
			r = mid - 1;
		}
	}
	print(ans), putc('\n');
}
// end solve1

// solve2 b[i] == a[i] + 1
bool solve2_check(int x) {
	int cnt = 0, sum = 0;
	for (int i = 1; i < n; i++) {
		sum += arr[i];
		if (sum >= x) {
			sum = 0;
			++cnt;
			if (cnt >= m)
				return true;
		}
	} 
	return false;
}
void solve2() {
//	printf("solve2\n");
	for (int u = 1; u < n; u++) {
		for (int i = hed[u], v = to[i]; i; i = nxt[i], v = to[i])
			if (v == u + 1)
				arr[u] = val[i];
	}
	l = 0, r = inf;
	while (l <= r) {
		mid = (l + r) >> 1;
		if (solve2_check(mid)) {
			l = mid + 1;
			ans = mid;
		} else {
			r = mid - 1;
		}
	}
	print(ans), putc('\n');
}
// end solve2

// solve3
int dp[maxn], lst[maxn], son[maxn][2], cnt[maxn], sval[maxn][2];
void solve3_pre(int u) {
	for (int i = hed[u], v = to[i]; i; i = nxt[i], v = to[i])
		if (v != fa[u]) {
			fa[v] = u;
			son[u][cnt[u]] = v;
			sval[u][cnt[u]] = val[i];
			++cnt[u];
			solve3_pre(v);
		}
}
void solve3_dfs(int u) {
	if (cnt[u] == 0) {
		dp[u] = 0;
		lst[u] = 0;
	} else if (cnt[u] == 1) {
		solve3_dfs(son[u][0]);
		int v1 = lst[son[u][0]] + sval[u][0];
		dp[u] = dp[son[u][0]] + (v1 >= limit ? 1 : 0);
		lst[u] = (v1 >= limit ? 0 : v1);
	} else if (cnt[u] == 2) {
		solve3_dfs(son[u][0]);
		solve3_dfs(son[u][1]);
		int v1 = lst[son[u][0]] + sval[u][0];
		int v2 = lst[son[u][1]] + sval[u][1];
		dp[u] = dp[son[u][0]] + dp[son[u][1]];
		if (v1 >= limit && v2 >= limit) {
			dp[u] += 2;
			lst[u] = 0;
		} else if (v1 >= limit) {
			dp[u] += 1;
			lst[u] = v2;
		} else if (v2 >= limit) {
			dp[u] += 1;
			lst[u] = v1;
		} else if (v1 + v2 >= limit) {
			dp[u] += 1;
			lst[u] = 0;
		} else {
			lst[u] = std::max(v1, v2);
		}
	}
}
bool solve3_check(int x) {
	limit = x;
	solve3_dfs(1);
//	printf("check %d : %d\n", x, dp[1] >= m);
//	for (int i = 1; i <= n; i++) printf("%3d", son[i][0]); puts("");
//	for (int i = 1; i <= n; i++) printf("%3d", son[i][1]); puts("");
//	for (int i = 1; i <= n; i++) printf("%3d", sval[i][0]); puts("");
//	for (int i = 1; i <= n; i++) printf("%3d", sval[i][1]); puts("");
//	for (int i = 1; i <= n; i++) printf("%3d", dp[i]); puts("");
//	for (int i = 1; i <= n; i++) printf("%3d", lst[i]); puts("");
	return dp[1] >= m;
}
void solve3() {
//	printf("solve3\n");
	solve3_pre(1);
	l = 0, r = inf;
	while (l <= r) {
		mid = (l + r) >> 1;
		if (solve3_check(mid)) {
			l = mid + 1;
			ans = mid;
		} else {
			r = mid - 1;
		}
	}
	print(ans), putc('\n');
}
// end solve3

void dfs1(int u) {
	for (int i = hed[u], v = to[i]; i; i = nxt[i], v = to[i])
		if (v != fa[u]) {
			fa[v] = f[v][0] = u;
			dep[v] = dep[u] + 1;
			fae[v] = i, fav[v] = val[i];
			dfs1(v);
		}
}

int lca(int u, int v) {
	if (dep[u] > dep[v])
		std::swap(u, v);
	for (int i = 19; i >= 0; i--)
		if (dep[f[v][i]] >= dep[u])
			v = f[v][i];
	if (u == v)
		return u;
	for (int i = 19; i >= 0; i--)
		if (f[u][i] != f[v][i])
			u = f[u][i], v = f[v][i];
	return f[u][0];
}

void dfs2(int cnt) {
//	printf("dfs2(%d)\n", cnt);
//	for (int i = 1; i < n; i++)
//		printf("%d ", tag[i]);
//	puts("");
	if (cnt >= m) {
		find_ans = true;
		return;
	}
	for (int s = 1; s <= n && !find_ans; s++)
		for (int e = s + 1; e <= n && !find_ans; e++) {
			int u = s, v = e, t = lca(s, e), flag = 1, sum = 0;
			while (u != t && flag) flag = !tag[fae[u]], sum += fav[u], u = fa[u];
			while (v != t && flag) flag = !tag[fae[v]], sum += fav[v], v = fa[v];
			if (flag && sum >= limit) {
				u = s, v = e;
				while (u != t) tag[fae[u]] = 1, u = fa[u];
				while (v != t) tag[fae[v]] = 1, v = fa[v];
				dfs2(cnt + 1);
				u = s, v = e;
				while (u != t) tag[fae[u]] = 0, u = fa[u];
				while (v != t) tag[fae[v]] = 0, v = fa[v];
			}
		}
}

bool check(int x) {
	find_ans = false;
	limit = x;
	dfs2(0);
//	printf("check(%d) = %d\n", x, find_ans);
	return find_ans;
}

void main() {
//	freopen("3.txt", "r", stdin);
	flag1 = flag2 = 1;
	read(n), read(m);
	for (int i = 1; i < n; i++) {
		read(u), read(v), read(w);
		if (u != 1) flag1 = false;
		if (v != u + 1) flag2 = false;
		++deg[u], ++deg[v];
		nxt[tot] = hed[u], to[tot] = v, val[tot] = w, hed[u] = tot++;
		nxt[tot] = hed[v], to[tot] = u, val[tot] = w, hed[v] = tot++;
	}
//	printf("flag1 = %d | flag2 = %d\n", flag1, flag2);
	int max_deg = 0;
	for (int i = 1; i <= n; i++)
		max_deg = std::max(max_deg, deg[i]);
//	printf("max degree = %d\n", max_deg);
	if (flag1) { solve1(); return; }
	if (flag2) { solve2(); return; }
	if (max_deg <= 3) { solve3(); return; }
	dep[1] = 1, dfs1(1);
	if (m == 1) { solve0(); return; }
//	printf("main solve\n");
	for (int i = 1; i < 20; i++)
		for (int j = 1; j <= n; j++)
			f[j][i] = f[f[j][i - 1]][i - 1];
	l = 0, r = inf;
	while (l <= r) {
		mid = (l + r) >> 1;
		if (check(mid)) {
			l = mid + 1;
			ans = mid;
		} else {
			r = mid - 1;
		}
	}
	print(ans), putc('\n');
}
	
} int main() { return ringo::main(), 0; }

/* backup solve3 
int dp[maxn][3], g[maxn][4], son[maxn][2], cnt[maxn][2], sval[maxn][2];
void solve3_pre(int u) {
	for (int i = hed[u], v = to[i]; i; i = nxt[i], v = to[i])
		if (v != fa[u]) {
			fa[v] = u;
			son[u][cnt[u]++] = v;
			solve3_pre(v);
		}
}
void solve3_len(int u) {
	g[u][2] = 0;
	if (cnt[u] == 0) {
		g[u][0] = g[u][1] = -inf;
	} else if (cnt[u] == 1) {
		solve3_len(son[u][0]);
		g[u][1] = -inf;
		g[u][0] = g[son[u][0]][3] + sval[u][0];
	} else {
		solve3_len(son[u][0]);
		g[u][0] = g[son[u][0]][3] + sval[u][0];
		solve3_len(son[u][1]);
		g[u][1] = g[son[u][1]][3] + sval[u][1];
	}
	g[u][3] = std::max(g[u][0], std::max(g[u][1], g[u][2]));
}
bool solve3_check(int u) {
	if (cnt[u] == 0) {
		dp[u][0] = -inf;
		dp[u][1] = -inf;
		dp[u][2] = 0;
	} else if (cnt[u] == 1) {
		solve3_check(son[u][0]);
		for (int i = 0, v = son[u][0]; i < 3; i++)
			
		dp[u][1] = -inf;
		for (int i = 0, v = son[u][0]; i < 3; i++)
			dp[u][2] = std::max(dp[u][2], dp[v][i] + (sval[u][0] + g[v][i] >= limit ? 1 : 0));
	} else if (cnt[u] == 2) {
		for (int i = 0, v = son[u][0]; i < 3; i++)
			dp[u][0] = std::max(dp[u][0], dp[v][i] + (sval[v][i] + g[v][i] >= limit ? 1 : 0));
		for (int i = 0, v = son[u][1]; i < 3; i++)
			dp[u][1] = std::max(dp[u][1], dp[v][i] + (sval[v][i] + g[v][i] >= limit ? 1 : 0));
	}
}
void solve3() {
	solve3_pre1(1);
	l = 0, r = inf;
	while (l <= r) {
		mid = (l + r) >> 1;
		if (solve3_check(mid)) {
			l = mid + 1;
			ans = mid;
		} else {
			r = mid - 1;
		}
	}
	print(ans), putc('\n');
}
// end solve3
*/
