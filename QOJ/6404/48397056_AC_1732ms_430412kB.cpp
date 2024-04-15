#include <bits/stdc++.h>
#ifndef popteam
#define endl '\n'
#endif
#define all(x) begin(x), end(x)
using namespace std;
const int N = 2e5 + 9, M = 59;
int n, m, tot, nod, fa[N], bln[N], siz[N], out[M];
bool ok[N];
long long dep[N];
string s;
bitset<M> bit[M], sub[M];
vector<int> leaves;
vector<pair<int, int>> G[N], child[M];
void dfs(int u) {
    siz[u] = 1;
    for (auto [v, w] : G[u])
        if (v != fa[u]) {
            fa[v] = u;
            dep[v] = dep[u] + w;
            dfs(v);
            siz[u] += siz[v];
        }
    if (siz[u] == 1) {
        leaves.push_back(u);
    }
}
struct atom {
    long long min, max;
    void reset() { min = LLONG_MAX, max = LLONG_MIN; }
    bool empty() { return min == LLONG_MAX && max == LLONG_MIN; }
    atom operator+(const atom &rhs) const {
        return {
            std::min(min, rhs.min),
            std::max(max, rhs.max),
        };
    }
} dp[M];
struct segtree {
    atom p[524288];
    void maintain(int u) {
        p[u].min = min(p[u << 1].min, p[u << 1 | 1].min);
        p[u].max = max(p[u << 1].max, p[u << 1 | 1].max);
    }
    void build(int u, int l, int r) {
        p[u].reset();
        if (l == r) return;
        int mid = (l + r) >> 1;
        build(u << 1, l, mid);
        build(u << 1 | 1, mid + 1, r);
    }
    void modify(int u, int k, bool op, int l, int r) {
        // fprintf(stderr, "modify %d %d %d %d %d\n", u, k, op, l, r);
        if (l == r) {
            if (op) {
                p[u].min = p[u].max = dep[k];
            } else {
                p[u].reset();
            }
            return;
        }
        int mid = (l + r) >> 1;
        if (k <= mid) {
            modify(u << 1, k, op, l, mid);
        } else {
            modify(u << 1 | 1, k, op, mid + 1, r);
        }
        maintain(u);
    }
    atom query(int u, int ql, int qr, int l, int r) {
        // fprintf(stderr, "query %d %d %d %d %d\n", u, ql, qr, l, r);
        if (ql == l && qr == r) {
            return p[u];
        }
        int mid = (l + r) >> 1;
        if (qr <= mid) return query(u << 1, ql, qr, l, mid);
        if (ql > mid) return query(u << 1 | 1, ql, qr, mid + 1, r);
        return query(u << 1, ql, mid, l, mid) + query(u << 1 | 1, mid + 1, qr, mid + 1, r);
    }
} seg[M];
int main() {
#ifdef popteam
    freopen("K.in", "r", stdin);
#endif
    cin.tie(0)->sync_with_stdio(0);
    cin >> n >> m >> s;
    for (int i = 1; i <= n; i++) {
        ok[i] = s[i - 1] == '1';
    }
    for (int u, v, w, i = 1; i < n; i++) {
        cin >> u >> v >> w;
        G[u].emplace_back(v, w);
        G[v].emplace_back(u, w);
    }
    dfs(1);
    memset(bln, -1, sizeof(bln));
    for (int i = 0; i < leaves.size(); i++) {
        seg[i].build(1, 1, n);
        int x = leaves[i];
        for (int u = x, lst = -1; u; lst = u, u = fa[u])
            if (bln[u] == -1) {
                bln[u] = i;
                if (ok[u]) {
                    seg[i].modify(1, u, true, 1, n);
                }
            } else {
                out[i] = u;
                child[bln[u]].emplace_back(i, lst);
                break;
            }
    }
    // for (int i = 1; i <= n; i++)
    //     cerr << bln[i] << " \n"[i == n];
    for (int op, x, l, r, i = 1; i <= m; i++) {
        cin >> op;
        if (op == 1) {
            cin >> x;
            ok[x] ^= 1;
            seg[bln[x]].modify(1, x, ok[x], 1, n);
        } else {
            cin >> l >> r;
            for (int i = 0; i < leaves.size(); i++) {
                sub[i].reset();
            }
            for (int i = leaves.size() - 1; i >= 0; i--) {
                dp[i] = seg[i].query(1, l, r, 1, n);
                if (!dp[i].empty()) {
                    sub[i].set(i);
                }
                if (out[i]) {
                    sub[bln[out[i]]] |= sub[i];
                }
                bit[i] = sub[i];
#ifdef popteam
                fprintf(stderr, "%d >> %lld %lld >> ", i, dp[i].min, dp[i].max);
                for (int k = 0; k < leaves.size(); k++)
                    cerr << sub[i][k] << " \n"[k + 1 == leaves.size()];
#endif
            }
            for (int i = 0; i < leaves.size(); i++) {
                for (auto [j, x] : child[i]) {
                    bit[j] |= bit[i];
                }
            }
            bool ok = false;
            long long ans = 0;
            for (int i = 0; i < leaves.size(); i++) {
#ifdef popteam
                fprintf(stderr, "%d >> %lld %lld >> ", i, dp[i].min, dp[i].max);
                for (int k = 0; k < leaves.size(); k++)
                    cerr << bit[i][k] << " \n"[k + 1 == leaves.size()];
#endif
                for (auto [j, x] : child[i]) {
                    if (sub[j].count()) {
                        dp[i] = dp[i] + atom{dep[fa[x]], dep[fa[x]]};
                        if ((bit[i] ^ (bit[i] & sub[j])).count()) {
                            dp[j] = dp[j] + atom{dep[fa[x]], dep[fa[x]]};
                        }
                    }
                }
            }
            for (int i = 0; i < leaves.size(); i++) {
                if (!dp[i].empty()) {
                    ok = true;
                    ans += dp[i].max - dp[i].min;
                }
            }
            cout << (ok ? (ans << 1) : -1) << endl;
        }
    }
}