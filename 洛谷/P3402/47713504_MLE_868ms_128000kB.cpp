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

const int maxn = 100010, maxm = 200010, maxl = 2200010;

int n, m, u, v, k, pos, opt;
int root[maxm], lc[maxl], rc[maxl], val[maxl];

struct pair {
	int fa, dep;
	pair() {}
	pair(int a, int b)  {
		fa = a, dep = b;
	}
} x, y;

void build(int &u, int l, int r) {
	u = ++pos;
	if (l == r) { val[u] = l; return; }
	int mid = (l + r) >> 1;
	build(lc[u], l, mid);
	build(rc[u], mid + 1, r);
}
int query(int u, int l, int r, int k) {
	if (l == r) return val[u];
	int mid = (l + r) >> 1;
	if (k <= mid) return query(lc[u], l, mid, k);
	else return query(rc[u], mid + 1, r, k);
}
void modify(int &u, int l, int r, int k, int c) {
	u = ++pos;
	if (l == r) { val[u] = c; return; }
	int mid = (l + r) >> 1;
	if (k <= mid) modify(lc[u], l, mid, k, c);
	else modify(rc[u], mid + 1, r, k, c);
}

pair find(int root, int u) {
	int f = query(root, 1, n, u);
	if (u == f) return pair(u, 1);
	pair ret = find(root, f);
	ret.dep += 1;
	return ret;
}

int main() {
	
	n = read(), m = read();
	build(root[0], 1, n);
	for (int i = 1; i <= m; i++) {
		root[i] = root[i - 1];
		opt = read();
		if (opt == 1) {
			u = read(), v = read();
			x = find(root[i], u);
			y = find(root[i], v);
			if (x.fa != y.fa) {
				if (x.dep < y.dep) modify(root[i], 1, n, x.fa, y.fa);
				else modify(root[i], 1, n, y.fa, x.fa);
			} 
		} else if (opt == 2) {
			k = read();
			root[i] = root[k];
		} else {
			u = read(), v = read();
			x = find(root[i], u);
			y = find(root[i], v);
			if (x.fa == y.fa) puts("1");
			else puts("0");
		}
	}

	return 0;
}
