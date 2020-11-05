// luogu-judger-enable-o2
// =================================
//   author: memset0
//   date: 2019.01.13 17:39:37
//   website: https://memset0.cn/
// =================================
#include <bits/stdc++.h>
#define ll long long
namespace ringo {
template <class T> inline void read(T &x) {
    x = 0; register char c = getchar(); register bool f = 0;
    while (!isdigit(c)) f ^= c == '-', c = getchar();
    while (isdigit(c)) x = x * 10 + c - '0', c = getchar();
    if (f) x = -x;
}
template <class T> inline void print(T x) {
    if (x < 0) putchar('-'), x = -x;
    if (x > 9) print(x / 10);
    putchar('0' + x % 10);
}
template <class T> inline void print(T x, char c) { print(x), putchar(c); }

const int N = 1e5 + 10, M = N * 60;
int n, m, pos, n_val, n_cst;
int ans[N], val[N], cst[N], rt[N], lc[M], rc[M];
ll cnt[M], sum[M];

struct info { int val, cst, lim; } a[N];
struct query { ll max, lim; } b[N];
inline bool cmp(const info &a, const info &b) { return a.val > b.val; }

void build(int &u, int l, int r) {
    u = ++pos;
    if (l == r) return;
    int mid = (l + r) >> 1;
    build(lc[u], l, mid);
    build(rc[u], mid + 1, r);
}

void modify(int &u, int v, int k, int w, int l, int r) {
    u = ++pos, lc[u] = lc[v], rc[u] = rc[v], cnt[u] = cnt[v], sum[u] = sum[v];
    if (l == r) { cnt[u] += w, sum[u] += (ll)w * cst[l]; return; }
    int mid = (l + r) >> 1;
    if (k <= mid) modify(lc[u], lc[v], k, w, l, mid);
    else modify(rc[u], rc[v], k, w, mid + 1, r);
    sum[u] = sum[lc[u]] + sum[rc[u]];
    cnt[u] = cnt[lc[u]] + cnt[rc[u]];
}

bool query(int u, ll c, ll s, int l, int r) {
    // printf("query %d %d %d %d %d : %d %d\n", u, c, s, l, r, cnt[u], sum[u]);
    if (c > cnt[u]) return false;
    if (s > sum[u]) return true;
    if (l == r) return (ll)c * cst[l] <= s;
    int mid = (l + r) >> 1;
    if (c <= cnt[lc[u]]) return query(lc[u], c, s, l, mid);
    return query(rc[u], c - cnt[lc[u]], s - sum[lc[u]], mid + 1, r);
}

bool check(int i, int mid) {
    bool answer = query(rt[mid], b[i].lim, b[i].max, 1, n_cst);
    // printf("check %d %d => %d : %d %d : %d %lld\n", i, mid, answer, b[i].lim, b[i].max, cnt[rt[mid]], sum[rt[mid]]);
    return answer;
}

void main() {
    read(n), read(m);
    for (int i = 1; i <= n; i++) read(a[i].val), read(a[i].cst), read(a[i].lim);
    for (int i = 1; i <= m; i++) read(b[i].max), read(b[i].lim);
    for (int i = 1; i <= n; i++) val[i] = a[i].val, cst[i] = a[i].cst;
    // std::sort(val + 1, val + n + 1), n_val = std::unique(val + 1, val + n + 1) - val - 1;
    std::sort(cst + 1, cst + n + 1), n_cst = std::unique(cst + 1, cst + n + 1) - cst - 1;
    for (int i = 1; i <= n; i++) {
        // a[i].val = std::lower_bound(val + 1, val + n_val + 1, a[i].val) - val;
        a[i].cst = std::lower_bound(cst + 1, cst + n_cst + 1, a[i].cst) - cst;
    }
    std::sort(a + 1, a + n + 1, cmp);
    build(rt[0], 1, n_cst);
    for (int i = 1; i <= n; i++)
        modify(rt[i], rt[i - 1], a[i].cst, a[i].lim, 1, n_cst);
    for (int i = 1; i <= m; i++) {
        ans[i] = -1;
        for (int l = 1, r = n, mid; l <= r; )
            if (check(i, mid = (l + r) >> 1)) ans[i] = mid, r = mid - 1;
            else l = mid + 1;
        print(~ans[i] ? a[ans[i]].val : -1, '\n');
    }
}

} signed main() { return ringo::main(), 0; }
