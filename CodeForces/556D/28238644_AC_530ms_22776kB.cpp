// =================================
//   author: memset0
//   date: 2019.04.05 22:52:29
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

const int N = 2e5 + 10;
int n, m, ans[N];
ll l[N], r[N], a[N];
std::set <std::pair <ll, int> > set;

struct limit {
    ll l, r; int id;
    inline bool operator < (const limit &other) const {
        return r == other.r ? l < other.l : r < other.r;
    }
} c[N];

void main() {
    read(n), read(m);
    for (int i = 1; i <= n; i++) read(l[i]), read(r[i]);
    for (int i = 1; i <= m; i++) read(a[i]), set.insert(std::make_pair(a[i], i));
    for (int i = 1; i < n; i++) c[i] = (limit){l[i + 1] - r[i], r[i + 1] - l[i], i};
    std::sort(c + 1, c + n);
	// for (auto& it : set) printf("<< %lld %d\n", it.first, it.second);
	// for (int i = 1; i < n; i++) printf(">> %lld %lld\n", c[i].l, c[i].r);
    for (int i = 1; i < n; i++) {	
        auto it = set.lower_bound(std::make_pair(c[i].l, -1));
		// printf("%lld %lld -> %lld %d\n", c[i].l, c[i].r, it->first, it->second);
        if (it == set.end()) { puts("No"); return; }
        if (it->first > c[i].r) { puts("No"); return; }
        ans[c[i].id] = it->second, set.erase(it);
    }
    puts("Yes");
    for (int i = 1; i < n; i++) print(ans[i], " \n"[i == n]);
}

} signed main() {
#ifdef MEMSET0_LOCAL_ENVIRONMENT
    freopen("1.in", "r", stdin);
#endif
    return ringo::main(), 0;
}