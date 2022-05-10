// luogu-judger-enable-o2
// =================================
//   author: memset0
//   date: 2019.04.10 10:12:54
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

const int N = 8e5 + 10, P = N << 4, E = P << 2;
char s[N];
ll ans, dis[N];
int T, m, len, cnt;
std::vector <int> G[P], nod[N];
int x[N], y[N], q[N], val[P], ind[P];

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

namespace sa {
    const int M = N << 1;
    int siz, sa[M], rnk[M], tmp[M], tax[M], log[N], height[M], st[N][20];
    int query(int l, int r) {
        if (l > r) std::swap(l, r); l++; int t = log[r - l + 1];
        return std::min(st[l][t], st[r - (1 << t) + 1][t]);
    }
    void sort() {
        for (int i = 1; i <= siz; i++) tax[i] = 0;
        for (int i = 1; i <= len; i++) tax[rnk[i]]++;
        for (int i = 1; i <= siz; i++) tax[i] += tax[i - 1];
        for (int i = len; i >= 1; i--) sa[tax[rnk[tmp[i]]]--] = tmp[i];
    }
    void build(char *s) {
        memset(sa, 0, sizeof(sa));
        memset(rnk, 0, sizeof(rnk));
        memset(tmp, 0, sizeof(tmp));
        memset(height, 0, sizeof(height));
        siz = 200, log[0] = -1;
        for (int i = 1; i <= len; i++) rnk[i] = s[i], tmp[i] = i, log[i] = log[i >> 1] + 1;
        sort();
        for (int now = 1, cnt = 0; cnt < len; siz = cnt, now <<= 1) {
            cnt = 0;
            for (int i = len; i >= len - now + 1; i--) tmp[++cnt] = i;
            for (int i = 1; i <= len; i++) if (sa[i] > now) tmp[++cnt] = sa[i] - now;
            sort(), std::swap(rnk, tmp), rnk[sa[1]] = cnt = 1;
            for (int i = 2; i <= len; i++) rnk[sa[i]] = (tmp[sa[i]] == tmp[sa[i - 1]] && tmp[sa[i] + now] == tmp[sa[i - 1] + now]) ? cnt : ++cnt;
        }
        for (int i = 1, j, ans = 0; i <= len; i++) {
            j = sa[rnk[i] - 1]; if (ans) --ans;
            while (s[i + ans] == s[j + ans]) ++ans;
            height[rnk[i]] = ans;
        }
        height[1] = 0;
        for (int i = 1; i <= len; i++) st[i][0] = height[i];
        for (int i = 1; i < 20; i++)
            for (int j = 1; j + (1 << i) - 1 <= len; j++)
                st[j][i] =  std::min(st[j][i - 1], st[j + (1 << (i - 1))][i - 1]);
    }
}

struct node {
    int l, r, mid, cnt;
} p[N << 2];

void build(int u, int l, int r) {
    p[u].l = l, p[u].r = r, p[u].mid = (l + r) >> 1, p[u].cnt = ++cnt;
    // printf("[%d : %d - %d] %d\n", u, l, r, cnt);
    if (l == r) {
        for (auto it : nod[l])
            G[p[u].cnt].push_back(it);
        return;
    }
    build(u << 1, l, p[u].mid);
    build(u << 1 | 1, p[u].mid + 1, r);
    G[p[u].cnt].push_back(p[u << 1].cnt);
    G[p[u].cnt].push_back(p[u << 1 | 1].cnt);
}

void modify(int u, int l, int r, int s) {
    if (p[u].l == l && p[u].r == r) {
        G[s].push_back(p[u].cnt);
        return;
    }
    if (r <= p[u].mid) return modify(u << 1, l, r, s);
    if (l > p[u].mid) return modify(u << 1 | 1, l, r, s);
    modify(u << 1, l, p[u].mid, s), modify(u << 1 | 1, p[u].mid + 1, r, s);
}

struct array {
    int n, l[N], r[N], id[N], len[N];
    hash::pair h[N];
    inline void init() {
        read(n);
        for (int i = 1; i <= n; i++) {
            read(l[i]), read(r[i]);
            id[i] = ++cnt, len[i] = r[i] - l[i] + 1;
            // h[i] = hash::query(l[i], r[i]);
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
    scanf("%s", s + 1), len = strlen(s + 1), /*hash::init(), */a.init(), b.init(), read(m);
    for (int i = 1; i <= a.n; i++) G[1].push_back(a.id[i]), val[a.id[i]] = a.len[i];
    for (int i = 1; i <= m; i++) read(x[i]), read(y[i]), G[a.id[x[i]]].push_back(b.id[y[i]]);
    // for (int u = 1; u <= b.n; u++)
    //     for (int v = 1; v <= a.n; v++)
    //         if (a.len[v] >= b.len[u] && b.h[u] == hash::query(a.l[v], a.l[v] + b.len[u] - 1))
    //             G[b.id[u]].push_back(a.id[v]);
    sa::build(s);
    for (int i = 1; i <= a.n; i++) nod[sa::rnk[a.l[i]]].push_back(a.id[i]);
    // for (int i = 1;  <= a.n; i++) printf("[%d %d] -> %d\n", a.l[i], a.r[i], sa::rnk[a.l[i]]);
    build(1, 1, len);
    // for (int i = 1; i <= len; i++) for (int j : nod[i]) printf("nod %d -> %d\n", i, j);
    // for (int i = 1; i <= len; i++) print(sa::sa[i], " \n"[i == len]);
    // for (int i = 1; i <= len; i++) print(sa::rnk[i], " \n"[i == len]);
    for (int i = 1, U, L, R; i <= b.n; i++) {
        U = L = R = sa::rnk[b.l[i]];
        for (int l = 1, r = U - 1, mid; mid = l + r >> 1, l <= r; )
            if (sa::query(mid, U) >= b.len[i]) L = mid, r = mid - 1;
            else l = mid + 1;
        for (int l = U + 1, r = len, mid; mid = l + r >> 1, l <= r; )
            if (sa::query(U, mid) >= b.len[i]) R = mid, l = mid + 1;
            else r = mid - 1;
        // printf("%d : %d %d %d\n", i, U, L, R);
        modify(1, L, R, b.id[i]);
    }
    // for (int i = 1; i <= a.n; i++) print(a.id[i], " \n"[i == a.n]);
    // for (int i = 1; i <= b.n; i++) print(b.id[i], " \n"[i == b.n]);
    // for (int i = 1; i <= cnt; i++) for (auto j : G[i]) printf("edge : %d -> %d\n", i, j);
    print(find_answer(), '\n');
}

void init() {
    for (int i = 1; i <= len; i++) {
        nod[i].clear();
    }
    for (int i = 1; i <= cnt; i++) {
        G[i].clear();
        dis[i] = ind[i] = val[i] = 0;
    }
    cnt = 1, ans = 0;
}

void main() { for (read(T); T--; ) init(), solve(); }

} signed main() {
#ifdef MEMSET0_LOCAL_ENVIRONMENT
	freopen("1.in", "r", stdin);
#endif
	return ringo::main(), 0;
}