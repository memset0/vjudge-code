#include <bits/stdc++.h>
#ifndef popteam
#define endl '\n'
#endif
#define all(x) begin(x), end(x)
using namespace std;
const int N = 1e6 + 9;
int n, m, a[N], p[N], l[N], r[N];
struct section {
    int l, r;
    bool include(const section &rhs) const { return l <= rhs.l && rhs.r <= r; }
    bool operator<(const section &rhs) const {
        if (r == rhs.r) return l > rhs.l;
        return r < rhs.r;
    }
} q[N];
struct segment {
    int l, r, mid;
    int max, tag;
} e[N << 2];
void maintain(int u) { e[u].max = max(e[u << 1].max, e[u << 1 | 1].max); }
void pushup(int u, int x) {
    e[u].max += x;
    e[u].tag += x;
}
void pushdown(int u) {
    if (e[u].tag) {
        pushup(u << 1, e[u].tag);
        pushup(u << 1 | 1, e[u].tag);
        e[u].tag = 0;
    }
}
void build(int u, int l, int r) {
    e[u].l = l, e[u].r = r, e[u].mid = (l + r) >> 1;
    if (l == r) return;
    build(u << 1, l, e[u].mid);
    build(u << 1 | 1, e[u].mid + 1, r);
}
void modify(int u, int l, int r) {
    if (e[u].l == l && e[u].r == r) return pushup(u, 1);
    pushdown(u);
    if (r <= e[u].mid) {
        modify(u << 1, l, r);
    } else if (l > e[u].mid) {
        modify(u << 1 | 1, l, r);
    } else {
        modify(u << 1, l, e[u].mid);
        modify(u << 1 | 1, e[u].mid + 1, r);
    }
    maintain(u);
}
int query(int u, int l, int r) {
    if (e[u].l == l && e[u].r == r) return e[u].max;
    pushdown(u);
    if (r <= e[u].mid) return query(u << 1, l, r);
    if (l > e[u].mid) return query(u << 1 | 1, l, r);
    return max(query(u << 1, l, e[u].mid), query(u << 1 | 1, e[u].mid + 1, r));
}
int main() {
#ifdef popteam
    freopen("D.in", "r", stdin);
#endif
    cin.tie(0)->sync_with_stdio(0);
    cin >> n;
    vector<int> tmp;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        tmp.push_back(a[i]);
    }
    sort(all(tmp));
    for (int i = 1; i <= n; i++) {
        int h = lower_bound(all(tmp), a[i]) - tmp.begin();
        // fprintf(stderr, "a[%d] -> %d -> %d\n", i, a[i], h);
        p[n - h] = i;
    }
    cin >> m;
    for (int i = 1; i <= m; i++) {
        cin >> q[i].l >> q[i].r;
    }
    sort(q + 1, q + m + 1);
    vector<section> stk;
    for (int i = 1; i <= m; i++) {
        while (stk.size() && q[i].include(stk.back()))
            stk.pop_back();
        stk.push_back(q[i]);
    }
    m = stk.size();
    for (int i = 1; i <= m; i++) {
        l[i] = stk[i - 1].l;
        r[i] = stk[i - 1].r;
        // fprintf(stderr, "> l=%d r=%d\n", l[i], r[i]);
    }
    build(1, 1, m);
    long long ans = -1;
    for (int i = 1; i <= n; i++) {
        int k = p[i];
        int ql = lower_bound(r + 1, r + m + 1, k) - r;
        int qr = upper_bound(l + 1, l + m + 1, k) - l - 1;
        if (ql <= qr) {
            // fprintf(stderr, "i=%d k=%d l=%d r=%d :: %d*%d\n", i, k, ql, qr, a[k], query(1, ql, qr));
            ans = max(ans, (long long)a[k] * query(1, ql, qr));
            modify(1, ql, qr);
        }
    }
    cout << ans << endl;
}