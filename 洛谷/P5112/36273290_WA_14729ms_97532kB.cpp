// luogu-judger-enable-o2
// =================================
//   author: memset0
//   date: 2019.03.20 14:50:08
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

const int N = 3e6 + 10;
int n, m, k, tn, tm, sqn, cnt[N], bln[N];
ll ans, out[N];
unsigned long long tmp, a[N], b[N], h[N];
char s[N];

struct query {
    int l, r, id;
    inline bool operator < (const query &other) const {
        return bln[l] == bln[other.l] ? r < other.r : l < other.l;
    }
} q[N];

inline void add(unsigned long long x) { debug("add %u %d\n", x, cnt[x]); ++cnt[x]; ans += (cnt[x] << 1) - 2; }
inline void del(unsigned long long x) { debug("del %u %d\n", x, cnt[x]); ans -= (cnt[x] << 1) - 2; --cnt[x]; }

template <class T> inline T fpow(T a, int b) {
    T s = 1;
    for (; b; b >>= 1, a = a * a)
        if (b & 1) s = s * a;
    return s;
}

void main() {
    read(n), read(m), read(k), sqn = sqrt(n), scanf("%s", s + 1);
    
    for (int i = 1; i <= n; i++) h[i] = h[i - 1] * 131 + s[i];
    n = n - k + 1, tmp = fpow(131, k);
    for (int i = 1; i <= n; i++) a[i] = b[i] = h[i + k - 1] - tmp * h[i - 1];
    std::sort(b + 1, b + n + 1), tn = std::unique(b + 1, b + n + 1) - b - 1;
    for (int i = 1; i <= n; i++) a[i] = std::lower_bound(b + 1, b + tn + 1, a[i]) - b;
    for (int i = 1; i <= n; i++) bln[i] = (i - 1) / sqn + 1;
    for (int i = 1, l, r; i <= m; i++) {
        read(l), read(r), r = std::min(r, n);
        if (l <= r) q[++tm] = (query){l, r, i};
    }
    std::sort(q + 1, q + tm + 1);
    for (int i = 1, ul = 1, ur = 0; i <= tm; i++) {
        while (ul > q[i].l) add(a[--ul]);
        while (ur < q[i].r) add(a[++ur]);
        while (ul < q[i].l) del(a[ul++]);
        while (ur > q[i].r) del(a[ur--]);
        debug(">> %d %d %d | %d\n", q[i].l, q[i].r, q[i].id, ans);
        out[q[i].id] = ans;
    }
    // for (int i = 1; i <= n; i++) print(a[i], " \n"[i == n]);
    // for (int i = 1; i <= n; i++) print(b[i], " \n"[i == n]);
    for (int i = 1; i <= m; i++) print(out[i] >> 1, '\n');
}

} signed main() { return ringo::main(), 0; }