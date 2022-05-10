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

const int maxn = 2010, maxm = 6010;

int T, n, m, l, r, u, v, w;
int q[maxn], dis[maxm], cnt[maxn], inq[maxn];
int tot = 2, hed[maxn], nxt[maxm], to[maxm], val[maxm];

void add_edge(int u, int v, int w) {
	nxt[tot] = hed[u], to[tot] = v, val[tot] = w;
	hed[u] = tot++;
}

bool spfa() {
	memset(dis, 63, sizeof(dis));
	memset(cnt, 0, sizeof(cnt));
	l = r = 0, q[0] = 1, cnt[1] = inq[1] = 1, dis[1] = 0;
	while (l <= r) {
//		printf("%d\n", u);
		u = q[(l++) % n], inq[u] = 	0;
		for (int i = hed[u]; i; i = nxt[i]) {
			v = to[i];
			if (dis[u] + val[i] < dis[v]) {
				dis[v] = dis[u] + val[i];
				if (!inq[v]) {
					inq[v] = 1;
					if (++cnt[v] == n) {
						return true;
					}
					q[(++r) % n] = v;
				} 
			} 
		} 
	}
	return false;
}

int main() {
	T = read();
	while (T--) {
		tot = 2, memset(hed, 0, sizeof(hed));
		n = read(), m = read();
		for (int i = 1; i <= m; i++) {
			u = read(), v = read(), w = read();
			if (w >= 0) {
				add_edge(u, v, w);
				add_edge(v, u, w);
			} else {
				add_edge(u, v, w);
			}
		}
		printf("%s\n", spfa() ? "YES" : "NO");
	}
	return 0;
}
