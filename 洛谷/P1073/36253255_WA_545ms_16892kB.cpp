// luogu-judger-enable-o2
// ==============================
//  author: memset0
//  website: https://memset0.cn
// ==============================
#include <bits/stdc++.h>
#define ll long long
#define rep(i,l,r) for (int i = l; i <= r; i++)
#define getc(x) getchar(x)
#define putc(x) putchar(x)

template <typename T> inline void read(T &x) {
	x = 0; register char ch; register bool fl = 0;
	while (ch = getc(), ch < 48 || 57 < ch) fl ^= ch == '-'; x = (ch & 15);
	while (ch = getc(), 47 < ch && ch < 58) x = (x << 1) + (x << 3) + (ch & 15);
	if (fl) x = -x;
}
template <typename T> inline void readc(T &x) {
	while (x = getc(), !islower(x) && !isupper(x));
}
template <typename T> inline void print(T x, char c = ' ') {
	static int buf[40];
	if (x == 0) { putc('0'); putc(c); return; }
	if (x < 0) putc('-'), x = -x;
	for (buf[0] = 0; x; x /= 10) buf[++buf[0]] = x % 10 + 48;
	while (buf[0]) putc((char) buf[buf[0]--]);
	putc(c);
}

const int maxn = 300010, maxm = 3000010;

int n, m, u, v, w, ans;
int dis[maxn], vis[maxn];
int tot, hed[maxn], nxt[maxm], to[maxm], val[maxm];

struct status {
	int u, v;
	inline bool operator < (const status &other) const {
		return v > other.v;
	}
};
std::priority_queue < status > q;

inline int id(int x, int i) { return x + n * i; }
inline void add_edge(int u, int v, int w) { nxt[++tot] = hed[u], to[tot] = v, val[tot] = w, hed[u] = tot++; }

void solve() {
	memset(dis, -63, sizeof(dis));
	q.push({1, 0}), dis[1] = 0;
	while (q.size()) {
		u = q.top().u, q.pop();
		if (vis[u]) continue;
		else vis[u] = 1;
		for (int i = hed[u], v = to[i]; i; i = nxt[i], v = to[i])
			if (dis[v] < dis[u] + val[i]) {
				dis[v] = dis[u] + val[i];
				q.push({v, dis[v]});
			}
	}
}

int main() {
	// freopen("1.in", "r", stdin);

	read(n), read(m);
	for (int i = 1; i <= n; i++) {
		read(w);
		add_edge(id(i, 0), id(i, 1), -w);
		add_edge(id(i, 1), id(i, 2), w);
	}
	for (int i = 1; i <= m; i++) {
		read(u), read(v), read(w);
		add_edge(id(u, 0), id(v, 0), w);
		add_edge(id(u, 1), id(v, 1), w);
		add_edge(id(u, 2), id(v, 2), w);
		if (w == 2) {
			add_edge(id(v, 0), id(u, 0), w);
			add_edge(id(v, 1), id(u, 1), w);
			add_edge(id(v, 2), id(u, 2), w);
		}
	}
	solve();
	ans = std::max(dis[id(n, 0)], dis[id(n, 2)]);
	print(ans, '\n');

	return 0;
}