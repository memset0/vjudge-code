// luogu-judger-enable-o2
// =================================
//   author: memset0
//   date: 2019.04.12 19:16:07
//   website: https://memset0.cn/
// =================================
#include <bits/stdc++.h>
#define ll long long
#define debug(...) ((void)0)
#ifndef debug
#define debug(...) fprintf(stderr,__VA_ARGS__)
#endif
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
template <class T> inline void print(const std::string &s, T a, int l, int r) {
    std::cerr << s << " ";
    for (int i = l; i <= r; i++) std::cerr << a[i] << " \n"[i == r];
}

const int N = 3e4 + 10, M = 128, mod = 1e4 + 7;
int n, m, lim, val[N], son[N], fa[N], siz[N], inv[mod];
int tot = 2, hed[N], nxt[N << 1], to[N << 1];

inline int half(int x) { return x & 1 ? (x + mod) >> 1 : x >> 1; }
inline int mul(int a, int b) { return a * b - a * b / mod * mod; }
inline int dec(int a, int b) { a -= b; return a < 0 ? a + mod : a; }
inline int inc(int a, int b) { a += b; return a >= mod ? a - mod : a; }

struct zint {
    int x, z;
    inline zint() {}
    inline zint(int _x, int _z) { x = _x, z = _z; }
    inline zint(int k) { k % mod ? (x = k, z = 0) : (x = 1, z = 1); }
    inline operator int () const { return z ? 0 : x; }
    inline zint operator * (const zint &other) const { return (zint){mul(x, other.x), z + other.z}; }
    inline zint operator / (const zint &other) const { return (zint){mul(x, inv[other.x]), z + other.z}; }
    inline zint operator * (int other) const { return other ? (zint){mul(x, other), z} : (zint){x, z + 1}; }
    inline zint operator / (int other) const { return other ? (zint){mul(x, inv[other]), z} : (zint){x, z - 1}; }
};

struct poly {
    int a[M];
    inline int& operator [] (int i) { return a[i]; }
    inline void fwt() {
        for (register int len = 1; len < lim; len <<= 1)
            for (register int i = 0; i < lim; i += (len << 1))
                for (register int j = 0; j < len; j++) {
                    int x = a[i + j], y = a[i + j + len];
                    a[i + j] = inc(x, y), a[i + j + len] = dec(x, y);
                }
    }
    inline void ifwt() {
        for (register int len = 1; len < lim; len <<= 1)
            for (register int i = 0; i < lim; i += (len << 1))
                for (register int j = 0; j < len; j++) {
                    int x = a[i + j], y = a[i + j + len];
                    a[i + j] = half(inc(x, y)), a[i + j + len] = half(dec(x, y));
                }
    }
} tf, tg, ans, one, tmp, f[N], g[N], lg[N], base[M];
inline poly operator + (const poly &a, const poly &b) { poly c; for (int i = 0; i < lim; i++) c.a[i] = inc(a.a[i], b.a[i]); return c; }
inline poly operator - (const poly &a, const poly &b) { poly c; for (int i = 0; i < lim; i++) c.a[i] = dec(a.a[i], b.a[i]); return c; }
inline poly operator * (const poly &a, const poly &b) { poly c; for (int i = 0; i < lim; i++) c.a[i] = mul(a.a[i], b.a[i]); return c; }

struct zpoly {
    zint a[M];
    inline zint& operator [] (int i) { return a[i]; }
    inline operator poly() const { poly r; for (int i = 0; i < lim; i++) r.a[i] = a[i]; return r; }
    inline void operator *= (const poly &other) { for (int i = 0; i < lim; i++) a[i] = a[i] * other.a[i]; }
    inline void operator /= (const poly &other) { for (int i = 0; i < lim; i++) a[i] = a[i] * other.a[i]; }
} lf[N];
inline zpoly operator * (const zpoly &a, const poly &b) { zpoly c; for (int i = 0; i < lim; i++) c[i] = a.a[i] * b.a[i]; return c; }
inline zpoly operator / (const zpoly &a, const poly &b) { zpoly c; for (int i = 0; i < lim; i++) c[i] = a.a[i] / b.a[i]; return c; }

struct matrix {
    poly a, b, c, d;
    inline void load(const zpoly &lf, const poly &lg, int val) {
        a = b = c = base[val] * (poly)lf, d = a + lg;
    }
    inline void dump(poly &f, poly &g) const {
        f = c, g = d;
    }
// a 0 c
// b 1 d
// 0 0 1
} F[N], G[N];
inline matrix operator * (const matrix &a, const matrix &b) {
    return (matrix){a.a * b.a, b.b + a.b * b.a, a.c + a.a * b.c, a.d + b.d + a.b * b.c};
}

namespace bst {
    int rt, top, fa[N], ch[N][2], stk[N];
    inline void maintain(int x) {
        F[x] = G[x];
        if (ch[x][0]) F[x] = F[ch[x][0]] * F[x];
        if (ch[x][1]) F[x] = F[x] * F[ch[x][1]];
    }
    int sbuild(int l, int r) {
        int sum = 0, now = 0;
        for (int i = l; i <= r; i++) sum += siz[stk[i]] - siz[son[stk[i]]];
        for (int i = l; i <= r; i++) {
            now += siz[stk[i]] - siz[son[stk[i]]];
            if ((now << 1) >= sum) {
                fa[ch[stk[i]][0] = sbuild(l, i - 1)] = stk[i];
                fa[ch[stk[i]][1] = sbuild(i + 1, r)] = stk[i];
                return maintain(stk[i]), stk[i];
            }
        }
        return 0;
    }
    int build(int x) {
        for (int u = x; u; u = son[u])
            for (int i = hed[u], v; v = to[i], i; i = nxt[i])
                if (v != ringo::fa[u] && v != son[u])
                    fa[build(v)] = u;
        top = 0; for (int u = x; u; u = son[u]) stk[++top] = u;
        return sbuild(1, top);
    }
    void modify(int k) {
        // int cnt = 0;
        for (int x = k; x; x = fa[x])
            if (ch[fa[x]][0] != x && ch[fa[x]][1] != x && fa[x]) {
                F[x].dump(tf, tg);
                lf[fa[x]] = lf[fa[x]] / (tf + one);
                lg[fa[x]] = lg[fa[x]] - tg;
                G[x].load(lf[x], lg[x], val[x]), maintain(x);
                F[x].dump(tf, tg);
                lf[fa[x]] = lf[fa[x]] * (tf + one);
                lg[fa[x]] = lg[fa[x]] + tg;
            } else {
                G[x].load(lf[x], lg[x], val[x]), maintain(x);
            }
        // std::cerr << cnt << std::endl;
    }
}

void dp(int u) {
    // printf("DP %d\n", u);
    f[u] = base[val[u]];
    for (int i = 0; i < lim; i++) lf[u][i] = 1;
    for (int i = hed[u], v; v = to[i], i; i = nxt[i])
        if (v != fa[u]) {
            dp(v);
            tmp = f[v] + one;
            f[u] = f[u] * tmp;
            g[u] = g[u] + g[v];
            if (v != son[u]) {
                lf[u] = lf[u] * tmp;
                lg[u] = lg[u] + g[v];
            }
        }
    g[u] = f[u] + g[u];
}

void dfs(int u) {
    siz[u] = 1;
    for (int i = hed[u], v; v = to[i], i; i = nxt[i])
        if (v != fa[u]) {
            fa[v] = u, dfs(v), siz[u] += siz[v];
            if (siz[v] > siz[son[u]]) son[u] = v;
        }
}

void main() {
    // printf("%d %d : %d %d\n", zint(1).x, zint(1).z, 1 % mod ? 1 : 1, 1 % mod ? 0 : 1);
    read(n), read(lim);
    for (int i = 1; i <= n; i++) read(val[i]);
    inv[0] = inv[1] = 1;
    for (int i = 0; i < lim; i++) one[i] = base[i][i] = 1, base[i].fwt();
    for (int i = 2; i < mod; i++) inv[i] = mul(mod - mod / i, inv[mod % i]);
    for (int i = 1, u, v; i < n; i++) {
        read(u), read(v);
        nxt[tot] = hed[u], to[tot] = v, hed[u] = tot++;
        nxt[tot] = hed[v], to[tot] = u, hed[v] = tot++;
    }
    dfs(1);
    dp(1);
    for (int i = 1; i <= n; i++) G[i].load(lf[i], lg[i], val[i]);
    bst::rt = bst::build(1);
    ans = g[1], ans.ifwt();
    read(m);
    for (int i = 1, k, v, opt, lazy = 1; i <= m; i++) {
        while (opt = getchar(), opt != 'Q' && opt != 'C');
        if (opt == 'Q') {
            read(k);
            if (!lazy) lazy = 1, F[bst::rt].dump(tf, ans), ans.ifwt();
            print(ans[k], '\n');
        } else {
            read(k), read(v), lazy = 0;
            val[k] = v, bst::modify(k);
        }
    }
    // std::cerr << clock() / (double)CLOCKS_PER_SEC << std::endl;
}

} signed main() {
#ifdef MEMSET0_LOCAL_ENVIRONMENT
    freopen("1.in", "r", stdin);
    freopen("1.out", "w", stdout);
#endif
    return ringo::main(), 0;
}