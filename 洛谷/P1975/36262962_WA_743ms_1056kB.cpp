// luogu-judger-enable-o2
// luogu-judger-enable-o2
// luogu-judger-enable-o2
// luogu-judger-enable-o2
// luogu-judger-enable-o2
// luogu-judger-enable-o2
// luogu-judger-enable-o2
// luogu-judger-enable-o2
#include <bits/stdc++.h>
namespace ringo {
typedef long long ll;

template < class T >
inline void read(T &x) {
    x = 0; register char c = getchar(); register bool f = 0;
    while (!isdigit(c)) f ^= c == '-', c = getchar();
    while (isdigit(c)) x = x * 10 + c - '0', c = getchar();
    if (f) x = -x;
}

template < class T >
inline void print(T x) {
    if (x < 0) putchar('-'), x = -x;
    if (x > 9) print(x / 10);
    putchar('0' + x % 10);
}

template < class T >
inline void print(T x, char c) {
    print(x), putchar(c);
}

const int N = 2e4 + 10, p = 1e9 + 7;
int n, m, i, l, r, b[N], f[N], g[N], x[N], y[N];
ll sl, sr, ans;

inline void add(int x, int y) {
    while (x) {
        f[x] += y, ++g[x];
        x -= x & -x;
    }
}
inline void ask(int x) {
    sl = sr = 0;
    while (x <= n) {
        sl += f[x], sr += g[x];
        x += x & -x;
    }
}

void main() {
    read(n);
    for (i = 1; i <= n; ++i) {
        read(x[i]), y[i] = 1;
        b[i] = x[i];
    }
    std::sort(b + 1, b + n + 1);
    int tn = std::unique(b + 1, b + n + 1) - b - 1;
    for (i = 1; i <= n; ++i)
        x[i] = std::lower_bound(b + 1, b + tn + 1, x[i]) - b;
    for (i = 1; i <= n; ++i) {
        ask(x[i]), add(x[i], y[i]);
        ans += sl + sr * y[i];
    }
    print(ans, '\n');
    read(m);
    while(m--) {
        read(l), read(r); if(l > r) std::swap(l, r);
        i = l + 1;
        while(i < r) {
            if (x[i] > x[l]) ans += y[i] + y[l];
            if (x[i] < x[r]) ans += y[i] + y[r];
            if (x[i] < x[l]) ans -= y[i] + y[l];
            if (x[i] > x[r]) ans -= y[i] + y[r];
            ++i;
        }
        if (x[l] > x[r]) ans -= y[l] + y[r];
        if (x[l] < x[r]) ans += y[l] + y[r];
        std::swap(x[l],x[r]), std::swap(y[l],y[r]);
        print(ans = (ans % p + p) % p, '\n');
    }
}

} signed main() { return ringo::main(), 0; }