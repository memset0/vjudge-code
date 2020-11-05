// =================================
//   author: memset0
//   date: 2019.08.03 17:05:46
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
template <class T> inline void print(const std::vector<T> &vet) {
	for (auto it : vet) print(it), putchar(' ');
}
template <class T> inline void print(T x, char c) { print(x), putchar(c); }
template <class T> inline void print(T a, int l, int r, std::string s = "") {
	if (s != "") std::cout << s << ": ";
	for (int i = l; i <= r; i++) print(a[i], " \n"[i == r]);
}

const int N = 110, M = 1e5 + 10, mod = 1e9 + 7;
bool vis[N];
std::map<int, int> map;
std::vector<int> node, vet, dp[N][2];
int n, m, ans, sum, cnt, nod, fa[N], fa_x[N], fac[M], ifac[M], mov[1 << 20];

struct edge_t { int u, v, w; };
std::vector<edge_t> e, edge, rest, G[N];

inline int dec(int a, int b) { a -= b; return a < 0 ? a + mod : a; }
inline int inc(int a, int b) { a += b; return a >= mod ? a - mod : a; }
inline int mul(int a, int b) { return (ll)a * b - (ll)a * b / mod * mod; }

inline void inc_f(int &a, int b) { a += b; if (a >= mod) a -= mod; }
inline int find(int x) { return fa[x] == x ? x : fa[x] = find(fa[x]); }
inline int find_x(int x) { return fa_x[x] == x ? x : fa_x[x] = find_x(fa_x[x]); }
inline int binom(int n, int m) { return n < m ? 0 : mul(fac[n], mul(ifac[m], ifac[n - m])); }

int get_id(int x) {
	auto it = map.find(x);
	return it == map.end() ? map[x] = ++nod : it->second;
}

std::vector<int> inc(const std::vector<int> &a, const std::vector<int> &b) {
	std::vector<int> c(std::max(a.size(), b.size()));
	for (int i = 0; i < a.size(); i++) c[i] = a[i];
	for (int i = 0; i < b.size(); i++) c[i] = inc(c[i], b[i]);
	return c;
}

std::vector<int> mul(const std::vector<int> &a, const std::vector<int> &b) {
	std::vector<int> c(a.size() + b.size() - 1);
	for (int i = 0; i < a.size(); i++)
		for (int j = 0; j < b.size(); j++)
			c[i + j] = (c[i + j] + (ll)a[i] * b[j]) % mod;
	return c;
}

void init_fac(int n) {
	fac[0] = fac[1] = ifac[0] = ifac[1] = 1;
	for (int i = 2; i <= n; i++) fac[i] = mul(fac[i - 1], i);
	for (int i = 2; i <= n; i++) ifac[i] = mul(mod - mod / i, ifac[mod % i]);
	for (int i = 2; i <= n; i++) ifac[i] = mul(ifac[i - 1], ifac[i]);
}

void dfs(int u, int father) {
	// printf("dfs %d %d\n", u, father);
	dp[u][0] = std::vector<int>{1};
	dp[u][1] = std::vector<int>{};
	for (auto it : G[u]) {
		int v = it.v, w = it.w;
		if (v != father) {
			// printf("%d %d %d\n", u, v, w);
			dfs(v, u);
			if (!vis[u] && !vis[v]) {
				dp[u][1] = inc(mul(dp[u][1], inc(dp[v][0], dp[v][1])), mul(dp[u][0], mul(dp[v][0], std::vector<int>{0, w})));
			} else {
				dp[u][1] = mul(dp[u][1], inc(dp[v][0], dp[v][1]));
			}
			dp[u][0] = mul(dp[u][0], inc(dp[v][0], dp[v][1]));
		}
	}
}

std::vector<int> solve(int now) {
	node.clear(), edge.clear();
	for (int i = 1; i <= nod; i++) if (find(i) == now) node.push_back(i);
	for (const auto &it : e) if (find(it.u) == now) edge.push_back(it);
	// printf("solve %d\n", now);
	// for (auto it : node) print(it, ' '); puts("");
	// for (auto it : edge) printf("(%d %d %d) ", it.u, it.v, it.w), puts("");
	if (node.size() == 1) return std::vector<int>{1};

	std::vector<int> res(edge.size() + 1);
	if (node.size() <= 20) {
		std::map<int, int> map;
		for (int i = 0; i < node.size(); i++) map[node[i]] = i;
		memset(mov, 0, 1 << node.size() << 2);
		mov[0] = 1;
		for (int i = 0, u, v; i < edge.size(); i++) {
			u = map[edge[i].u], v = map[edge[i].v];
			for (int x = (1 << node.size()) - 1; x >= 0; x--)
				if (mov[x] && (x & (1 << u)) == 0 && (x & (1 << v)) == 0) {
					// printf("%d -> %d : %d\n", x, x | (1 << u) | (1 << v), mul(mov[x], edge[i].w));
					inc_f(mov[x | (1 << u) | (1 << v)], mul(mov[x], edge[i].w));
				}
		}
		for (int x = 0; x < (1 << node.size()); x++) if (mov[x]) {
			// printf("%d %d : %d\n", x, __builtin_popcount(x) >> 1, mov[x]);
			inc_f(res[__builtin_popcount(x) >> 1], mov[x]);
		}
		return res;
	} else {
		rest.clear();
		for (auto it : node) fa_x[it] = it;
		for (auto it : edge)
			if (find_x(it.u) != find_x(it.v)) {
				G[it.u].push_back({it.u, it.v, it.w});
				G[it.v].push_back({it.v, it.u, it.w});
				fa_x[find_x(it.u)] = find_x(it.v);
				// printf("USED %d %d %d\n", it.u, it.v, it.w);
			} else {
				rest.push_back(it);
				// printf("REST %d %d %d\n", it.u, it.v, it.w);
			}
		for (int x = 0; x < (1 << rest.size()); x++) {
			sum = 1, cnt = 0;
			memset(vis, 0, nod + 1);
			for (int i = 0; i < rest.size(); i++) if ((x >> i) & 1) {
				if (vis[rest[i].u] || vis[rest[i].v]) { sum = 0; break; }
				++cnt, sum = mul(sum, rest[i].w);
				vis[rest[i].u] = vis[rest[i].v] = 1;
			}
			if (sum) {
				dfs(now, 0);
				std::vector<int> tmp(cnt + 1); tmp[cnt] = sum;
				res = inc(res, mul(tmp, inc(dp[now][0], dp[now][1])));
			}
		}
		return res;
	}
}

void main() {
	read(m), read(n), init_fac(std::max(n, m));
	for (int x, y, w, i = 1; i <= n; i++) {
		read(x), read(y), read(w);
		if (w != 1) e.push_back({get_id(x), get_id(y + m), w - 1});
	}
	for (int i = 1; i <= nod; i++) fa[i] = i;
	for (edge_t it : e) fa[find(it.u)] = find(it.v);
	vet.push_back(1);
	for (int i = 1; i <= nod; i++) if (find(i) == i) {
		vet = mul(vet, solve(i));
	}
	for (int i = 0; i < vet.size() && i <= m; i++) {
		ans = inc(ans, mul(vet[i], fac[m - i]));
		// printf(">> %d %d : %d\n", vet[i], fac[m - i], ans);
	}
	print(ans, '\n');
}

} signed main() {
#ifdef memset0
	freopen("1.in", "r", stdin);
#endif
	return ringo::main(), 0;
}