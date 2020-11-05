// =================================
//   author: memset0
//   date: 2019.01.03 12:08:20
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

const int N = 5e5 + 10;
int n, m, u, v, t, rt, cnt, dis, mid, pos, left, right;
int fa[N], id[N], top[N], son[N], siz[N], wid[N], dep[N];
int tot = 2, hed[N], nxt[N << 1], to[N << 1];

inline void add_edge(int u, int v) {
    nxt[tot] = hed[u], to[tot] = v, hed[u] = tot++;
    nxt[tot] = hed[v], to[tot] = u, hed[v] = tot++;
}

void dfs1(int u) {
    siz[u] = 1;
    for (int i = hed[u], v = to[i]; i; i = nxt[i], v = to[i])
        if (v != fa[u]) {
            fa[v] = u, dep[v] = dep[u] + 1, dfs1(v), siz[u] += siz[v];
            if (siz[v] > siz[son[u]]) son[u] = v;
        }
}

void dfs2(int u, int toppoint) {
    top[u] = toppoint, id[u] = ++pos, wid[id[u]] = u;
    if (siz[u] == 1) return;
    dfs2(son[u], toppoint);
    for (int i = hed[u], v = to[i]; i; i = nxt[i], v = to[i])
        if (v != fa[u] && v != son[u]) dfs2(v, v);
}

struct node {
    int l, r, mid;
    int sum, tag;
} p[N << 2];

inline void pushup(int u, int x) {
    p[u].tag = x, p[u].sum = x ? (p[u].r - p[u].l + 1) : 0;
}

inline void pushdown(int u) {
    if (p[u].tag == -1 || p[u].l == p[u].r) return;
    pushup(u << 1, p[u].tag), pushup(u << 1 | 1, p[u].tag), p[u].tag = -1;
}

void build(int u, int l, int r) {
    p[u].l = l, p[u].r = r, p[u].mid = (l + r) >> 1, p[u].tag = -1;
    if (l == r) return;
    build(u << 1, l, p[u].mid);
    build(u << 1 | 1, p[u].mid + 1, r);
}

void modify(int u, int l, int r, int x) {
    if (l > r) return;
    pushdown(u);
    // printf("modify %d[%d %d] %d %d %d %d\n", u, p[u].l, p[u].r, l, r, x, p[u].sum);
    if (p[u].l == l && p[u].r == r) return pushup(u, x);
    if (r <= p[u].mid) modify(u << 1, l, r, x);
    else if (l > p[u].mid) modify(u << 1 | 1, l, r, x);
    else modify(u << 1, l, p[u].mid, x), modify(u << 1 | 1, p[u].mid + 1, r, x);
    p[u].sum = p[u << 1].sum + p[u << 1 | 1].sum;
}

int lca(int u, int v) {
    while (top[u] != top[v]) {
        if (dep[top[u]] > dep[top[v]]) std::swap(u, v);
        v = fa[top[v]];
    }
    return dep[u] < dep[v] ? u : v;
}

int jump(int u, int v) {
    while (dep[u] - dep[top[u]] + 1 <= v) {
        v -= dep[u] - dep[top[u]] + 1;
        u = fa[top[u]];
    }
    return wid[id[u] - v];
}

void main() {
    read(n), read(m);
    for (int i = 1; i < n; i++) read(u), read(v), add_edge(u, v);
    dep[1] = 1, dfs1(1), dfs2(1, 1), build(1, 1, n);
    for (int i = 1; i <= m; i++) {
        read(cnt), read(rt), modify(1, 1, n, 1);
        for (int i = 2; i <= cnt; i++) {
            read(u), t = lca(rt, u);
            left = dep[rt] - dep[t] + 1, right = dep[u] - dep[t] + 1;
            dis = left + right - 1, mid = dis >> 1;
            // printf("left = %d right = %d dis = %d mid = %d\n", left, right, dis, mid);
            if (mid < right) {
                v = jump(u, mid - 1);
                modify(1, id[v], id[v] + siz[v] - 1, 0);
            } else {
                v = jump(rt, dis - mid - 1);
                modify(1, 1, id[v] - 1, 0);
                modify(1, id[v] + siz[v], n, 0);
            }
        }
        print(p[1].sum, '\n');
    }
}

} signed main() { return ringo::main(), 0; }
