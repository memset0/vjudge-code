// luogu-judger-enable-o2
// luogu-judger-enable-o2
// ==============================
//  author: memset0
//  website: https://memset0.cn
// ==============================
#include <bits/stdc++.h>
#define ll long long
#define rep(i,l,r) for (int i = l; i <= r; i++)
#define getc(x) getchar(x)
#define putc(x) putchar(x)

template <typename T> inline void read(T &x) {
    x = 0; register char ch; register bool fl = 0;
    while (ch = getc(), ch < 48 || 57 < ch) fl ^= ch == '-'; x = (ch & 15);
    while (ch = getc(), 47 < ch && ch < 58) x = (x << 1) + (x << 3) + (ch & 15);
    if (fl) x = -x;
}
template <typename T> inline void readc(T &x) {
    while (x = getc(), !islower(x) && !isupper(x));
}
template <typename T> inline void print(T x, char c = ' ') {
    static int buf[40];
    if (x == 0) { putc('0'); putc(c); return; }
    if (x < 0) putc('-'), x = -x;
    for (buf[0] = 0; x; x /= 10) buf[++buf[0]] = x % 10 + 48;
    while (buf[0]) putc((char) buf[buf[0]--]);
    putc(c);
}

using std::vector;

const int maxn = 22, maxm = 100010;
const int mod = 998244353;

int n, m, x, u, now, ans;
int f[maxn], c[maxn][maxn];

struct status {
    int x, v;
} a[maxm];

int main() {

    read(n), read(m);
    for (int i = 1; i <= m; i++) {
        u = 0; char c;
        while (c = getc(), !isdigit(c));
        while (isdigit(c)) u = u << 1 | (c - '0'), c = getc();
        read(x);
        a[i].x = u, a[i].v = x;
    }
    for (int i = 0; i <= n; i++) {
        c[i][0] = 1;
        for (int j = 1; j <= i; j++)
            c[i][j] = (c[i - 1][j - 1] + c[i - 1][j]) % mod;
    }
    f[0] = 1;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= i; j++)
            f[i] = (f[i] + 1ll * f[i - j] * c[i][j]) % mod;
    for (int i = 1; i <= m; i++) {
        now = __builtin_popcount(a[i].x);
        ans = (ans + 1ll * f[now] * f[n - now] % mod * a[i].v % mod) % mod;
    }
    print(ans, '\n');

    return 0;
}