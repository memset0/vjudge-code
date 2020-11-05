#include <bits/stdc++.h>
#define LL long long
#define pb push_back
#define mp make_pair
#define pii pair<int, int>
using namespace std;
inline int read() {
	int v = 0, f = 1;
	char c = getchar();
	while (c < '0' || c > '9') {
		if (c == '-') f = -1;
		c = getchar();
	}
	while (c >= '0' && c <= '9') {
		v = v * 10 + c - '0';
		c = getchar();
	}
	return v * f;
}
const int Maxn = 250005;
int n, a[Maxn];
int ans[Maxn], res[Maxn], dep[Maxn], par[Maxn][20], dp[Maxn];
int bit[Maxn], tree[Maxn * 20], lson[Maxn * 20], rson[Maxn * 20], root[Maxn], kc;
void Add(int pos, int v) {
	while (pos < Maxn) {
		bit[pos] = max(bit[pos], v);
		pos += pos & -pos;
	}
}
int Qry(int pos) {
	int ret = 0;
	while (pos) {
		ret = max(ret, bit[pos]);
		pos -= pos & -pos;
	}
	return ret;
}
int lca(int u, int v) {
	if (dep[u] < dep[v]) swap(u, v);
	int dlt = dep[u] - dep[v];
	for (int i = 0; i < 20; i++) {
		if (dlt >> i & 1) u = par[u][i];
	}
	if (u == v) return u;
	for (int i = 19; i >= 0; i--) {
		if (par[u][i] != par[v][i]) {
			u = par[u][i];
			v = par[v][i];
		}
	}
	return par[u][0];
}
void _init() {
	memset(bit, 0, sizeof(bit));
	memset(ans, 0, sizeof(ans));
	memset(tree, 0, sizeof(tree));
	for (int i = 0; i < Maxn * 20; i++) lson[i] = rson[i] = -1;
	memset(root, 0, sizeof(root));
	kc = 0;
	memset(dep, 0, sizeof(dep));
	memset(dp, 0, sizeof(dp));
	for (int i = 0; i < Maxn; i++) {
		for (int j = 0; j < 20; j++) par[i][j] = -1;
	}
}
void Update(int p) {
	if (lson[p] == -1) {
		tree[p] = tree[rson[p]];
		return;
	}
	if (rson[p] == -1) {
		tree[p] = tree[lson[p]];
		return;
	}
	tree[p] = lca(tree[rson[p]], tree[lson[p]]);
}
void modify(int p, int l, int r, int pos, int val) {
	if (l == r) {
		tree[p] = val;
		return;
	}
	int mid = l + r >> 1;
	if (pos <= mid) {
		if (lson[p] == -1) { lson[p] = ++kc; }
		modify(lson[p], l, mid, pos, val);
	} else {
		if (rson[p] == -1) { rson[p] = ++kc; }
		modify(rson[p], mid + 1, r, pos, val);
	}
	Update(p);
}
int query(int p, int l, int r, int lo, int hi) {
	if (p == -1) return -1;
	if (lo <= l && r <= hi) { return tree[p]; }
	int mid = l + r >> 1;
	if (lo <= mid && hi > mid) {
		int A = query(lson[p], l, mid, lo, min(hi, mid));
		int B = query(rson[p], mid + 1, r, max(lo, mid + 1), hi);
		if (A == -1) return B;
		if (B == -1) return A;
		return lca(A, B);
	}
	if (lo <= mid) { return query(lson[p], l, mid, lo, min(hi, mid)); }
	if (hi > mid) { return query(rson[p], mid + 1, r, max(lo, mid + 1), hi); }
}
void Ins(int Dp, int val, int Pos) {
	modify(root[Dp], 0, n, val, Pos);
	//	cout<<"INS"<<" "<<Dp<<' '<<val<<' '<<Pos<<endl;
}
void Add_edge(int u, int p) {
	par[u][0] = p;
	dep[u] = dep[p] + 1;
	for (int i = 1; i < 20; i++) {
		if (par[u][i - 1] == -1) {
			par[u][i] = -1;
		} else {
			par[u][i] = par[par[u][i - 1]][i - 1];
		}
	}
}
void Solve() {
	_init();
	for (int i = 1; i <= n; i++) { root[i] = ++kc; }
	dp[0] = 0;
	Ins(0, 0, 0);
	for (int i = 1; i <= n; i++) {
		int Mx = Qry(a[i]);
		int pa = query(root[Mx], 0, n, 0, a[i]);
		//	cout<<"PAR"<<' '<<Mx<<' '<<i<<' '<<pa<<endl;
		Add_edge(i, pa);
		dp[i] = Mx + 1;
		Add(a[i], dp[i]);
		Ins(dp[i], a[i], i);
	}
	// cout<<lca(4,5)<<endl;
	for (int i = 1; i <= n; i++) {
		//	cout<<i<<' '<<dep[i]-1<<endl;
		ans[i] = dep[i] - 1;
	}
}
int main() {
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) { scanf("%d", &a[i]); }
	Solve();
	for (int i = 1; i <= n; i++) res[i] += ans[i];
	reverse(a + 1, a + 1 + n);
	for (int i = 1; i <= n; i++) { a[i] = n + 1 - a[i]; }
	Solve();
	for (int i = 1; i <= n; i++) res[n + 1 - i] += ans[i];
	for (int i = 1; i <= n; i++) { printf("%d ", res[i]); }
	printf("\n");
	return 0;
}