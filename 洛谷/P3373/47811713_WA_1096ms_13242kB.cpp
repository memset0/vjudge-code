#include <bits/stdc++.h>
using namespace std;
const int maxn = 100010;
int n, m, ans, a[maxn];
long long M, s[maxn];
struct Node {
	int l, r, mid;
	long long val, dts, dtm;
} p[maxn * 4];
void push_up(int u, int s, int m) {
	p[u].val = (p[u].val * m + s) % M;
	p[u].dts = p[u].dts * m + s;
	p[u].dtm = p[u].dtm * m;
}
void push_down(int u) {
	if (p[u].dts != 0 || p[u].dtm != 1) {
		if (p[u].l != p[u].r) {
			push_up(u << 1, p[u].dts, p[u].dtm);
			push_up(u << 1 | 1, p[u].dts, p[u].dtm);
		}
		p[u].dts = 0, p[u].dtm = 1;
	}
}
void build(int u, int l, int r) {
	p[u].l = l, p[u].r = r, p[u].mid = (l + r) / 2;
	p[u].val = (s[r] - s[l - 1]) % M;
	p[u].dts = 0, p[u].dtm = 1;
	if (l == r) return ;
	build(u << 1, l, p[u].mid);
	build(u << 1 | 1, p[u].mid + 1, r);
}
void update(int u, int l, int r, int s, int m) {
	push_down(u);
	if (l == p[u].l && r == p[u].r) {
		push_up(u, s, m);
		return ;
	}
	if (r <= p[u].mid) update(u << 1, l, r, s, m);
	else if (l > p[u].mid) update(u << 1 | 1, l, r, s, m);
	else {
		update(u << 1, l, p[u].mid, s, m);
		update(u << 1 | 1, p[u].mid + 1, r, s, m);
	}
	p[u].val = (p[u << 1].val + p[u << 1 | 1].val) % M;
}
void query(int u, int l, int r) {
	push_down(u);
	if (l == p[u].l && r == p[u].r) {
		ans = (ans + p[u].val) % M;
		return ;
	}
	if (r <= p[u].mid) query(u << 1, l, r);
	else if (l > p[u].mid) query(u << 1 | 1, l, r);
	else {
		query(u << 1, l, p[u].mid);
		query(u << 1 | 1, p[u].mid + 1, r);
	}
}
int main() {
	scanf("%d%d%lld", &n, &m, &M);
	for (int i = 1; i <= n; i++) {
		scanf("%d", &a[i]);
		s[i] = s[i - 1] + a[i];
	}
	build(1, 1, n);
	int x, y, k;
	for (int i = 1; i <= m; i++) {
		scanf("%d", &x);
		if (x == 1) {
			scanf("%d%d%d", &x, &y, &k);
			update(1, x, y, 0, k % M);
		} else if (x == 2) {
			scanf("%d%d%d", &x, &y, &k);
			update(1, x, y, k % M, 1);
		} else if (x == 3) {
			scanf("%d%d", &x, &y);
			ans = 0;
			query(1, x, y);
			printf("%d\n", ans);
		}
	}
	return 0;
}