// luogu-judger-enable-o2
// luogu-judger-enable-o2
// =================================
//   author: memset0
//   date: 2018.12.16 16:21:24
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

const int N = 1e6 + 10, M = 16777217, p = 1e9 + 7;
int n, m, k, ans;
int phi[M], pri[M / 10];

int lcm(int a, int b) {
    return a / std::__gcd(a, b) * b;
}

void dfs(int u, int now) {
    if (u == k) {
        // printf(">> %d %d\n", now, phi[now]);
        ans = (ll)ans * phi[now] % p;
        return;
    }
    for (int i = 1; i <= n; i++) {
        dfs(u + 1, lcm(now, i));
    }
}

void init(int m) {
    phi[1] = 1;
    for (int i = 2; i <= m; i++) {
        if (!phi[i]) {
            phi[i] = i - 1;
            pri[++pri[0]] = i;
        }
        for (int j = 1; j <= pri[0] && i * pri[j] <= m; j++) {
            if (i % pri[j] == 0) {
                phi[i * pri[j]] = phi[i] * pri[j];
                break;
            } else {
                phi[i * pri[j]] = phi[i] * (pri[j] - 1);
            }
        }
    }
}

int solve(int n, int k) {
    ans = 1;
    for (int i = 1; i <= n; i++)
        dfs(1, i);
    return ans;
}

void main() {
    read(n), read(k);
    if (n > 8) return;
    m = 1;
    for (int i = 1; i <= k; i++) m *= n;
    init(m);
	print(solve(n, k), '\n');
	// for (int i = 1; i <= 8; i++) {
	// 	for (int j = 1; j <= 8; j++)
	// 		print(solve(i, j), ' ');
	// 	puts("");
	// }
}

} signed main() { return ringo::main(), 0; }