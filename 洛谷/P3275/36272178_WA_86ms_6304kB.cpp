// luogu-judger-enable-o2
// ==============================
//  author: memset0
//  website: https://memset0.cn
// ==============================
#include <bits/stdc++.h>
#define ll long long
#define rep(i,l,r) for (int i = l; i <= r; i++)

int read() {
	int x = 0; bool m = 0; char c = getchar();
	while (!isdigit(c) && c != '-') c = getchar();
	if (c == '-') m = 1, c = getchar();
	while (isdigit(c)) x = x * 10 + c - '0', c = getchar();
	if (m) return -x; else return x;
}

const int maxn = 100010, maxe = 400010;

int n, m, u, v, x, y, opt, dis[maxn];
ll ans;
int cnt[maxn], inq[maxn];
std::queue<int> q;

int tot = 2, hed[maxn], nxt[maxe], to[maxe], val[maxe], cst[maxe];

inline void add_edge(int u, int v, int w)
	{ nxt[tot] = hed[u], to[tot] = v, val[tot] = w, hed[u] = tot++; }

void spfa(int s) {
	memset(dis, -125, sizeof(dis));
	q.push(s), inq[s] = 1, dis[s] = 0, cnt[s] = 1;
	while (!q.empty()) {
		u = q.front(), q.pop();
		for (int i = hed[u], v = to[i]; i; i = nxt[i], v = to[i])
			if (dis[u] + val[i] > dis[v]) {
				dis[v] = dis[u] + val[i];
				if (!inq[v]) {
					if (++cnt[v] >= n) { printf("%d: %d\n", v, cnt[v]); puts("-1"); exit(0); }
					inq[v] = 1, q.push(v);
				}
			}
		inq[u] = 0;
	}
}

int main() {
	n = read(), m = read();
	for (int i = n; i; i--) add_edge(0, i, 1);
	rep(i, 1, m) {
		opt = read(), x = read(), y = read();
		if (x == y) {
			if (opt == 2 || opt == 4) { puts("-1"); exit(0); }
		}
		switch (opt) {
			case 1: add_edge(x, y, 0), add_edge(y, x, 0); break;
			case 2: add_edge(x, y, 1); break;
			case 3: add_edge(y, x, 0); break;
			case 4: add_edge(y, x, 1); break;
			case 5: add_edge(x, y, 0); break;
		}
	}
	spfa(0);
//	for (int i = 1; i <= n; i++)
//		printf("%d ", dis[i]);
//	puts("");
	for (int i = 1; i <= n; i++) {
		ans += dis[i];
	} 
	printf("%lld\n", ans);
	return 0;
}