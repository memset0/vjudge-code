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

const int maxn = 5010;
int n, m, u, v, ss, tim, cnt, max_ind;
int fr[maxn], fa[maxn], ans[maxn], now[maxn], vis[maxn], ind[maxn];
int tot = 2, hed[maxn], to[maxn << 1], nxt[maxn << 1];
std::vector < int > p[maxn];

void dfs1(int u) {
//	printf("dfs1 %d\n", u);
	ans[++tim] = u;
	for (int i = hed[u], v = to[i]; i; i = nxt[i], v = to[i])
		if (v != fa[u]) {
			fa[v] = u;
			p[u].push_back(v);
		}
	std::sort(p[u].begin(), p[u].end());
	for (int i = 0; i < (int)p[u].size(); i++)
		dfs1(p[u][i]);
}

void dfs2(int u) {
//	printf("dfs2 %d\n", u);
	if (cnt == n) {
//		for (int i = 1; i <= n; i++)
//			printf("%d ", now[i]);
//		puts("");
		for (int i = 1; i <= n; i++)
			if (now[i] < ans[i] || !ans[i]) {
				for (int i = 1; i <= n; i++)
					ans[i] = now[i];
				break;
			} else if (now[i] > ans[i]) {
				break;
			}
	}
	for (int i = hed[u], v = to[i]; i; i = nxt[i], v = to[i])
		if (!vis[v]) {
			vis[v] = 1;
			fr[v] = u;
			now[++cnt] = v;
			dfs2(v);
			now[cnt--] = 0;
			fr[v] = 0;
			vis[v] = 0;
		} else if (v == fr[u]) {
			dfs2(v);
		}
}

void dfs4(int u) {
//	printf("dfs4 %d %d\n", u, ss);
	ans[++tim] = u, vis[u] = 1;
	for (int i = hed[u], v = to[i]; i; i = nxt[i], v = to[i])
		if (!vis[v]) {
			if (ss && ss < v)
				v = ss, ss = 0;
			dfs4(v);
		}
}

void main() {
//	freopen("3.txt", "r", stdin);
	
	read(n), read(m);
	for (int i = 1; i <= m; i++) {
		read(u), read(v);
		++ind[u], ++ind[v];
		nxt[tot] = hed[u], to[tot] = v, hed[u] = tot++;
		nxt[tot] = hed[v], to[tot] = u, hed[v] = tot++;
	}
	for (int i = 1; i <= n; i++)
		max_ind = std::max(max_ind, ind[i]);
	if (m == n - 1) {
		dfs1(1);
	} else if (max_ind <= 2) {
//		printf("max ind <= 2\n");
		ans[1] = tim = vis[1] = 1;
		int s1 = 0, s2 = 0;
		for (int i = hed[1], v = to[i]; i; i = nxt[i], v = to[i])
			if (s1) s2 = v;
			else s1 = v;
		if (s1 < s2) ss = s2, dfs4(s1);
		else ss = s1, dfs4(s2);
	} else {
		now[1] = cnt = vis[1] = 1;
		dfs2(1);
	}
	for (int i = 1; i <= n; i++)
		print(ans[i]), putc(i == n ? '\n' : ' ');
}
	
} int main() { ringo::main(); return 0; }

//void dfs2(int u) {
//	vis[u] = 1;
//	for (int i = hed[u], v = to[i]; i; i = nxt[i], v = to[i])
//		if (!vis[v]) {
//			fa[v] = u;
//			dep[v] = dep[u] + 1;
//			dfs2(v);
//		} else if (v != fa[u]) {
//			su = u, sv = v;
//			// ÌØÊâ±ß 
//		}
//}
//
//void dfs3(int u) {
//	vis[u] = 1, ans[++tim] = u;
//	if (ins[u] && !sos) {
//		sos = 1;
//	}
//}
//
//void color(int u, int v)  {
//	if (dep[u] > dep[v])
//		std::swap(u, v);
//	while (dep[v] > dep[u])
//		ins[v] = 1, v = fa[v];
//	while (u != v) {
//		ins[u] = ins[v] = 1;
//		u = fa[u], v = fa[v];
//	}
//	ins[u] = 1;
//}
