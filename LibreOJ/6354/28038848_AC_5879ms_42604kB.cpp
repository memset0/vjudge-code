// =================================
//   author: memset0
//   date: 2019.05.24 06:42:57
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

const int N = 2e5 + 10, M = 3e6 + 10;
int n, m, c, s, e, p, lim = 1; ll dis[N];
int tot = 2, hed[N], to[M << 1], val[M << 1], nxt[M << 1];

inline void add_edge(int u, int v, int w) {
	// printf("add edge %d %d %d\n", u, v, w);
	nxt[tot] = hed[u], to[tot] = v, val[tot] = w, hed[u] = tot++;
}

struct status {
	int u; ll w;
	inline status() {}
	inline status(int _u, int _w) { u = _u, w = _w; }
	inline bool operator<(const status &other) const {
		return w > other.w;
	}
};
std::priority_queue<status> q;

void main() {
	read(n), read(m), read(c);
	for (int u, v, w, i = 1; i <= m; i++) {
		read(u), read(v), read(w);
		add_edge(u, v, w);
	}
	while (lim < n) lim <<= 1, ++p;
	for (int i = 0; i < lim; i++)
		for (int k = 0; k <= p; k++) {
			int j = i ^ (1 << k);
			if (0 <= j && j <= lim) add_edge(i, j, (1 << k) * c);
		}
	read(s), read(e);
	memset(dis, 63, sizeof(dis)), dis[s] = 0;
	q.push(status(s, 0));
	while (q.size()) {
		int u = q.top().u; q.pop();
		for (int i = hed[u], v, w; v = to[i], w = val[i], i; i = nxt[i])
			if (dis[u] + w < dis[v]) {
				dis[v] = dis[u] + w;
				q.push(status(v, dis[v]));
			}
	}
	print(dis[e], '\n');
}

} signed main() {
#ifdef MEMSET0_LOCAL_ENVIRONMENT
	freopen("1.in", "r", stdin);
#endif
	return ringo::main(), 0;
}
