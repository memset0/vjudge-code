// ==============================
//  author: memset0
//  website: https://memset0.cn
// ==============================
#include <bits/stdc++.h>
#define ll long long
using namespace std;

int read() {
    int x = 0; bool m = 0; char c = getchar();
    while (!isdigit(c) && c != '-') c = getchar();
    if (c == '-') m = 1, c = getchar();
    while (isdigit(c)) x = x * 10 + c - '0', c = getchar();
    if (m) return -x; else return x;
}

const int maxn = 100010, maxm = 200010;

int n, m, p, u, k, v, w, l, r, t;
int ans;
int dis[maxn], q[maxn * 100], id[maxn], f[maxn][51];
bool inq[maxn];

struct graph {
	int tot, hed[maxn], nxt[maxm], to[maxm], val[maxm];
	inline void add_edge(int u, int v, int w) {
		nxt[tot] = hed[u], to[tot] = v, val[tot] = w;
		hed[u] = tot++;
	}
} h, g;


bool cmp(int a, int b) {
	if (dis[a] != dis[b]) return dis[a] < dis[b];
	return a < b;
}

int main() {
//	freopen("INPUT", "r", stdin);
	
	t = read();
	while (t--) {
		h.tot = g.tot = 2, ans = 0;
		memset(h.hed, 0, sizeof(h.hed));
		memset(g.hed, 0, sizeof(g.hed));
		memset(dis, -1, sizeof(dis));
		
		n = read(), m = read(), k = read(), p = read();
		for (int i = 1; i <= m; i++) {
			u = read(), v = read(), w = read();
			g.add_edge(u, v, w);
			h.add_edge(v, u, w);
		}
		
		l = r = 1, q[1] = 1, dis[1] = 0, inq[1] = 1;
		while (l <= r) {
			u = q[l++], inq[u] = 0;
			for (int i = g.hed[u]; i; i = g.nxt[i]) {
				v = g.to[i];
				if (!~dis[v] || dis[v] > dis[u] + g.val[i]) {
					dis[v] = dis[u] + g.val[i];
					if (!inq[v]) {
						inq[v] = 1;
						q[++r] = v;
					}
				}
			}
		}
		
//		for (int i = 1; i <= n; i++)
//			printf("%d ", dis[i]);
//		puts("");
		for (int i = 1; i <= n; i++)
			id[i] = i;
		sort(id + 1, id + n + 1, cmp);
		
		f[1][0] = 1;
		for (int q = 0; q <= k; q++)
			for (int i = 1; i <= n; i++) {
				u = id[i];
				for (int j = h.hed[u]; j; j = h.nxt[j]) {
					v = h.to[j];
					t = dis[v] + h.val[j] - dis[u];
//					printf("%d -> %d : %d\n", v, u, t);
					f[u][q] += q >= t ? f[v][q - t] : 0;
				}
			}
		
//		for (int i = 1; i <= n; i++) {
//			for (int j = 0; j <= k; j++)
//				printf("%d ", f[i][j]);
//			puts("");
//		}
		for (int i = 0; i <= k; i++)
			ans += f[n][i];
		printf("%d\n", ans);
		
	}
	
	return 0;
}