#include <bits/stdc++.h>
#define il inline 
using namespace std;
const int maxn = 100010;
int n, ans, sum, a[maxn];

int i, j, l, r, k, u;
int mrk; char chr;
il void _R(int &x) {
	x = 0, chr = getchar(), mrk = 1;
	while (!('0' <= chr && chr <= '9') && chr != '-') chr = getchar();
	if (chr == '-') mrk = -1, chr = getchar();
	while ('0' <= chr && chr <= '9') x = x * 10 + chr - '0', chr = getchar();
	x *= mrk;
}

struct Str_Max {
	int val, left, right;
} Max, Now;

struct EdgeTree_Node {
	int l, r, mid, val, min, dnt;
};
struct EdgeTree {
	EdgeTree_Node p[maxn * 8];
	il void build(int u, int l, int r) {
		p[u].l = l, p[u].r = r, p[u].mid = (l + r) >> 1, p[u].dnt = 0;
		if (l == r) {
//			cout << l << " " << a[l] << endl;
			p[u].val = a[l];
			p[u].min = a[l];
		} else {
			build(u << 1, l, p[u].mid);
			build(u << 1 | 1, p[u].mid + 1, r);
			p[u].val = p[u << 1].val + p[u << 1 | 1].val;
			p[u].min = min(p[u << 1].min, p[u << 1 | 1].min);
		}
//		printf(">> %d %d %d %d %d %d %d\n", u, p[u].l, p[u].r, p[u].mid, p[u].val, p[u].ful, p[u].dnt);
	}
	il void update(int u, int l, int r, int v) {
		if (p[u].l == p[u].r) {
//			printf(">>%d %d %d\n", u, p[u].val, p[u].min);
			p[u].val -= v;
			p[u].min -= v;
//			printf(">>%d %d %d\n", u, p[u].val, p[u].min);
			if (p[u].min < 0) printf("[WARN] bad edge tree!\n");
		} else {
			if (r <= p[u].mid) update(u << 1, l, r, v);
			else if (l > p[u].mid) update(u << 1 | 1, l, r, v);
			else {
				update(u << 1, l, p[u].mid, v);
				update(u << 1 | 1, p[u].mid + 1, r, v);
			}
			p[u].val = p[u << 1].val + p[u << 1 | 1].val;
			p[u].min = min(p[u << 1].min, p[u << 1 | 1].min);
		}
	}
	il int query(int u, int l, int r) {
//		printf("<<%d %d %d %d\n", u, p[u].l, p[u].r, p[u].min);
		if (l == p[u].l && r == p[u].r) {
			return p[u].min;
		} else {
			if (r <= p[u].mid) return query(u << 1, l, r);
			else if (l > p[u].mid) return query(u << 1 | 1, l, r);
			else return min(query(u << 1, l, p[u].mid), query(u << 1 | 1, p[u].mid + 1, r));
		}
	}
} t;

int main() {
//	freopen("block.in", "r", stdin);
//	freopen("block.out", "w", stdout);
//	freopen("data.txt", "r", stdin);
	_R(n);
	for (i = 1; i <= n; ++i) _R(a[i]);
	for (i = 1; i <= n; ++i) sum += a[i];
	t.build(1, 1, n);
	for (i = n; sum; i--) {
		for (l = 1, r = l + i - 1; r <= n; ++l, ++r) {
			u = t.query(1, l, r);
//			cout << l << " " << r << " " << u << " " << sum << endl;
			if (u > 0) {
				t.update(1, l, r, u);
				sum -= (r - l + 1) * u;
			}
			ans += u;
		}
	}
	printf("%d\n", ans);
	return 0;
}
