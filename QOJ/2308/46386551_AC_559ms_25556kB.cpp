// =================================
//   author: memset0
//   date: 2019.03.22 17:12:24
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

const int N = 2e5 + 10;
int n, m, k, lft, rit;
int a[N], l[N], d[N];
ll L, R, ans, s[N];

struct node {
    int a, l;
    inline bool operator < (const node &other) const {
        return a < other.a;
    }
} p[N];
inline ll dis(int a, int b) { return s[b] - s[a]; }

struct segment_tree {
    bool F;
    struct node {
        int l, r, mid, min, max;
    } p[N << 2];
    void build(int u, int l, int r) {
        p[u].l = l, p[u].r = r, p[u].mid = (l + r) >> 1;
        if (l == r) {
            p[u].min = p[u].max = F ? s[a[l]] + ringo::l[l] : s[a[l]] - ringo::l[l];
            return; }
        build(u << 1, l, p[u].mid);
        build(u << 1 | 1, p[u].mid + 1, r);
        p[u].min = std::min(p[u << 1].min, p[u << 1 | 1].min);
        p[u].max = std::max(p[u << 1].max, p[u << 1 | 1].max);
    }
    int query_min(int u, int l, int r) {
        // printf("query min %d %d %d : %d\n", u, l, r, p[u].min);
        if (p[u].l == l && p[u].r == r) return p[u].min;
        if (r <= p[u].mid) return query_min(u << 1, l, r);
        if (l > p[u].mid) return query_min(u << 1 | 1, l, r);
        return std::min(query_min(u << 1, l, p[u].mid), query_min(u << 1 | 1, p[u].mid + 1, r));
    }
    int query_max(int u, int l, int r) {
        // printf("query max %d %d %d : %d\n", u, l, r, p[u].max);
        if (p[u].l == l && p[u].r == r) return p[u].max;
        if (r <= p[u].mid) return query_max(u << 1, l, r);
        if (l > p[u].mid) return query_max(u << 1 | 1, l, r);
        return std::max(query_max(u << 1, l, p[u].mid), query_max(u << 1 | 1, p[u].mid + 1, r));
    }
    void dfs(int u) {
        printf("[%d %d] => %d %d\n", p[u].l, p[u].r, p[u].min, p[u].max);
        if (p[u].l == p[u].r) return;
        dfs(u << 1), dfs(u << 1 | 1);
    }
} s0, s1;

void main() {
    read(n), read(m);
    for (int i = 1; i < n; i++) read(d[i]), s[i + 1] = s[i] + d[i];
    s0.F = 0, s1.F = 1;
    for (int i = 1; i <= m; i++) {
        read(k), ans = 0;
        for (int i = 1; i <= k; i++) read(p[i].a), read(p[i].l);
        std::sort(p + 1, p + k + 1);
		for (int i = 1; i <= k; i++) a[i] = p[i].a, l[i] = p[i].l;
        s0.build(1, 1, k), s1.build(1, 1, k);
        for (int i = 1, F, L, M, R; i <= k; i++) {
            lft = a[i];
			for (int left = 1, right = a[i], mid; F = 1, mid = (left + right) >> 1, left <= right; ) {
                L = std::lower_bound(a + 1, a + i + 1, (mid << 1) - a[i]) - a;
                M = std::lower_bound(a + 1, a + i + 1, mid) - a;
                R = i - 1, L = std::max(L, (int)1);
                if (a[L] - mid == mid - a[i] && s[a[L]] - l[L] == (s[mid] << 1) - l[i] - s[a[i]]) L++;
                if (L <= M - 1) F &= s0.query_max(1, L, M - 1) < (s[mid] << 1) - l[i] - s[a[i]];
                if (M <= R) F &= s1.query_min(1, M, R) > s[a[i]] + l[i];
				F ? right = mid - 1, lft = mid : left = mid + 1;
			}
			rit = a[i];
			for (int left = a[i], right = n, mid; F = 1, mid = (left + right) >> 1, left <= right; ) {
                L = i + 1;
                M = std::upper_bound(a + i, a + k + 1, mid) - a - 1;
                R = std::upper_bound(a + i, a + k + 1, (mid << 1) - a[i]) - a - 1;
                if (L <= M) F &= s0.query_max(1, L, M) < s[a[i]] - l[i];
                if (M + 1 <= R) F &= s1.query_min(1, M + 1, R) > (s[mid] << 1) + l[i] - s[a[i]];
				F ? left = mid + 1, rit = mid : right = mid - 1;
			}
			// printf("%d : [%d %d]\n", i, lft, rit);
            ans += std::max(rit - lft + 1, (int)0);
        }
        print(ans, '\n');
    }
}

} signed main() { return ringo::main(), 0; }