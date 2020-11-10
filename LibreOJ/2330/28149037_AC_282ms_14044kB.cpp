// luogu-judger-enable-o2
// =================================
//   author: memset0
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

const int N = 1e5 + 10;
int W, T, n;
int f[N], fa[N], dep[N], ans[N], siz[N];
int tot = 2, hed[N], nxt[N << 1], to[N << 1];
std::vector <int> son[N];

void init() {
    tot = 2, memset(hed, 0, sizeof(hed));
    for (int i = 1; i <= n; i++) son[i].clear();
}

void dfs1(int u) {
    siz[u] = 1;
    for (int i = hed[u], v; v = to[i], i; i = nxt[i])
        if (v != fa[u]) {
            fa[v] = u, dep[v] = dep[u] + 1, son[u].push_back(v);
            dfs1(v), siz[u] += siz[v];
        }
}

void dfs2(int u) {
//	printf(">> dfs2 %d siz=%d\n", u, siz[u]);
    if (siz[u] == 1) { f[u] = 0; return; }
    for (auto v : son[u]) dfs2(v);
    int max = 0;
    for (auto v : son[u]) if (siz[v] > siz[max]) max = v;
    int half = siz[u] - 1 - siz[max];
    if (half >= f[max] + 1) f[u] = (siz[u] - 1) & 1;
    else f[u] = f[max] - half + 1;
//	printf("dfs2 %d %d[%d %d] %d\n", u, max, f[max], siz[max], half);
}

void dfs3(int u, int Max) {
//	printf("dfs3 %d %d %d\n", u, Sum, Max);
    int mx1 = 0, mx2 = 0, sum = 0;
    for (auto v : son[u]) {
        if (siz[v] > siz[mx1]) mx2 = mx1, mx1 = v;
        else if (siz[v] > siz[mx2]) mx2 = v;
    }
    for (auto v : son[u]) {
        int max = mx1 == v ? mx2 : mx1;
        dfs3(v, siz[max] > siz[Max] ? max : Max);
    }
    if (u != 1 && ans[u]) {
        Max = siz[mx1] > siz[Max] ? mx1 : Max;
        int Half = n - dep[u] - siz[Max];
//		printf(">> recheck %d => max = %d half\n", u, Max, Half);
        if (Half < f[Max]) {
            ans[u] = (f[Max] - Half + 1) == 0;
        }
    }
}

void main() {
    read(W), read(T), f[0] = siz[0] = -1;
    while (T--) {
        read(n), init();
        for (int i = 1, u, v; i < n; i++) {
            read(u), read(v);
            nxt[tot] = hed[u], to[tot] = v, hed[u] = tot++;
            nxt[tot] = hed[v], to[tot] = u, hed[v] = tot++;
        }
        dep[1] = 1, dfs1(1), dfs2(1);
//		for (int i = 1; i <= n; i++) print(f[i], " \n"[i == n]);
//		for (int i = 1; i <= n; i++) print(siz[i], " \n"[i == n]);
        for (int i = 1; i <= n; i++) ans[i] = (n - dep[i]) & 1 ^ 1;
//		for (int i = 1; i <= n; i++) putchar('0' + ans[i]); putchar('\n');
        dfs3(1, 0), ans[1] &= f[1] == 0;
        if (W == 3) putchar('0' + ans[1]), putchar('\n');
        else { for (int i = 1; i <= n; i++) putchar('0' + ans[i]); putchar('\n'); }
    }
}

} signed main() {
#ifdef MEMSET0_LOCAL_ENVIRONMENT
    freopen("1.in", "r", stdin);
#endif
    return ringo::main(), 0;
}
