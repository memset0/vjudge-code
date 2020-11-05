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

const int maxn = 50010;

int n, l, r, L;
int a[maxn], q[maxn];
ll f[maxn], sum[maxn];

inline ll sqr(ll x) { return x * x; }
inline ll g(int i) { return sum[i] + i - L - 1; }
inline ll h(int i) { return sum[i] + i; }
inline ll x(int i) { return h(i); }
inline ll y(int i) { return f[i] + sqr(h(i)); }
inline ll slope(int i, int j) { return (y(j) - y(i)) / (x(j) - x(i)); }

int main() {
    // freopen("1.in", "r", stdin);

    read(n), read(L);
    for (int i = 1; i <= n; i++) {
        read(a[i]);
        sum[i] = sum[i - 1] + a[i];        
    }
    l = r = 1, q[1] = 0;
    for (int i = 1; i <= n; i++) {
        while (l < r && slope(q[l], q[l + 1]) < 2 * g(i)) l++;
        f[i] = f[q[l]] + sqr(g(i) - h(q[l]));
        while (l < r && slope(q[r - 1], q[r]) > slope(q[r], i)) r--;
        q[++r] = i;
    }
    print(f[n], '\n');

    return 0;
}