// luogu-judger-enable-o2
// luogu-judger-enable-o2
// =================================
//   author: memset0
//   date: 2019.02.14 11:37:47
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

const int N = 1e5 + 10, M = 2e5 + 10;
int n, m, s, dis[N];
int tot = 2, hed[N], nxt[M], to[M], val[M];

namespace Spfa {
    int M, tree[N << 2];
    inline int cmp(int a, int b) { return dis[a] < dis[b] ? a : b; }
    inline void build(int n) { M = 1; while (M < n + 2) M <<= 1; }
    inline void modify(int u, int w) { for (int k = u + M; dis[tree[k]] > w && k; k >>= 1) tree[k] = u; dis[u] = w; }
    inline void del(int k) { for (tree[k += M] = 0, k >>= 1; k; tree[k] = cmp(tree[k << 1], tree[k << 1 | 1]), k >>= 1); }
    void spfa() {
        memset(dis, 63, sizeof(dis)), build(n), modify(s, 0); int u, v;
        while (u = tree[1]) {
            del(u);
            for (int i = hed[u]; v = to[i], i; i = nxt[i], v = to[i])
                if (dis[v] > dis[u] + val[i]) {
                    dis[v] = dis[u] + val[i];
                    modify(v, dis[v]);
                }
        }
    }
} using Spfa::spfa;

void main() {
    read(n), read(m), read(s);
    for (int i = 1, u, v, w; i <= m; i++) {
        read(u), read(v), read(w);
        nxt[tot] = hed[u], to[tot] = v, val[tot] = w, hed[u] = tot++;
    } spfa();
    for (int i = 1; i <= n; i++) print(dis[i], " \n"[i == n]);
}

} signed main() { return ringo::main(), 0; }