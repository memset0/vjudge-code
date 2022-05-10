// luogu-judger-enable-o2
// =================================
//   author: memset0
//   date: 2019.02.11 19:50:54
//   website: https://memset0.cn/
// =================================
#include <bits/stdc++.h>
#define ll long long
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

const int mod = 1e9 + 7;
int T, n, ans;

inline int fpow(int a, int b) {
    int s = 1;
    for (; b; b >>= 1, a = (ll)a * a % mod)
        if (b & 1) s = (ll)s * a % mod;
    return s;
}

inline int phi(int x) {
    // printf("phi %d = ", x);
    int ans = 1;
    for (int i = 2; i * i <= x; i++)
        if (x % i == 0) {
            ans *= i - 1, x /= i;
            while (x % i == 0) x /= i, ans *= i;
        }
    if (x != 1) ans *= x - 1;
    // printf("%d\n", ans);
    return ans;
}

void main() {
    for (read(T); T--; ) {
        read(n), ans = 0;
        for (int i = 1; i * i <= n; i++)
            if (n % i == 0) {
                ans = (ans + (ll)fpow(n, i) * phi(n / i)) % mod;
                if (i * i != n) ans = (ans + (ll)fpow(n, n / i) * phi(i)) % mod;
            }
        print((ll)ans * fpow(n, mod - 2) % mod, '\n');
    }
}

} signed main() { return ringo::main(), 0; }