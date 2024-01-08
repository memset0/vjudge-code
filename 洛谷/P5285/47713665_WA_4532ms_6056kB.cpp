// luogu-judger-enable-o2
// =================================
//   author: memset0
//   date: 2019.04.10 08:24:58
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

std::string opt;

inline int mul(int a, int b, int p) { return (ll)a * b - (ll)a * b / p * p; }

inline int fpow(int a, int b, int p) { 
    int s = 1;
    for (; b; b >>= 1, a = mul(a, a, p))
        if (b & 1) s = mul(s, a, p);
    return s;
}

inline void read_with_mod(int &x, int mod) {
    x = 0; register char c = getchar(); register bool f = 0;
    while (!isdigit(c)) f ^= c == '-', c = getchar();
    while (isdigit(c)) x = ((ll)x * 10 + c - '0') % mod, c = getchar();
    if (f) x = x == 0 ? 0 : mod - x;
}

void test() { // test
    int n; __int128 x, max = 0;
    read(n);
    for (int i = 1; i <= n; i++)
        read(x), max = std::max(max, x);
    print(max, '\n');
}

void sol1() { // 1_998244353
    static const int mod = 998244353;
    int n, x;
    read(n);
    for (int i = 1; i <= n; i++) {
        read_with_mod(x, mod - 1);
        print(fpow(19, x, mod), '\n');
    }
}

void sol2() { // 1?
    static const int mod = 1145141;
    int n, x;
    read(n);
    for (int i = 1; i <= n; i++) {
        read_with_mod(x, mod - 1);
        print(fpow(19, x, mod), '\n');
    }
}

namespace space4 {
    const int mod = 998244353;
    void sol4() {
        int n, x, ans = 1;
        read(n);
        for (int i = 1; i <= n; i++) {
            read(x), print(ans, '\n');
            ans = ans * 19 % mod;
        }
    }
} using space4::sol4;

namespace space5 {
    const int limit = 1e6;
    int n, cnt, prime[limit / 10];
    bool vis[limit];
    void init() {
        for (int i = 2; i < limit; i++) {
            if (!vis[i]) prime[++cnt] = i;
            for (int j = 1; i * prime[j] < limit; j++) {
                vis[i * prime[j]] = 1;
                if (i % prime[j] == 0) break;
            }
        }
    }
    inline bool check(ll x) {
        if (x < limit) return vis[x] ^ 1;
        if (x % 2 == 0 || x % 3 == 0 || x % 5 == 0 || x % 7 == 0 || x % 11 == 0) return false;
        for (int i = 6; i < cnt && (ll)prime[i] * prime[i] <= x; i++)
            if (x % prime[i] == 0)
                return false;
        return true;
    }
    void sol5() { // 2p
        init(), read(n);
        ll l, r;
        for (int i = 1; i <= n; i++) {
            read(l), read(r);
            for (ll i = l; i <= r; i++) 
                putchar(check(i) ? 'p' : '.');
            putchar('\n');
        }
    }
} using space5::sol5;

namespace space6 {
    const int limit = 1e6 + 1;
    int n, l, r, cnt, mu[limit], prime[limit / 10];
    bool vis[limit];
    void sol6() { // 2u
        read(n);
        for (int i = 2; i < limit; i++) {
            if (!vis[i]) prime[++cnt] = i, mu[i] = -1;
            for (int j = 1; i * prime[j] < limit; j++) {
                vis[i * prime[j]] = 1;
                if (i % prime[j] == 0) break;
                else mu[i * prime[j]] = mu[i] * mu[prime[j]];
            }
        }
        for (int i = 1; i <= n; i++) {
            read(l), read(r);
            for (ll i = l; i <= r; i++) 
                putchar(mu[i] == 0 ? '0' : (mu[i] == 1 ? '+' : '-'));
            putchar('\n');
        }
    }
} using space6::sol6;

void main() {
    std::cin >> opt;
    if (opt == "test") return test();
    if (opt == "1_998244353") return sol1(); // AC
    if (opt == "1?") return sol2(); // AC
    // if (opt == "1?+") return sol3();
    if (opt == "1wa_998244353") return sol4();
    if (opt == "2p") return sol5(); // len = 1e6, r = 1e18, 1 / 3
    if (opt == "2u") return sol6(); // len = 1e6, r = 1e18, 1 / 3
    // if (opt == "2g") return sol7();
    // if (opt == "2g+") return sol8();
}

} signed main() {
#ifdef MEMSET0_LOCAL_ENVIRONMENT
    freopen("1.in", "r", stdin);
#endif
    ringo::main();
    std::cerr << clock() / (double)CLOCKS_PER_SEC << std::endl;
}