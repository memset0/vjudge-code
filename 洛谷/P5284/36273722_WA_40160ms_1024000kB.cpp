// luogu-judger-enable-o2
// =================================
//   author: memset0
//   date: 2019.04.10 10:12:54
//   website: https://memset0.cn/
// =================================
#include <bits/stdc++.h>
#define ll long long
#define int long long
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

const int N = 2e5 + 10, P = N << 2, E = P << 2;
char s[N];
ll ans, dis[N];
int T, m, len, cnt;
std::vector <int> G[P];
int x[N], y[N], q[N], val[P], ind[P];

void init() {
    for (int i = 1; i <= cnt; i++) {
        G[i].clear();
        dis[i] = ind[i] = 0;
    }
    cnt = 1, ans = 0;
}

namespace hash {
    const int p1 = 998244353, p2 = 1e9 + 7;
    inline int dec(int a, int b, int p) { a -= b; return a < 0 ? a + p : a; }
    inline int inc(int a, int b, int p) { a += b; return a >= p ? a - p : a; }
    inline int mul(int a, int b, int p) { return (ll)a * b - (ll)a * b / p * p; }
    inline int inv(int x, int p) { return x < 2 ? 1 : mul(p - p / x, inv(x, p), p); }
    inline int fpow(int a, int b, int p) { int s = 1; for (; b; b >>= 1, a = mul(a, a, p)) if (b & 1) s = mul(s, a, p); return s; }
    struct pair {
        int a, b;
        inline pair() {}
        inline pair(int x) { a = b = x; }
        inline pair(int x, int y) { a = x, b = y; }
        inline bool operator == (const pair &r) const { return a == r.a && b == r.b; }
        inline pair operator + (const pair &r) const { return pair(inc(a, r.a, p1), inc(b, r.b, p2)); }
        inline pair operator - (const pair &r) const { return pair(dec(a, r.a, p1), dec(b, r.b, p2)); }
        inline pair operator * (const pair &r) const { return pair(mul(a, r.a, p1), mul(b, r.b, p2)); }
    } base(131, 131131), h[N], p[N] = {pair(1)};
    inline void init() {
        for (int i = 1; i <= len; i++) p[i] = p[i - 1] * base;
        for (int i = 1; i <= len; i++) h[i] = h[i - 1] * base + pair(s[i]);
    }
    inline pair query(int l, int r) {
        return h[r] - h[l - 1] * p[r - l + 1];
    }
}

struct array {
    int n, l[N], r[N], id[N], len[N];
    hash::pair h[N];
    inline void init() {
        read(n);
        for (int i = 1; i <= n; i++) {
            read(l[i]), read(r[i]), len[i] = r[i] - l[i] + 1;
            id[i] = ++cnt, h[i] = hash::query(l[i], r[i]);
        }
    }
} a, b;

ll find_answer() {
    int l = 1, r = 0, u;
    for (int u = 1; u <= cnt; u++) for (auto v : G[u]) ind[v]++;
    for (int i = 1; i <= cnt; i++) if (!ind[i]) q[++r] = i;
    // for (int i = 1; i <= cnt; i++) print(ind[i], " \n"[i == cnt]);
    while (l <= r) {
        u = q[l++], ans = std::max(ans, dis[u]);
        for (auto v : G[u]) {
            // printf("%d -> %d\n", u, v);
            dis[v] = std::max(dis[v], dis[u] + val[v]);
            if (!--ind[v]) q[++r] = v;
        }
    }
    // for (int i = 1; i <= cnt; i++) print(ind[i], " \n"[i == cnt]);
    if (r != cnt) return -1;
    return ans;
}

void solve() {
    // puts("===========================");
    scanf("%s", s + 1), len = strlen(s + 1), hash::init(), a.init(), b.init(), read(m);
    for (int i = 1; i <= a.n; i++) val[a.id[i]] = a.len[i];
    for (int i = 1; i <= m; i++) read(x[i]), read(y[i]), G[a.id[x[i]]].push_back(b.id[y[i]]);
    for (int u = 1; u <= b.n; u++)
        for (int v = 1; v <= a.n; v++)
            if (a.len[v] > b.len[u] && b.h[u] == hash::query(a.l[v], a.l[v] + b.len[u] - 1))
                G[b.id[u]].push_back(a.id[v]);
    for (int i = 1; i <= a.n; i++) G[1].push_back(a.id[i]);
    // for (int i = 1; i <= a.n; i++) print(a.id[i], " \n"[i == a.n]);
    // for (int i = 1; i <= b.n; i++) print(b.id[i], " \n"[i == b.n]);
    // for (int i = 1; i <= cnt; i++) for (auto j : G[i]) printf("edge : %d -> %d\n", i, j);
    print(find_answer(), '\n');
}

void main() { for (read(T); T--; ) init(), solve(); }

} signed main() {
#ifdef MEMSET0_LOCAL_ENVIRONMENT
	freopen("1.in", "r", stdin);
#endif
	return ringo::main(), 0;
}