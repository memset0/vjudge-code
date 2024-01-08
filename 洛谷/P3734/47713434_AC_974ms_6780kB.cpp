// luogu-judger-enable-o2
// =================================
//   author: memset0
//   date: 2019.03.12 16:02:18
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

const int N = 1e4 + 10, M = 100, mod = 998244353;
int n, m, ans, f[N], fac[M], ifac[M], dp[M][M][M];
ll ex, ey, ez;

struct node {
    int x, y, z, cx, cy, cz;
    inline bool operator < (const node &other) const {
        if (cx != other.cx) return cx < other.cx;
        if (cy != other.cy) return cy < other.cy;
        if (cz != other.cz) return cz < other.cz;
        return x < other.x;
    }
    inline bool in(const node &other) {
        if (x != (x & other.x)) return false;
        if (y != (y & other.y)) return false;
        if (z != (z & other.z)) return false;
        return true;
    }
    inline node() {}
    inline node(ll a, ll b, ll c) {
        x = a, y = b, z = c;
        cx = __builtin_popcountll(x);
        cy = __builtin_popcountll(y);
        cz = __builtin_popcountll(z);
    }
} s, e, a[N];

inline void decd(int &a, int b) { a -= b; if (a < 0) a += mod; }
inline void sumd(int &a, int b) { a += b; if (a >= mod) a -= mod; }
inline int C(int n, int m) { return (ll)fac[n] * ifac[m] % mod * ifac[n - m] % mod; }

void main() {
    read(ex), read(ey), read(ez), read(n);
    for (int i = 1, x, y, z; i <= n; i++) read(x), read(y), read(z), a[i] = node(x, y, z);
    std::sort(a + 1, a + n + 1);
    s = node(0, 0, 0), e = node(ex, ey, ez), m = std::max(e.cx, std::max(e.cy, e.cz));
    fac[0] = fac[1] = ifac[0] = ifac[1] = dp[0][0][0] = 1;
    for (int i = 2; i <= m; i++) fac[i] = (ll)fac[i - 1] * i % mod;
    for (int i = 2; i <= m; i++) ifac[i] = (ll)(mod - mod / i) * ifac[mod % i] % mod;
    for (int i = 2; i <= m; i++) ifac[i] = (ll)ifac[i - 1] * ifac[i] % mod;
    for (int i = 0; i <= e.cx; i++)
        for (int j = 0; j <= e.cy; j++)
            for (int k = 0; k <= e.cz; k++) {
                for (int t = 1; t <= i; t++) sumd(dp[i][j][k], (ll)dp[i - t][j][k] * C(i, i - t) % mod);
                for (int t = 1; t <= j; t++) sumd(dp[i][j][k], (ll)dp[i][j - t][k] * C(j, j - t) % mod);
                for (int t = 1; t <= k; t++) sumd(dp[i][j][k], (ll)dp[i][j][k - t] * C(k, k - t) % mod);
            }
    a[n + 1] = e;
    for (int i = 1; i <= n + 1; i++)
        if (a[i].in(e)) {
            f[i] = dp[a[i].cx][a[i].cy][a[i].cz];
            for (int j = 1; j < i; j++) if (a[j].in(e) && a[j].in(a[i])) decd(f[i], (ll)f[j] * dp[a[i].cx - a[j].cx][a[i].cy - a[j].cy][a[i].cz - a[j].cz] % mod);
        }
    print(f[n + 1], '\n');
}

} signed main() { return ringo::main(), 0; }