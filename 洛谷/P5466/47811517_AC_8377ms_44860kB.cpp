// luogu-judger-enable-o2
// =================================
//   author: memset0
//   date: 2019.01.18 13:55:29
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

const int N = 2e6 + 10, mod = 998244353;
int n, k, inv, lim = 1;
ll ans;
int a[N], b[N], f[N], g[N], t[N], w[N], rev[N];
char s[N];

int fpow(int a, int b) {
    int s = 1;
    for (; b; b >>= 1, a = (ll)a * a % mod)
        if (b & 1)
            s = (ll)s * a % mod;
    return s;
}

void ntt(int *a) {
    for (int i = 0; i < lim; i++)
        if (i < rev[i])
            std::swap(a[i], a[rev[i]]);
    for (int len = 1; len < lim; len <<= 1)
        for (int i = 0; i < lim; i += (len << 1))
            for (int j = 0; j < len; j++) {
                int x = a[i + j], y = (ll)a[i + j + len] * w[len + j] % mod;
                a[i + j] = (x + y) % mod, a[i + j + len] = (x - y + mod) % mod;
            }
}

void calc(int *a, int *b, int *f) {
    ntt(a), ntt(b);
    for (int i = 0; i < lim; i++) f[i] = (ll)a[i] * b[i] % mod;
    std::reverse(f + 1, f + lim), ntt(f), inv = fpow(lim, mod - 2);
    for (int i = 0; i < n; i++) f[i] = (ll)f[i] * inv % mod;
}

void main() {
    scanf("%s", s), n = strlen(s);
    while (lim <= (n << 1)) lim <<= 1, ++k;
    for (int i = 0; i < lim; i++) rev[i] = (rev[i >> 1] >> 1) | ((i & 1) << (k - 1));
    for (int len = 1; len < lim; len <<= 1) {
        int wn = fpow(3, (mod - 1) / (len << 1));
        w[len] = 1;
        for (int i = 1; i < len; i++) w[i + len] = (ll)w[i + len - 1] * wn % mod;
    }
    for (int i = 0; i < n; i++) t[i] = s[i] == '?' ? 0 : (s[i] == '0' ? 2 : 1);
    for (int i = 0; i < n; i++) a[i] = t[i] * t[i], b[n - i - 1] = t[i] * t[i];
    calc(a, b, g);
    // for (int i = 0; i < n; i++) print(g[i], " \n"[i == n - 1]);
    for (int i = 0; i < n; i++) f[i] = 2ll * (mod - g[i]) % mod;
    memset(a, 0, sizeof(a)), memset(b, 0, sizeof(b)), memset(b, 0, sizeof(g));
    for (int i = 0; i < n; i++) a[i] = t[i] * t[i] * t[i], b[n - i - 1] = t[i];
    calc(a, b, g);
    // for (int i = 0; i < n; i++) print(g[i], " \n"[i == n - 1]);
    for (int i = 0; i < n; i++) f[i] = (f[i] + g[i]) % mod;
    memset(a, 0, sizeof(a)), memset(b, 0, sizeof(b)), memset(b, 0, sizeof(g));
    for (int i = 0; i < n; i++) a[i] = t[i], b[n - i - 1] = t[i] * t[i] * t[i];
    calc(a, b, g);
    // for (int i = 0; i < n; i++) print(g[i], " \n"[i == n - 1]);
    for (int i = 0; i < n; i++) f[i] = (f[i] + g[i]) % mod;
    // for (int i = 0; i < n; i++) print(f[i], " \n"[i == n - 1]);
    for (int i = 1, flag; i < n; i++) {
        flag = 1;
        for (int j = i; j < n && flag; j += i) flag &= !f[n - j - 1];
        // printf(">>> %d %d : %d\n", n - i, i, flag);
        if (flag)
            ans ^= (ll)(n - i) * (n - i);
        // if (flag) printf(">> "), print(n - i, '\n');
    }
    ans ^= (ll)n * n;
    print(ans, '\n');
}

}  // namespace ringo
signed main() { return ringo::main(), 0; }