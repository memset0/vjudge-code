// =================================
//   author: memset0
//   date: 2019.01.15 07:32:59
//   website: https://memset0.cn/
// =================================
#include <bits/stdc++.h>
#define ll long long
namespace ringo {
template <class T>
inline void read(T &x) {
    x = 0;
    register char c = getchar();
    register bool f = 0;
    while (!isdigit(c)) f ^= c == '-', c = getchar();
    while (isdigit(c)) x = x * 10 + c - '0', c = getchar();
    if (f)
        x = -x;
}
template <class T>
inline void print(T x) {
    if (x < 0)
        putchar('-'), x = -x;
    if (x > 9)
        print(x / 10);
    putchar('0' + x % 10);
}
template <class T>
inline void print(T x, char c) {
    print(x), putchar(c);
}

#define clear(x) memset(x, 0, sizeof(x))
const int N = 8e5 + 10, M = 8e4 + 10, mod = 1e9 + 7;
const double pi = acos(-1);
int T, n, m, p, v, k, lim, ans, limit;
int a[N], c[N], s[N], rev[N], lst[M];
bool tag[M];

inline int fpow(int a, int b) {
    int s = 1;
    for (; b; b >>= 1, a = (ll)a * a % mod)
        if (b & 1)
            s = (ll)s * a % mod;
    return s;
}

inline void print(int *a, int l, int r) {
    for (int i = l; i < r; i++) print(a[i], ' ');
    puts("");
}

struct complex {
    double x, y;
    inline complex() {}
    inline complex(double _x, double _y) { x = _x, y = _y; }
    inline complex operator+(const complex &other) { return complex(x + other.x, y + other.y); }
    inline complex operator-(const complex &other) { return complex(x - other.x, y - other.y); }
    inline complex operator*(const complex &other) {
        return complex(x * other.x - y * other.y, x * other.y + y * other.x);
    }
} w[25][N];

void fft(complex *a) {
    for (int i = 0; i < lim; i++)
        if (i < rev[i])
            std::swap(a[i], a[rev[i]]);
    for (int len = 1, cnt = 0; len < lim; len <<= 1, cnt++)
        for (int i = 0; i < lim; i += (len << 1))
            for (int j = 0; j < len; j++) {
                complex x = a[i + j], y = a[i + j + len] * w[cnt][j];
                a[i + j] = x + y, a[i + j + len] = x - y;
            }
}

inline void mul(int *f, int *g) {
    static complex v1(0.5, 0), v2(0, -0.5), v3(0, 1);
    static complex a[N], b[N], c[N], d[N];
    // printf("operator *\n  "), print(f, 0, lim), printf("  "), print(g, 0, lim);
    for (int i = 0; i < lim; i++) {
        a[i].x = f[i] & 32767, a[i].y = f[i] >> 15;
        c[i].x = g[i] & 32767, c[i].y = g[i] >> 15;
    }
    fft(a), fft(c);
    for (int i = 0, j; i < lim; i++) {
        j = (lim - 1) & (lim - i);
        complex A = complex(a[i].x + a[j].x, a[i].y - a[j].y) * v1;
        complex B = complex(a[i].x - a[j].x, a[i].y + a[j].y) * v2;
        complex C = complex(c[i].x + c[j].x, c[i].y - c[j].y) * v1;
        complex D = complex(c[i].x - c[j].x, c[i].y + c[j].y) * v2;
        b[j] = A * C + A * D * v3, d[j] = B * C + B * D * v3;
    }
    fft(b), fft(d), memset(f, 0, lim << 2);
    for (int i = 0; i < lim; i++) {
        ll _1 = b[i].x / lim + 0.5, _2 = b[i].y / lim + d[i].x / lim + 0.5, _3 = d[i].y / lim + 0.5;
        f[i % v] = (f[i % v] + ((_3 % mod) << 30) + ((_2 % mod) << 15) + _1 % mod) % mod;
    }
    // printf("= "), print(f, 0, lim);
}

int inv(int x) {
    if (!x || x == 1)
        return 1;
    return (ll)(mod - mod / x) * inv(mod % x) % mod;
}

void main() {
    for (read(T); T--;) {
        ans = k = 0, lim = 1;
        read(n), read(m), read(p);
        for (int i = 1; i <= m; i++) read(c[i]);
        v = c[1];
        for (int i = 2; i <= m; i++) v = std::__gcd(v, c[i]);
        while (lim <= (v << 1)) lim <<= 1, ++k;
        for (int i = 0; i < lim; i++) {
            a[i] = s[i] = 0;
            rev[i] = (rev[i >> 1] >> 1) | ((i & 1) << (k - 1));
            w[k][i] = complex(cos(pi * i / lim), sin(pi * i / lim));
        }
        a[0] = 100 - p, a[1 % v] = p, s[0] = 1;
        for (int i = k - 1, tmp = lim >> 1; ~i; i--, tmp >>= 1)
            for (int j = 0; j < tmp; j++) w[i][j] = w[i + 1][j << 1];
        for (int b = n; b; b >>= 1, mul(a, a))
            if (b & 1)
                mul(s, a);
        // print(s, 0, lim);
        for (int i = 1; i < v; i++) ans = (ans + (ll)(v - i) * s[i]) % mod;
        limit = (10000 / v + 1) * v, memset(tag, 0, sizeof(tag)), tag[0] = 1;
        for (int i = 1; i <= m; i++)
            for (int j = 0; j + c[i] <= limit; j++)
                if (tag[j])
                    tag[j + c[i]] = 1;
        for (int i = limit; i >= 0; i--) lst[i] = tag[i] ? 0 : lst[i + 1] + 1;
        for (int i = 0; i <= limit; i++) lst[i] = lst[i] - (i % v ? v - i % v : 0);
        for (int i = 0, now, C = 1; i <= limit && i <= n; i++) {
            if (i)
                C = (ll)C * (n - i + 1) % mod * inv(i) % mod;
            if (lst[i]) {
                // printf(">> %d %d %d : %d %d %d : %d %d %d\n", i, lst[i], ans, C, fpow(p, i), fpow(100 - p,
                // n - i));
                now = (ll)C % mod * fpow(p, i) % mod * fpow(100 - p, n - i) % mod;
                ans = (ans + (ll)now * lst[i]) % mod;
            }
        }
        print(ans, '\n');
    }
}

}  // namespace ringo
signed main() { return ringo::main(), 0; }
