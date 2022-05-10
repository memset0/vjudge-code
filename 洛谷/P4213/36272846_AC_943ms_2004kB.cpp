// luogu-judger-enable-o2
// luogu-judger-enable-o2
// =================================
//   author: memset0
//   date: 2019.01.18 19:38:19
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

const int N = 1e5 + 10;
int T, n, cnt, sqn, pri, prime[N], a[N], h[N], sum[N];
ll g[N];

inline int id(int x) { return x <= sqn ? x : cnt - (n / x) + 1; }

ll solvePhi(int a, int b) {
    if (a <= 1 || a < prime[b]) return 0;
    ll ans = g[id(a)] - h[id(a)] - g[id(prime[b - 1])] + h[id(prime[b - 1])];
    for (int i = b; i <= pri && prime[i] * prime[i] <= a; i++) {
        int x = prime[i]; ll f = x - 1, nxt = x * f;
        for (; (ll)x * prime[i] <= a; x *= prime[i], f = nxt, nxt *= prime[i])
            ans += f * solvePhi(a / x, i + 1) + nxt;
    } return ans;
}

int solveMu(int a, int b) {
    if (a <= 1 || a < prime[b]) return 0;
    int ans = -h[id(a)] + b - 1;
    for (int i = b; i <= pri && prime[i] * prime[i] <= a; i++)
        ans -= solveMu(a / prime[i], i + 1);
    return ans;
}

void solve(int n) {
    sqn = sqrt(n);
    for (int i = 1; i <= n; i = a[cnt] + 1) a[++cnt] = n / (n / i);
    for (int i = 1; i <= cnt; i++) {
        g[i] = (ll)a[i] * (a[i] + 1) / 2 - 1;
        h[i] = a[i] - 1;
    }
    for (int i = 2; i <= sqn; i++) if (h[i] != h[i - 1]) {
        prime[++pri] = i, sum[pri] = sum[pri - 1] + i;
        for (int j = cnt, sqr = i * i; a[j] >= sqr; j--) {
            g[j] -= (ll)i * (g[id(a[j] / i)] - sum[pri - 1]);
            h[j] -= h[id(a[j] / i)] - pri + 1;
        }
    }
    // for (int i = 1; i <= cnt; i++) print(a[i], " \n"[i == cnt]);
    // for (int i = 1; i <= cnt; i++) print(g[i], " \n"[i == cnt]);
    // for (int i = 1; i <= cnt; i++) print(h[i], " \n"[i == cnt]);
    // for (int i = 1; i <= pri; i++) print(prime[i], " \n"[i == pri]);
    print(solvePhi(n, 1) + 1, ' '), print(solveMu(n, 1) + 1, '\n');
}

void main() {
    for (read(T); T--; ) {
        pri = cnt = 0;
        read(n), solve(n);
    }
}

} signed main() { return ringo::main(), 0; }