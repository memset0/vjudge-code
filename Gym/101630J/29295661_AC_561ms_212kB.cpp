// =================================
//   author: memset0
//   date: 2019.02.14 11:17:34
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
 
const int N = 3010;
int n, m, p;
ll ans = 4e18, dis[N];
 
int tot = 2, hed[N], nxt[N << 1], val[N << 1], to[N << 1];
inline void add(int u, int v, int w) {
    // printf("add %d %d %d\n", u, v, w);
    nxt[tot] = hed[u], to[tot] = v, val[tot] = w, hed[u] = tot++;
    nxt[tot] = hed[v], to[tot] = u, val[tot] = w, hed[v] = tot++;
}
 
struct edge {
    int u, v, w;
} E[N];
 
struct info {
    int u; ll w;
    inline bool operator < (const info &other) const {
        return w > other.w;
    }
} now; std::priority_queue <info> q;
 
ll spfa() {
    memset(dis, 0x3f, sizeof(dis)), dis[1] = 0, q.push((info){1, 0}); int u, v;
    while (q.size()) {
        now = q.top(), q.pop(); if (now.w != dis[u = now.u]) continue;
        for (int i = hed[u]; v = to[i], i; i = nxt[i])
            if (dis[v] > dis[u] + val[i]) {
                dis[v] = dis[u] + val[i];
                q.push((info){v, dis[v]});
            }
    } return dis[n];
}
 
void main() {
    read(n), read(m), read(p);
    for (int i = 1, u, v, w; i <= m; i++) read(u), read(v), read(w), E[i] = {u, v, w};
    for (int k = 0; k <= m; k++) {
        tot = 2, memset(hed, 0, sizeof(hed));
        // printf("limit = %d\n", E[k].w);
        for (int i = 1; i <= m; i++) add(E[i].u, E[i].v, std::max(0, E[i].w - E[k].w));
        ans = std::min(ans, spfa() + (ll)p * E[k].w);
        // printf(">>> %lld %lld\n", spfa(), (ll)p * E[k].w);
    } print(ans, '\n');
}
 
} signed main() { return ringo::main(), 0; }
/**************************************************************
    Problem: 5217
    User: w15
    Language: C++
    Result: 正确
    Time:548 ms
    Memory:1680 kb
****************************************************************///adfdsfasdfasdf