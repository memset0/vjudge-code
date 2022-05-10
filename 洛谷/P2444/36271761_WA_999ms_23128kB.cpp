// luogu-judger-enable-o2
// =================================
//   author: memset0
//   date: 2019.01.07 08:46:27
//   website: https://memset0.cn/
// =================================
#include <bits/stdc++.h>
#define ll long long
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

const int N = 1e4 + 10, M = 2e6 + 10;
int n, m, x, l, r, t, p, tot;
int q[M], cnt[M], dis[M];
char a[N];
bool inq[M];

struct node {
	int ch[2], to[2], fail;
	bool tag;
} e[M];

void insert(char *a) {
	int len = strlen(a);
	p = 1;
	for (int i = 0; i < len; i++) {
		x = a[i] == '0' ? 0 : 1;
		if (!e[p].ch[x]) e[p].ch[x] = ++tot;
		p = e[p].ch[x];
	}
	e[p].tag = 1;
}

void build_fail() {
	std::queue <int> q; q.push(1); int p;
	while (q.size()) {
		p = q.front(), q.pop();
		for (int i = 0; i < 2; i++)
			if (e[p].ch[i]) {
				if (p == 1) e[e[p].ch[i]].fail = 1;
				else {
					t = e[p].fail;
					while (t) {
						if (e[t].ch[i]) {
							e[e[p].ch[i]].fail = e[t].ch[i];
							break;
						}
						t = e[t].fail;
					}
					if (!t) e[e[p].ch[i]].fail = 1;
				}
				q.push(e[p].ch[i]);
			}
	}
}

void pre() {
	for (int u = 1, p; u <= tot; u++)
		for (int i = 0; i < 2; i++)
			if (e[u].ch[i]) e[u].to[i] = e[u].ch[i];
			else {
				bool flag = false;
				for (p = u; !e[p].ch[i] && p != 1; p = e[p].fail) flag |= e[p].tag;
				e[u].to[i] = flag ? 0 : e[p].ch[i] ? e[p].ch[i] : 1;
			}
}

void dfs(int u) {
	if (!u) return;
	printf("%d : ch %d %d to %d %d fail %d\n", u, e[u].ch[0], e[u].ch[1], e[u].to[0], e[u].to[1], e[u].fail);
	for (int i = 0; i < 2; i++) dfs(e[u].ch[i]);
}

bool spfa() {
	memset(inq, 0, sizeof(inq));
	memset(cnt, 0, sizeof(cnt));
	memset(dis, 0, sizeof(dis));
	int u, v, l = 0, r = 0; q[0] = 1, dis[1] = 0;
	while (l <= r) {
		u = q[(l++) % tot];
		for (int i = 0; i < 2; i++) {
			v = e[u].to[i];
			if (dis[u] + 1 > dis[v] && v && !e[v].tag) {
				dis[v] = dis[u] + 1;
				// printf("%d -> %d : %d %d\n", u, v, dis[u], dis[v]);
				if (!inq[v]) {
					if (++cnt[v] >= tot) return true;
					inq[q[(++r) % tot] = v];
				}
			}
		}
	}
	return false;
}

void main() {
	read(n), tot = 1;
	for (int i = 1; i <= n; i++) scanf("%s", a), insert(a);
	build_fail(), pre(), puts(spfa() ? "TAK" : "NIE");
}

} signed main() { return ringo::main(), 0; }