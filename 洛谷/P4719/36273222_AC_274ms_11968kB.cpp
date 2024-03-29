// luogu-judger-enable-o2
// luogu-judger-enable-o2
// luogu-judger-enable-o2
// =================================
//   author: memset0
//   date: 2018.12.19 09:56:29
//   website: https://memset0.cn/
// =================================
#include <bits/stdc++.h>
#define rep(i, l, r) for (register int i = l; i <= r; i++)
namespace ringo {
typedef long long ll;
typedef unsigned long long ull;


inline char read() {
    static const int IN_LEN = 1000000;
    static char buf[IN_LEN], *s, *t;
    return (s==t?t=(s=buf)+fread(buf,1,IN_LEN,stdin),(s==t?-1:*s++):*s++);
}
template<class T>
inline void read(T &x) {
    static bool iosig;
    static char c;
    for (iosig=false, c=read(); !isdigit(c); c=read()) {
        if (c == '-') iosig=true;
        if (c == -1) return;
    }
    for (x=0; isdigit(c); c=read()) x=((x+(x<<2))<<1)+(c^'0');
    if (iosig) x=-x;
}
const int OUT_LEN = 10000000;
char obuf[OUT_LEN], *ooh=obuf;
inline void print(char c) {
    if (ooh==obuf+OUT_LEN) fwrite(obuf, 1, OUT_LEN, stdout), ooh=obuf;
    *ooh++=c;
}
template <class T> inline void print(T x) {
    static int buf[30], cnt;
    if (x==0) print('0');
    else {
        if (x<0) print('-'), x=-x;
        for (cnt=0; x; x/=10) buf[++cnt]=x%10+48;
        while(cnt) print((char)buf[cnt--]);
    }
}
inline void flush() { fwrite(obuf, 1, ooh - obuf, stdout); }
template <class T> inline void maxd(T &a, T b) { if (b > a) a = b; }
template <class T> inline void mind(T &a, T b) { if (b < a) a = b; }
template <class T> inline void print(T x, char c) { print(x), print(c); }
template <class T> inline T abs(const T &a) { if (a < 0) return -a; return a; }

const int N = 1e5 + 10, inf = 1e9;
int n, m, u, v, w, rt, top, dta, ch[N][2];
typedef int R[N]; R a, stk, son, fa, siz, fat, dep;
int tot = 2, hed[N], to[N << 1], nxt[N << 1];

struct matrix {
    int a[2][2];
    inline int* operator [] (const size_t i) { return a[i]; }
} f[N], g[N], sum[N];

inline matrix operator * (const matrix &a, const matrix &b) {
    return (matrix) {{{
        std::max(a.a[0][0] + b.a[0][0], a.a[0][1] + b.a[1][0]),
        std::max(a.a[0][0] + b.a[0][1], a.a[0][1] + b.a[1][1])},{	
        std::max(a.a[1][0] + b.a[0][0], a.a[1][1] + b.a[1][0]),
        std::max(a.a[1][0] + b.a[0][1], a.a[1][1] + b.a[1][1])
    }}};
}

void dfs(int u) {
    siz[u] = 1;
    for (int i = hed[u], v = to[i]; i; i = nxt[i], v = to[i])
        if (v != fat[u]) {
            fat[v] = u, dep[v] = dep[u] + 1, dfs(v), siz[u] += siz[v];
            if (siz[v] > siz[son[u]]) son[u] = v;
        }
}

void dfs2(int u) {
    f[u][1][0] = g[u][1][0] = a[u];
    for (int i = hed[u], v = to[i]; i; i = nxt[i], v = to[i])
        if (v != fat[u]) {
            dfs2(v);
            f[u][0][0] += std::max(f[v][0][0], f[v][1][0]);
            f[u][1][0] += f[v][0][0];
            if (v != son[u]) {
                g[u][0][0] += std::max(f[v][0][0], f[v][1][0]);
                g[u][1][0] += f[v][0][0];
            }
        }
}

void update(int u) {
    f[u] = g[u];
    if (ch[u][0]) f[u] = f[ch[u][0]] * f[u];
    if (ch[u][1]) f[u] = f[u] * f[ch[u][1]];
}

int sbuild(int l, int r) {
    int sum = 0, now = 0;
    for (int i = l; i <= r; i++) sum += siz[stk[i]] - siz[son[stk[i]]];
    for (int i = l; i <= r; i++) {
        now += siz[stk[i]] - siz[son[stk[i]]];
        if ((now << 1) >= sum) {
            fa[ch[stk[i]][0] = sbuild(l, i - 1)] = stk[i];
            fa[ch[stk[i]][1] = sbuild(i + 1, r)] = stk[i];
            return update(stk[i]), stk[i];
        }
    }
    return 0;
}

int build(int u) {
    for (int x = u; x; x = son[x])
        for (int i = hed[x], v = to[i]; i; i = nxt[i], v = to[i])
            if (v != fat[x] && v != son[x])
                fa[build(v)] = x;
    top = 0; for (int x = u; x; x = son[x]) stk[++top] = x;
    return sbuild(1, top);
}

void update(int u, int dta) { 
    for (int x = u; x; x = fa[x])
        if (ch[fa[x]][0] != x && ch[fa[x]][1] != x && fa[x]) {
            g[fa[x]][0][0] -= std::max(f[x][0][0], f[x][1][0]);
			g[fa[x]][0][1] = g[fa[x]][0][0];
            g[fa[x]][1][0] -= f[x][0][0];
            if (u == x) g[x][1][0] += dta;
            update(x);
            g[fa[x]][0][0] += std::max(f[x][0][0], f[x][1][0]);
			g[fa[x]][0][1] = g[fa[x]][0][0];
            g[fa[x]][1][0] += f[x][0][0];
        } else {
            if (u == x) g[x][1][0] += dta;
            update(x);
        }
}

void main() {
    read(n), read(m);
    for (int i = 1; i <= n; i++) read(a[i]);
    for (int i = 1; i < n; i++) {
        read(u), read(v);
        nxt[tot] = hed[u], to[tot] = v, hed[u] = tot++;
        nxt[tot] = hed[v], to[tot] = u, hed[v] = tot++;
    }
    f[0] = {{{1, 0}, {0, 1}}};
    dfs(1), dfs2(1);
    for (int i = 1; i <= n; i++)
		g[i][0][1] = g[i][0][0], g[i][1][1] = -inf;
	rt = build(1);
    for (int i = 1; i <= m; i++) {
        read(u), read(w), dta = w - a[u], a[u] = w;
        update(u, dta), print(std::max(f[rt][0][0], f[rt][1][0]), '\n');
    }
}

} signed main() { return ringo::main(), ringo::flush(), 0; }