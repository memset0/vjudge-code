#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef unsigned un;
const int MAXN = 4e5 + 9, mod = 1e9 + 7, inv2 = (mod + 1) >> 1;
int n, q;
struct Segment_Tree {
    struct node {
        ll sum, tag;
    } t[MAXN << 2 | 1];
#define rt t[num]
#define tl t[num << 1]
#define tr t[num << 1 | 1]
    void pushup(un num) { rt.sum = (tl.sum + tr.sum) % mod; }
    void pushdown(un num) {
        if (rt.tag == 1) return;
        tl.sum = tl.sum * rt.tag % mod, tl.tag = tl.tag * rt.tag % mod;
        tr.sum = tr.sum * rt.tag % mod, tr.tag = tr.tag * rt.tag % mod;
        rt.tag = 1;
    }
    void init(un l = 1, un r = n, un num = 1) {
        rt.tag = 1;
        if (l == r) {
            rt.sum = 1;
            return;
        }
        un mid = (l + r) >> 1;
        init(l, mid, num << 1), init(mid + 1, r, num << 1 | 1);
        pushup(num);
    }
    void Mul(un ql, un qr, ll k, un l = 1, un r = n, un num = 1) {
        if (ql > qr) return;
        if (ql <= l && r <= qr) {
            rt.sum = rt.sum * k % mod, rt.tag = rt.tag * k % mod;
            return;
        }
        pushdown(num);
        un mid = (l + r) >> 1;
        if (ql <= mid) Mul(ql, qr, k, l, mid, num << 1);
        if (qr > mid) Mul(ql, qr, k, mid + 1, r, num << 1 | 1);
        pushup(num);
    }
    ll Qsum(un ql, un qr, un l = 1, un r = n, un num = 1) {
        if (ql > qr) return 0;
        if (ql <= l && r <= qr) return rt.sum;
        pushdown(num);
        un mid = (l + r) >> 1;
        ll res = 0;
        if (ql <= mid) res += Qsum(ql, qr, l, mid, num << 1);
        if (qr > mid) res += Qsum(ql, qr, mid + 1, r, num << 1 | 1);
        return res % mod;
    }
} t1, t2;
vector<int> g[MAXN];
int fa[MAXN], sz[MAXN], ms[MAXN], dep[MAXN];
int dfn[MAXN], ed[MAXN], top[MAXN], cur = 0;
void dfs1(int u) {
    sz[u] = 1;
    for (auto v : g[u]) {
        if (v == fa[u]) continue;
        fa[v] = u, dep[v] = dep[u] + 1;
        dfs1(v);
        if (sz[v] > sz[ms[u]]) ms[u] = v;
        sz[u] += sz[v];
    }
}
void dfs2(int u, int now_top) {
    top[u] = now_top, dfn[u] = ++cur;
    if (ms[u]) dfs2(ms[u], now_top);
    for (auto v : g[u])
        if (v != fa[u] && v != ms[u]) dfs2(v, v);
    ed[u] = cur;
}
int LCA(int u, int v) {
    while (top[u] != top[v])
        if (dep[top[u]] >= dep[top[v]])
            u = fa[top[u]];
        else
            v = fa[top[v]];
    return dep[u] > dep[v] ? v : u;
}
void _mul(int l, int r, int k) { t1.Mul(l, r, k), t2.Mul(l, r, k); }
void Mul(int u, int v, int k) {
    int inv = (k == 2 ? inv2 : 2);
    while (top[u] != top[v])
        if (dep[top[u]] >= dep[top[v]])
            _mul(dfn[top[u]], dfn[u], k), u = fa[top[u]];
        else
            _mul(dfn[top[v]], dfn[v], k), v = fa[top[v]];
    int l = dfn[u], r = dfn[v];
    if (l > r) std::swap(l, r);
    _mul(l, r, k);
    t2.Mul(l, l, inv);
}
int main() {
#ifdef popteam
    freopen("C.in", "r", stdin);
#endif
    cin.tie(0)->sync_with_stdio(0);
    cin >> n;
    for (int i = 1; i < n; ++i) {
        int u, v;
        cin >> u >> v;
        g[u].push_back(v), g[v].push_back(u);
    }
    dep[1] = 1, dfs1(1), dfs2(1, 1);
    t1.init(), t2.init();
    cin >> q;
    while (q--) {
        string op;
        int x, y;
        cin >> op >> x >> y;
        if (op == "+")
            Mul(x, y, 2);
        else
            Mul(x, y, inv2);
        ll res = t1.Qsum(1, n) - t2.Qsum(2, n) - 1;
        printf("%lld\n", (res % mod + mod) % mod);
    }
    return 0; // hello
}