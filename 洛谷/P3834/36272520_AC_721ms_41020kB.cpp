// luogu-judger-enable-o2
// luogu-judger-enable-o2
#include <bits/stdc++.h>
#define il inline
#define rg register
#define ll long long
#define getc getchar
#define putc putchar
#define rep(i, l, r) for (int i = l; i <= r; ++i)
namespace ringo {

template < class T > il void read(T &x) {
    x = 0; rg char c = getc(); rg bool f = 0;
    while (!isdigit(c)) f ^= c == '-', c = getc();
    while (isdigit(c)) x = x * 10 + c - '0', c = getc();
    if (f) x = -x;
}

template < class T > il void print(T x) {
    if (x < 0) putc('-'), x = -x;
    if (x > 9) print(x / 10);
    putc('0' + x % 10);
}

const int maxn = 200010, maxm = maxn * 20;

int n, m, l, r, k, tn, pos;
int a[maxn], b[maxn], rt[maxn];
int lc[maxm], rc[maxm], siz[maxm];

void build(int &u, int l, int r) {
    u = ++pos;
    if (l == r) return;
    int mid = (l + r) >> 1;
    build(lc[u], l, mid);
    build(rc[u], mid + 1, r);
}

void insert(int &u, int v, int k, int l, int r) {
    u = ++pos, siz[u] = siz[v] + 1, lc[u] = lc[v], rc[u] = rc[v];
    if (l == r) return;
    int mid = (l + r) >> 1;
    if (k <= mid) insert(lc[u], lc[v], k, l, mid);
    else insert(rc[u], rc[v], k, mid + 1, r);
}

int query(int u, int v, int k, int l, int r) {
    // printf("query %d %d %d : %d %d : %d %d\n", u, v, k, l, r, siz[u], siz[v]);
    if (l == r) return b[l];
    int sum = siz[lc[u]] - siz[lc[v]], mid = (l + r) >> 1;
    if (k <= sum) return query(lc[u], lc[v], k, l, mid);
    return query(rc[u], rc[v], k - sum, mid + 1, r);
}

void main() {
    read(n), read(m);
    rep(i, 1, n) read(a[i]), b[i] = a[i];
    std::sort(b + 1, b + n + 1);
    tn = std::unique(b + 1, b + n + 1) - b - 1;
    rep(i, 1, n) a[i] = std::lower_bound(b + 1, b + tn + 1, a[i]) - b;
    build(rt[0], 1, tn);
    rep(i, 1, n) insert(rt[i], rt[i - 1], a[i], 1, tn);
    // rep(i, 0, n) print(siz[rt[i]]), putc(' '); putc('\n');
    for (int i = 1; i <= m; i++) {
        read(l), read(r), read(k);
        print(query(rt[r], rt[l - 1], k, 1, tn)), putc('\n');
    }
}

} int main() { return ringo::main(), 0; }