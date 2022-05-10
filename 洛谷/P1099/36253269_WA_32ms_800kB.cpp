// ==============================
//  author: memset0
//  website: https://memset0.cn
// ==============================
#include <bits/stdc++.h>
#define ll long long
 
int read() {
    int x = 0; bool m = 0; char c = getchar();
    while (!isdigit(c) && c != '-') c = getchar();
    if (c == '-') m = 1, c = getchar();
    while (isdigit(c)) x = x * 10 + c - '0', c = getchar();
    if (m) return -x; else return x;
}

const int maxn = 310;

int n, s, m, l, r, u, v, w, ans, max;
int dis[maxn], cst[maxn], sum[maxn], q[maxn], pre[maxn];
int tot = 2, hed[maxn], nxt[maxn << 1], to[maxn << 1], val[maxn << 1];

void add_edge(int u, int v, int w)  {
	nxt[tot] = hed[u], to[tot] = v, val[tot] = w;
	hed[u] = tot++;
}

void bfs(int s) {
	memset(dis, 0, sizeof(dis));
	memset(pre, 0, sizeof(pre));
	l = r = 1, q[1] = s, dis[s] = 1;
	while (l <= r) {
		u = q[l++];
		for (int i = hed[u], v = to[i]; i; i = nxt[i], v = to[i])
			if (!dis[v]) {
				dis[v] = dis[u] + val[i];
				pre[v] = i;
				q[++r] = v;
			}
	}
}

int main() {
	n = read(), s = read();
	for (int i = 1; i < n; i++) {
		u = read(), v = read(), w = read();
		add_edge(u, v, w), add_edge(v, u, w);
	}
	bfs(1);
	for (int i = 1; i <= n; i++)
		if (dis[i] > dis[max])
			max = i;
	bfs(max);
	max = 0;
	for (int i = 1; i <= n; i++)
		if (dis[i] > dis[max])
			max = i;
	for (int i = pre[max]; i; i = pre[to[i ^ 1]]) {
//		printf("%d %d %d %d\n", i, to[i], to[i ^ 1], pre[to[i ^ 1]]);
		cst[++m] = val[i];
	}
	for (int i = 1; i <= m; i++)
		sum[i] = sum[i - 1] + cst[i];
	
	ans = sum[m];
	for (int i = 1, j = 0; i <= m; i++) {
		s += cst[i - 1];
		while (j <= m && s >= cst[j]) s -= cst[j++];
		ans = std::min(ans, std::max(sum[i - 1], sum[m] - sum[j - 1]));
	}
	printf("%d\n", ans);
	
	return 0;
}