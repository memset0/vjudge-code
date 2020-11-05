#include <bits/stdc++.h>

inline long long read() {
    char c; long long x; for (c = getchar(); !isdigit(c); c = getchar());
    for (x = 0; isdigit(c); c = getchar()) { x = x * 10 + c - '0'; } return x;
}

const int N = 2e5 + 10, V = 4e5 + 10;
const unsigned long long lim = 18e18;

int n, m, q, tot, st[N], ed[N];
std::vector<std::pair<int, int>> vec;

struct Line {
    long long a, b;

    inline unsigned long long y(unsigned long long x) {
        if (a == 0) { return lim; }
        x = (x - a);
        return x * x * x * x + b;
    }
} s[N];

struct SegmentTree {
    int f[N];

    void build(int u, int l, int r) {
        f[u] = 0;
        if (l + 1 >= r) { return; }
        int mid = l + r >> 1, ls = u << 1, rs = ls | 1;
        build(ls, l, mid); build(rs, mid, r);
    }
    void modify(int u, int l, int r, int pl, int pr, int i) {
        if (pl >= pr) { return; }
        int mid = l + r >> 1, ls = u << 1, rs = ls | 1;
        if (l == pl && r == pr) {
            int j = f[u];
            if (j == 0) { vec.push_back({u, f[u]}); f[u] = i; return; }
            unsigned long long il = s[i].y(l), ir = s[i].y(r), jl = s[j].y(l), jr = s[j].y(r);
            if (il > jl && ir > jr) { return; }
            if (il < jl && ir < jr) { vec.push_back({u, f[u]}); f[u] = i; return; }
            unsigned long long im = s[i].y(mid), jm = s[j].y(mid);
            if (im > jm) { std::swap(i, j); std::swap(il, jl); std::swap(ir, jr); }
            vec.push_back({u, f[u]}); f[u] = i;
            if (il > jl) { modify(ls, l, mid, pl, mid, j); }
            if (ir > jr) { modify(rs, mid, r, mid, pr, j); }
        } else if (pr <= mid) {
            modify(ls, l, mid, pl, pr, i);
        } else if (pl > mid) {
            modify(rs, mid, r, pl, pr, i);
        } else {
            modify(ls, l, mid, pl, mid, i);
            modify(rs, mid, r, mid, pr, i);
        }
    }
    unsigned long long query(int u, int l, int r, int p) {
        if (l + 1 >= r) { return s[f[u]].y(p); }
        int mid = l + r >> 1, ls = u << 1, rs = ls | 1;
        if (p < mid) {
            return std::min(query(ls, l, mid, p), s[f[u]].y(p));
        } else {
            return std::min(query(rs, mid, r, p), s[f[u]].y(p));
        }
    }
} smt;

struct TimeTree {
    int qry[V];
    std::vector<int> e[V];

    void build(int u, int l, int r) {
        qry[u] = 0; e[u].clear();
        if (l + 1 >= r) { return; }
        int mid = l + r >> 1, ls = u << 1, rs = ls | 1;
        build(ls, l, mid); build(rs, mid, r);
    }
    void insert(int u, int l, int r, int pl, int pr, int i) {
        if (pl >= pr) { return; }
        if (l == pl && r == pr) { e[u].push_back(i); return; }
        int mid = l + r >> 1, ls = u << 1, rs = ls | 1;
        if (pr <= mid) {
            insert(ls, l, mid, pl, pr, i);
        } else if (pl > mid) {
            insert(rs, mid, r, pl, pr, i);
        } else {
            insert(ls, l, mid, pl, mid, i);
            insert(rs, mid, r, mid, pr, i);
        }
    }
    void query(int u, int l, int r, int p, int x) {
        if (l + 1 >= r) { qry[u] = x; return; }
        int mid = l + r >> 1, ls = u << 1, rs = ls | 1;
        if (p < mid) {
            query(ls, l, mid, p, x);
        } else {
            query(rs, mid, r, p, x);
        }
    }
    void solve(int u, int l, int r) {
        int vol = vec.size();
        for (auto i : e[u]) {
            smt.modify(1, 0, n, 0, s[i].a, i);
            smt.modify(1, 0, n, s[i].a, n, i);
        }
        if (l + 1 >= r) {
            if (qry[u] > 0) {
                unsigned long long ans = smt.query(1, 0, n, qry[u]);
                if (ans == lim) {
                    printf("-1\n");
                } else {
                    printf("%llu\n", ans);
                }
            }
        } else {
            int mid = l + r >> 1, ls = u << 1, rs = ls | 1;
            solve(ls, l, mid); solve(rs, mid, r);
        }
        for (; vec.size() != vol; vec.pop_back()) {
            smt.f[vec.back().first] = vec.back().second;
        }
    }
} tr;

int main() {
    for (int T = read(); T; T--) {
        n = 50001; m = read(); q = read();
        for (int i = 1; i <= tot; i++) {
            st[i] = ed[i] = 0;
        }
        tot = 0;
        smt.build(1, 0, n);
        for (int i = 1; i <= m; i++) {
            long long a = read(), b = read();
            s[++tot] = (Line) {a, b};
            st[tot] = 0;
        }
        tr.build(1, 0, q + 1);
        for (int i = 1; i <= q; i++) {
            int opt = read();
            if (opt == 1) {
                long long a = read(), b = read();
                s[++tot] = (Line) {a, b};
                st[tot] = i;
            } else if (opt == 2) {
                int u = read();
                ed[u] = i;
            } else {
                int x = read();
                tr.query(1, 0, q + 1, i, x);
            }
        }
        for (int i = 1; i <= tot; i++) {
            if (ed[i] == 0) { ed[i] = q + 1; }
            tr.insert(1, 0, q + 1, st[i], ed[i], i);
        }
        tr.solve(1, 0, q + 1);
        vec.clear();
    }
    return 0;
}