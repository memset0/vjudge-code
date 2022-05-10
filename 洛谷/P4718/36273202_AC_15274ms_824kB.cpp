// luogu-judger-enable-o2
// luogu-judger-enable-o2
// luogu-judger-enable-o2
// luogu-judger-enable-o2
// =================================
//   author: memset0
//   date: 2018.12.08 18:07:46
//   website: https://memset0.cn/
// =================================
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

int T;
ll x, ans;

const int base[5] = {2, 3, 7, 61, 24251};

ll fpow(ll a, ll b, ll p) {
    ll s = 1;
    while (b) {
        if (b & 1) s = (__int128)s * a % p;
        b >>= 1, a = (__int128)a * a % p;
    }
    return s;
}

bool millerRabin(ll n) {
    for (int i = 0; i <= 4; i++) { if (n % base[i] == 0) { return n == base[i]; } }
    ll m = n - 1; int s = 0;
    while (!(m & 1)) { m >>= 1; s++; }
    for (int i = 0, j; i <= 4; i++) {
        ll x = fpow(base[i], m, n);
        printf("%d %lld\n", base[i], x);
        if (x == 1 || x == n - 1) { continue; }
        for (j = 1; j <= s; j++) {
            x = (__int128) x * x % n;
            if (x == n - 1) { break; }
        }
        if (j > s) { return false; }
    }
    return true;
}

bool is_prime(ll x) {
    if (x == 46856248255981 || x < 2) return false;
    if (x == 2 || x == 3 || x == 7 || x == 61 || x == 24251) return true;
    if (!(x % 2) || !(x % 3) || !(x % 7) || !(x % 61) || !(x % 24251)) return false;
    ll cnt = 0, lst = x - 1, r; bool flag;
    while (!(lst & 1)) ++cnt, lst >>= 1;
    for (int i = 0; i < 5; i++) {
        r = fpow(base[i], lst, x), flag = false;
        if (r == 1 || r == x - 1) continue;
        for (int j = 1; j <= cnt; j++) {
            r = (__int128)r * r % x;
            if (r == x - 1) { flag = true; break; }
        }
        if (!flag) return false;
    }
    return true;
}

ll prho(ll x) {
    // printf("prho %lld\n", x);
    ll a = rand() % x, b = a, c = rand() % (x - 1) + 1, g;
    for (int i = 1, j = 1; ; i++) {
        a = ((__int128)a * a + c) % x;
        if (a == b) return x;
        g = std::__gcd(std::abs(a - b), x);
        if (g != 1 && g != x) return g;
        if (i == j) b = a, j <<= 1;
    }
}

ll find(ll x) {
    if (x == 1) return 0;
    if (is_prime(x)) return x;
    ll t = x; while (t == x) t = prho(x);
    while (!(x % t)) x /= t;
    return std::max(find(x), find(t));
}

void main() {
    // printf("is_prime(%lld) = %d\n", 13ll, (int)is_prime(13));
    for (read(T); T--; ) {
        read(x);
        ans = find(x);
        if (ans == x) puts("Prime");
        else print(ans, '\n');
    }
}

} signed main() { return ringo::main(), 0; }