#include <bits/stdc++.h>
#define pk push_back
#define mk make_pair
using namespace std;
typedef long long LL;
typedef pair<int, int> pi;
const int N = 3e5 + 5, M = 20;
int n, m, q, R;
namespace p2 {
int tot = 1, to[N << 1], head[N], nxt[N << 1], dfn[N], low[N], idx;
int cnt, cut[N << 1], bel[N];
void add(int x, int y) { to[++tot] = y, nxt[tot] = head[x], head[x] = tot; }
void tarjan(int x, int pre) {
	low[x] = dfn[x] = ++idx;
	for (int i = head[x]; i; i = nxt[i])
		if (!dfn[to[i]]) {
			tarjan(to[i], i), low[x] = min(low[x], low[to[i]]);
			if (low[to[i]] > dfn[x]) { cut[i] = cut[i ^ 1] = 1; }
		} else if (i != (pre ^ 1))
			low[x] = min(low[x], dfn[to[i]]);
}
void dfs(int x, int col) {
	bel[x] = col;
	for (int i = head[x]; i; i = nxt[i])
		if (!cut[i] && !bel[to[i]]) dfs(to[i], col);
}
void build(vector<int>& v) {
	for (auto x : v)
		if (!dfn[x]) tarjan(x, 0);
	for (auto x : v)
		if (!bel[x]) dfs(x, ++cnt);
}
}  // namespace p2
namespace p1 {
int tot = 1, to[N << 1], head[N], nxt[N << 1], dfn[N], low[N], idx;
int cnt, cut[N << 1], bel[N];
void add(int x, int y) { to[++tot] = y, nxt[tot] = head[x], head[x] = tot; }
void tarjan(int x, int pre) {
	low[x] = dfn[x] = ++idx;

	for (int i = head[x]; i; i = nxt[i])
		if (!dfn[to[i]]) {
			tarjan(to[i], i), low[x] = min(low[x], low[to[i]]);
			if (low[to[i]] > dfn[x]) cut[i] = cut[i ^ 1] = 1;
		} else if (i != (pre ^ 1))
			low[x] = min(low[x], dfn[to[i]]);
}
void dfs(int x, int col) {
	bel[x] = col;
	for (int i = head[x]; i; i = nxt[i])
		if (!cut[i] && !bel[to[i]]) dfs(to[i], col);
}
void build() {
	for (int i = 1; i <= n; ++i)
		if (!dfn[i]) tarjan(i, 0);
	for (int i = 1; i <= n; ++i)
		if (!bel[i]) dfs(i, ++cnt);
}
int f[N][M], dep[N], fm[N], num, st[N], out[N];
void dfs2(int x, int pre) {
	fm[x] = num;
	dep[x] = dep[pre] + 1, f[x][0] = pre, dfn[x] = ++idx;
	for (int i = 1;; ++i)
		if (f[x][i - 1])
			f[x][i] = f[f[x][i - 1]][i - 1];
		else
			break;
	for (int i = head[x]; i; i = nxt[i])
		if (to[i] != pre) dfs2(to[i], x);
	out[x] = idx;
}
int lca(int x, int y) {
	if (dep[x] < dep[y]) swap(x, y);
	for (int i = M - 1; i >= 0; --i)
		if (dep[f[x][i]] >= dep[y]) x = f[x][i];
	if (x == y) return x;
	for (int i = M - 1; i >= 0; --i)
		if (f[x][i] ^ f[y][i]) x = f[x][i], y = f[y][i];
	return f[x][0];
}
int rotate(int element) {
	element = (element + R) % n;
	if (element == 0) { element = n; }
	return element;
}
bool cmp(int x, int y) { return fm[x] < fm[y]; }
bool cmp2(int x, int y) { return dfn[x] < dfn[y]; }
void reset(vector<int>& del) {
	for (int i = 2; i <= p2::tot; ++i) p2::cut[i] = 0;
	p2::tot = 1;
	p2::idx = 0;
	p2::cnt = 0;
	for (auto x : del) p2::dfn[x] = 0, p2::bel[x] = 0, p2::head[x] = 0;
}
bool solve() {
	int ni, mi;	 // cout<<"qwq"<<endl;
	cin >> ni >> mi;
	vector<int> v, v1;
	for (int i = 1, x; i <= ni; ++i) {
		cin >> x;
		x = rotate(x);
		//			cout<<bel[x]<<endl;
		v.pk(bel[x]);
		v1.pk(bel[x]);
	}
	for (int i = 1, x, y; i <= mi; ++i) {
		cin >> x >> y;
		x = rotate(x), y = rotate(y);
		x = bel[x], y = bel[y];
		if (x == y) continue;
		//			cout<<x<<' '<<y<<endl;
		v.pk(x);
		v.pk(y);
		p2::add(x, y), p2::add(y, x);
	}
	//		getchar();
	sort(v.begin(), v.end());
	v.erase(unique(v.begin(), v.end()), v.end());
	sort(v.begin(), v.end(), cmp);
	vector<int> del = v;
	for (int i = 0, j; i < v.size(); i = j + 1) {
		j = i - 1;
		vector<int> t;
		while (j + 1 < v.size() && fm[v[j + 1]] == fm[v[i]]) t.pk(v[++j]);

		sort(t.begin(), t.end(), cmp2);
		int sz = t.size();
		for (int k = 0; k < sz - 1; ++k) t.pk(lca(t[k], t[k + 1]));
		sort(t.begin(), t.end(), cmp2);
		t.erase(unique(t.begin(), t.end()), t.end());
		int tp = 0;
		for (int k = 0; k < t.size(); ++k) {
			while (tp && dfn[t[k]] > out[st[tp]]) --tp;
			if (tp) p2::add(t[k], st[tp]), p2::add(st[tp], t[k]), del.pk(t[k]), del.pk(st[tp]);
			st[++tp] = t[k];
		}
	}
	//		for(int i=0;i<v1.size();++i) cout<<p2::dfn[v1[i]]<<' ';cout<<endl;
	p2::build(v1);
	int o = p2::bel[v1[0]];
	for (int i = 1; i < v1.size(); ++i) {
		if (p2::bel[v1[i]] != o) { return reset(del), false; }
	}
	return reset(del), true;
}
void init() {
	cin >> n >> m >> q;
	for (int i = 1; i <= m; ++i) {
		int x, y;
		cin >> x >> y;
		add(x, y), add(y, x);
	}
	build();
	set<pi> st;
	for (int i = 2; i <= tot; i += 2) {
		int x = bel[to[i]], y = bel[to[i ^ 1]];
		if (x == y) continue;
		if (x > y) swap(x, y);
		st.insert(mk(x, y));
	}
	tot = 0;
	memset(head, 0, sizeof head);
	for (auto x : st) add(x.first, x.second), add(x.second, x.first);
	idx = 0;
	for (int i = 1; i <= cnt; ++i)
		if (!dep[i]) ++num, dfs2(i, 0);
}
}  // namespace p1
int main() {
	ios::sync_with_stdio(false);
	p1::init();
	for (int i = 1; i <= q; ++i)
		if (p1::solve())
			cout << "YES" << endl, R = (R + i) % n;
		else
			cout << "NO" << endl;
	return 0;
}