// luogu-judger-enable-o2
// luogu-judger-enable-o2
// =================================
//   author: memset0
//   date: 2018.12.22 07:49:07
//   website: https://memset0.cn/
// =================================
#include <bits/stdc++.h>
#define rep(i, l, r) for (register int i = l; i <= r; i++)
namespace ringo {
typedef long long ll;
typedef unsigned long long ull;
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

namespace Mker {
    unsigned long long SA, SB, SC;
    void init() { scanf("%llu%llu%llu", &SA, &SB, &SC); }
    unsigned long long rand() {
        SA ^= SA << 32, SA ^= SA >> 13, SA ^= SA << 1;
        unsigned long long t = SA;
        SA = SB, SB = SC, SC ^= t ^ SA; return SC;
    }
}

const int K = 65536, P = 2, p = 1e9 + 7;
int T, sum;
unsigned long long x;

struct vector {
    int a, b;
} ans, temp;

struct matrix {
    int a, b, c, d;
} base, f[P][K];

inline matrix operator * (const matrix &a, const matrix &b) {
    matrix c;
    c.a = ((ll)a.a * b.a + (ll)a.b * b.c) % p;
    c.b = ((ll)a.a * b.b + (ll)a.b * b.d) % p;
    c.c = ((ll)a.c * b.a + (ll)a.d * b.c) % p;
    c.d = ((ll)a.c * b.b + (ll)a.d * b.d) % p;
    return c;
}

void main() {
    read(T), Mker::init();
    base.a = 233, base.c = 666, base.b = 1;
    for (register int p = 0; p < P; p++) {
        f[p][0].a = f[p][0].d = 1;
        for (int k = 1; k < K; k++) f[p][k] = f[p][k - 1] * base;
        base = base * f[p][K - 1];
    }
    for (register int i = 1; i <= T; i++) {
        x = Mker::rand() % (p - 1) - 1; if (x == -1) continue;
        // if (x < K) sum ^= f[0][x].a;
        // else {
            matrix A = f[0][x % K], B = f[1][x / K % K];
            sum ^= ((ll)A.a * B.a + (ll)A.b * B.c) % p;
        // }
    }
    print(sum, '\n');
}

} signed main() { return ringo::main(), 0; }
// 18446744073709551615