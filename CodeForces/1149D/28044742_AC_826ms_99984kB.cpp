// =================================
//   author: memset0
//   date: 2019.05.01 10:38:17
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

const int N = 75, M = 1 << 17;
int col[N], id[N];
ll ans[N], dis[N][M];
bool tag[N], vis[N][M];
std::vector<int> node_set;
int n, m, id_cnt, col_cnt, key1, key2;

struct Map {
	std::vector<std::pair<int, int>> graph[N];
	inline void add_edge(int u, int v, int w) {
		graph[u].push_back(std::make_pair(v, w));
		graph[v].push_back(std::make_pair(u, w));
	}
} map0, map1, map2;

struct status {
	int u, s; ll w;
	inline bool operator < (const status &other) const {
		if (w != other.w) return w > other.w;
		if (u != other.u) return u > other.u;
		return s > other.s;
	}
};
std::priority_queue<status> q;

void dfs(int u) {
	tag[u] = 1;
	node_set.push_back(u);
	for (auto it : map1.graph[u]) {
		int v = it.first, w = it.second;
		if (!tag[v]) dfs(v);
	}
}

inline void push_status(int u, int s, ll w) {
	// printf("> %d %d %lld\n", u, s, w);
	if (w < dis[u][s]) {
		dis[u][s] = w;
		q.push((status){u, s, w});
	}
}

void main() {
	memset(ans, 0x3f, sizeof(ans));
	memset(dis, 0x3f, sizeof(dis));
	read(n), read(m), read(key1), read(key2);
	if (key1 > key2) std::swap(key1, key2);
	for (int u, v, w, i = 1; i <= m; i++) {
		read(u), read(v), read(w);
		map0.add_edge(u, v, w);
		if (w == key1) map1.add_edge(u, v, w);
		if (w == key2) map2.add_edge(u, v, w);
	}
	for (int i = 1; i <= n; i++) if (!tag[i]) {
		node_set.clear();
		dfs(i);
		++col_cnt;
		for (auto u : node_set) {
			col[u] = col_cnt;
		}
		if (node_set.size() > 3) {
			id[col_cnt] = ++id_cnt;
		}
	}
	// for (int i = 1; i <= n; i++) print(col[i], " \n"[i == n]);
	// for (int i = 1; i <= n; i++) print(id[col[i]], " \n"[i == n]);
	push_status(1, id[1] ? 1 : 0, 0);
	while (q.size()) {
		int u = q.top().u, s = q.top().s;
		q.pop();
		if (vis[u][s]) continue;
		vis[u][s] = 1;
		for (auto it : map0.graph[u]) {
			int v = it.first, w = it.second;
			// printf("%d -> %d : %lld\n", u, v, w);
			if (col[u] == col[v] && w == key2) continue;
			if (id[col[v]] && id[col[u]] != id[col[v]]) {
				if (s & (1 << (id[col[v]] - 1)))
					continue;
				push_status(v, s | (1 << (id[col[v]] - 1)), dis[u][s] + w);
			} else {
				push_status(v, s, dis[u][s] + w);
			}
		}
	}
	for (int x = 0; x < (1 << id_cnt); x++) {
		for (int i = 1; i <= n; i++)
			ans[i] = std::min(ans[i], dis[i][x]);
	}
	for (int i = 1; i <= n; i++) {
		print(ans[i], " \n"[i == n]);
	}
}

} signed main() {
#ifdef MEMSET0_LOCAL_ENVIRONMENT
	freopen("1.in", "r", stdin);
#endif
	return ringo::main(), 0;
} // 123123