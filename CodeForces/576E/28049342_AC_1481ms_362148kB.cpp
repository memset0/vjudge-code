#include <bits/stdc++.h>
#define root 1, q, 1
#define ls l, mid, k << 1
#define rs mid + 1, r, k << 1 | 1
using namespace std;
int read();
int n, m, k, q;
struct E {
	int u, v, c;
} e[500005];

struct P {
	int e, c;
} p[500005];

vector<int> chan[500005];
vector<int>::iterator pos[500005];

struct Dsu {
	int fa[500005];
	bool fw[500005];
	short h[500005];
	bool check(int id) {
		int u = e[id].u, v = e[id].v, w = 0;
		while (fa[u]) w ^= fw[u], u = fa[u];
		while (fa[v]) w ^= fw[v], v = fa[v];
		return u != v || w;
	}
	E merge(int u, int v) {
		int w = 1;
		while (fa[u]) w ^= fw[u], u = fa[u];
		while (fa[v]) w ^= fw[v], v = fa[v];
		if (u == v) return (E){0};
		h[u] > h[v] ? swap(u, v) : void(), fa[u] = v, fw[u] = w;
		return (E){u, v, (h[u] == h[v]) ? h[v]++ : h[v]};
	}
} dsu[51];

struct Seg {
	vector<E> t[2000006], rec[202];
	void ins(int k, int d) {
		rec[d].clear();
		for (int i = 0; i < t[k].size(); ++i) rec[d].push_back(dsu[t[k][i].c].merge(t[k][i].u, t[k][i].v));
	}
	void del(int k, int d) {
		for (int i = t[k].size() - 1; i >= 0; --i) {
			if (!rec[d][i].u) continue;
			int u = rec[d][i].u, v = rec[d][i].v, c = t[k][i].c;
			dsu[c].fa[u] = dsu[c].fw[u] = 0, dsu[c].h[v] = rec[d][i].c;
		}
	}
	void modi(int l, int r, int k, int st, int en, E v) {
		if (st > r || en < l) return;
		if (st <= l && en >= r) return t[k].push_back(v);
		int mid = l + r >> 1;
		modi(ls, st, en, v), modi(rs, st, en, v);
	}
	void work(int l, int r, int k, int d) {
		ins(k, d);
		if (l == r) {
			int id = p[l].e;
			++pos[id], dsu[p[l].c].check(id) ? (puts("YES"), e[id].c = p[l].c) : (puts("NO"));
			return modi(root, l + 1, (*pos[id]) - 1, e[id]), del(k, d);
		}
		int mid = l + r >> 1;
		work(ls, d + 1), work(rs, d + 1), del(k, d);
	}
} seg;

int main() {
	n = read(), m = read(), k = read(), q = read();
	for (int i = 1; i <= m; ++i) e[i].u = read(), e[i].v = read();
	for (int i = 1; i <= q; ++i) p[i].e = read(), p[i].c = read(), chan[p[i].e].push_back(i);
	for (int i = 1; i <= m; ++i) chan[i].push_back(q + 1), pos[i] = chan[i].begin();
	seg.work(root, 0);
	return 0;
}

int read() {
	int x = 0, f = 1;
	char c = getchar();
	while (c < '0' || c > '9') f = (c == '-') ? -1 : f, c = getchar();
	while (c >= '0' && c <= '9') x = x * 10 + c - '0', c = getchar();
	return x * f;
}