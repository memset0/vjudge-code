// =================================
//   author: memset0
//   date: 2019.04.16 10:07:48
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

const int N = 110, P = N << 1, E = 20410;
ll ans;
std::vector<int> vet[N];
int n, m, s, e, cnt, max, key;
int cur[P], dep[P], gap[P], pre[P];
int tot = 2, hed[P], to[E], val[E], nxt[E];
int id1[N], id2[N], max1[N], max2[N], a[N][N];

inline void add(int u, int v, int w) {
    // printf("add %d %d %d\n", u, v, w);
    nxt[tot] = hed[u], to[tot] = v, val[tot] = w, hed[u] = tot++;
    nxt[tot] = hed[v], to[tot] = u, val[tot] = 0, hed[v] = tot++;
}

ll isap() {
    int u = s;
    ll ans = 0;
    while (dep[u] < cnt) {
        if (u == e) {
            int flow = 1e9;
            for (int i = pre[e]; i; i = pre[to[i ^ 1]])
                flow = std::min(flow, val[i]);
            for (int i = pre[e]; i; i = pre[to[i ^ 1]])
                val[i] -= flow, val[i ^ 1] += flow;
            // printf("find yet another new flow : %d\n", flow);
            ans += flow, u = s;
        }
        bool flag = false;
        for (int &i = cur[u]; i; i = nxt[i])
            if (val[i] && dep[u] == dep[to[i]] + 1) {
                u = to[i], pre[u] = i;
                flag = true; break;
            }
        if (!flag) {
            if (!--gap[dep[u]]) break;
            dep[u] = cnt;
            for (int i = hed[u]; i; i = nxt[i])
                if (val[i] && dep[u] > dep[to[i]] + 1) {
                    dep[u] = dep[to[i]] + 1;
                    cur[u] = i;
                }
            if (u != s) u = to[pre[u] ^ 1];
        }
    }
    return ans;
}

void main() {
    read(n), read(m);
    s = ++cnt, e = ++cnt;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            read(a[i][j]);
    for (int i = 1; i <= n; i++) {
        id1[i] = ++cnt, max = key = -1;
        for (int j = 1; j <= m; j++)
            if (a[i][j] > max)
                max = a[i][j], key = j;
        // printf("[1] %d -> %d\n", i, max);
        if (max > 1) {
            max1[i] = max;
            ans -= max - 1;
            add(s, id1[i], max - 1);
        }
    }
    for (int i = 1; i <= m; i++) {
        id2[i] = ++cnt, max = key = -1;
        for (int j = 1; j <= n; j++)
            if (a[j][i] > max)
                max = a[j][i], key = j;
        // printf("[2] %d -> %d\n", i, max);
        if (max > 1) {
            max2[i] = max;
            ans -= max - 1;
            add(id2[i], e, max - 1);
        }
    }
    // printf(">> %lld\n", ans);
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            if (a[i][j])
                ans += a[i][j] - 1;
    // printf(">> %lld\n", ans);
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            if (a[i][j] && max1[i] == max2[j] && ~max1[i] && ~max2[i]) {
                // printf("%d <-> %d : %d\n", i, j, max1[i] - 1);
                add(id1[i], id2[j], max1[i] - 1);
            }   
    ans += isap();
    // printf(">> %lld\n", ans);
    print(ans, '\n');
}

} signed main() {
#ifdef MEMSET0_LOCAL_ENVIRONMENT
    freopen("1.in", "r", stdin);
#endif
    return ringo::main(), 0;
}