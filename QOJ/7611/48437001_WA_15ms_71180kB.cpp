#include <bits/stdc++.h>
using namespace std;
const int N = 5e5 + 9, M = 6e5, V = N * 40;
int n, m, nod, a[N], l[N], r[N];
long long ans, out[2][N];
struct oper {
    int x, k;
} q[N];
string op;
int _rt[M << 1 | 1], *rt = _rt + M;
set<int> _st[M << 1 | 1], *st = _st + M;
struct node {
    int lc, rc, cnt;
} p[V];
void maintain(int u) { p[u].cnt = p[u << 1].cnt + p[u << 1 | 1].cnt; }
void update(int &u, int v, int k, int x, int l, int r) {
    u = ++nod;
    if (l == r) {
        p[u].cnt = x;
        return;
    }
    int mid = (l + r) >> 1;
    if (k <= mid) {
        p[u].rc = p[v].rc;
        update(p[u].lc, p[v].lc, k, x, l, mid);
    } else {
        p[u].lc = p[v].lc;
        update(p[u].rc, p[v].rc, k, x, mid + 1, r);
    }
}
void solve(long long out[N]) {
    for (int i = 1; i <= n; i++) {
        st[a[i]].insert(i);
    }
    for (int i = M; i >= -M; i--) {
        rt[i] = i == M ? 0 : rt[i + 1];
        for (int x : st[i]) {
            update(rt[i], rt[i], x, 1, 1, n);
        }
    }
}
void reset() {
    ans = 0;
    memset(_rt, 0, sizeof(_rt));
    for (int i = -M; i <= M; i++)
        st[i].clear();
}
int main() {
#ifdef popteam
    freopen("F.in", "r", stdin);
#endif
    cin.tie(0)->sync_with_stdio(0);
    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    for (int i = 1; i <= m; i++) {
        cin >> op >> q[i].k;
        q[i].x = op[0] == '+' ? 1 : -1;
    }
    solve(out[0]);
    for (int i = 1; i <= n; i++) {
        a[i] *= -1;
    }
    for (int i = 1; i <= m; i++) {
        q[i].x *= -1;
    }
    reset();
    solve(out[1]);
}