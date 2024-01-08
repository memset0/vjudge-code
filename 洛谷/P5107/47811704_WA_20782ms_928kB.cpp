// luogu-judger-enable-o2
// luogu-judger-enable-o2
// =================================
//   author: memset0
//   date: 2018.12.16 16:36:37
//   website: https://memset0.cn/
// =================================
#include <bits/stdc++.h>
namespace ringo {
typedef long long ll;

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
template <class T> inline void maxd(T &a, T b) { if (b > a) a = b; }
template <class T> inline void mind(T &a, T b) { if (b < a) a = b; }
template <class T> inline void print(T x, char c) { print(x), putchar(c); }
template <class T> inline T abs(const T &a) { if (a < 0) return -a; return a; }

const int N = 55, M = 2510, Q = 5e4 + 10, p = 998244353;
int n, m, u, v, q, x, limit, final_ans;
int a[N], b[N], siz[N], qry[Q];
int tot = 2, hed[N], to[M], nxt[M];

template <class T> inline void sumd(int &a, T b) { a = (a + b) % p; }

struct edge {
    int u, v;
} e[M];

struct matrix {
    int a[N][N];
    void print() {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++)
                ringo::print(a[i][j], " \n"[j == n - 1]);
        }
    }
 } orga, base, temp, ans;

inline matrix operator * (const matrix &a, const matrix &b) {
    matrix c; memset(c.a, 0, sizeof(c.a));
    for (int k = 0; k < n; k++)
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                c.a[i][j] = (c.a[i][j] + (ll)a.a[i][k] * b.a[k][j]) % p;
    return c;
}

inline int inv(int x) {
    if (!x || x == 1) return 1;
    return (ll)(p - p / x) * inv(p % x) % p;
}

inline void fpow(matrix a, int b, matrix &s) {
    s = a, --b;
    while (b) {
        if (b & 1) s = s * a;
        b >>= 1, a = a * a;
    }
}

void main() {
    read(n), read(m), read(q);
    for (int i = 1; i <= n; i++) read(a[i]), siz[i] = 1;
    for (int i = 1; i <= m; i++) {
        read(u), read(v);
        e[i] = (edge){u, v}, ++siz[u];
    }
    for (int i = 1; i <= n; i++) siz[i] = inv(siz[i]);
    for (int i = 1; i <= n; i++) orga.a[i - 1][0] = a[i];
    for (int i = 1; i <= n; i++) base.a[i - 1][i - 1] = siz[i];
    for (int i = 1; i <= m; i++) {
        u = e[i].u, v = e[i].v;
        sumd(base.a[u - 1][v - 1], siz[u]);
    }
    orga.print();
    for (int i = 1; i <= q; i++) {
        puts("=============");
        read(x);
        fpow(base, x, ans);
        ans.print();
        ans = orga * ans;
        ans.print();
        final_ans = 0;
        for (int i = 1; i <= n; i++)
            final_ans ^= ans.a[0][i - 1];
        print(final_ans % p, '\n');
    }
}

} signed main() { return ringo::main(), 0; }