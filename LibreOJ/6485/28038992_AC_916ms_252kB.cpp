// =================================
//   author: memset0
//   date: 2019.03.30 15:37:11
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

const int mod = 998244353;
int T, n, s, wn, ans;
int a[4], w[4];

inline int dec(int a, int b) { a -= b; return a < 0 ? a + mod : a; }
inline int sub(int a, int b) { a += b; return a >= mod ? a - mod : a; }
inline int mul(int a, int b) { return (ll)a * b - (ll)a * b / mod * mod; }
inline int inv(int x) { return x < 2 ? 1 : mul(mod - mod / x, inv(mod % x)); }
inline int sub4(int a, int b, int c, int d) { return ((ll)a + b + c + d) % mod; }
inline int fpow(int a, int b) { int s = 1; for (; b; b >>= 1, a = mul(a, a)) if (b & 1) s = mul(s, a); return s; }

void main() {
    wn = fpow(3, (mod - 1) >> 2), w[0] = 1;
    for (int i = 1; i < 4; i++) w[i] = mul(w[i - 1], wn);
    for (read(T); T--; ) {
        read(n), read(s), ans = 0;
        for (int i = 0; i < 4; i++) read(a[i]);
        for (int i = 0; i < 4; i++)
            for (int j = 0; j < 4; j++)
                ans = sub(ans, mul(a[i], mul(w[(444 - i * j) % 4], fpow(sub(mul(s, w[j]), 1), n))));
        print(mul(ans, inv(4)), '\n');
    }
}

} signed main() {
#ifdef MEMSET0_LOCAL_ENVIRONMENT
    freopen("1.in", "r", stdin);
#endif
    return ringo::main(), 0;
}
