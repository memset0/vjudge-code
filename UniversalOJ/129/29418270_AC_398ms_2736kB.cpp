// =================================
//   author: memset0
//   date: 2019.05.07 13:02:08
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
template <class T> inline void print(T a, int l, int r, std::string s = "") {
    if (s != "") std::cout << s << ": ";
    for (int i = l; i <= r; i++) print(a[i], " \n"[i == r]);
}

const int N = 510, M = 1 << 8;
const int pri[] = {2, 3, 5, 7, 11, 13, 17, 19};
int n, cnt, ord;
std::vector<int> s[N];
std::map<int, int> map;
ll ans, mod, f[M][M], g[M][M], dp[M][M];

template <class T> inline T dec(T a, T b) {
    a -= b; return a < 0 ? a + mod : a;
}
template <class T> inline T inc(T a, T b) {
    a += b; return a >= mod ? a - mod : a;
}
template <class T> inline void incTo(T &a, T b) {
    a += b; if (a >= mod) a -= mod;
}

void main() {
    read(n), read(mod);
    for (int x = 2; x <= n; x++) {
        int t = x, y = 0;
        for (int i = 0; i < 8; i++)
            if (x % pri[i] == 0) {
                while (t % pri[i] == 0) t /= pri[i];
                y |= 1 << i;
            }
        if (t == 1) {
            s[0].push_back(y);
        } else {
            int ord = map[t] ? map[t] : (map[t] = ++cnt);
            s[ord].push_back(y);
        }
        // printf("%d : %d %d\n", x, y, t);
    }
    dp[0][0] = 1;
    for (int i = 0; i < s[0].size(); i++)
        for (int x = (1 << 8) - 1; ~x; x--)
            for (int y = (1 << 8) - 1; ~y; y--) {
                if ((y & s[0][i]) == 0) incTo(dp[x | s[0][i]][y], dp[x][y]);
                if ((x & s[0][i]) == 0) incTo(dp[x][y | s[0][i]], dp[x][y]);
            }
    for (int k = 1; k <= cnt; k++) {
        for (int x = 0; x < (1 << 8); x++)
            for (int y = 0; y < (1 << 8); y++)
                f[x][y] = g[x][y] = dp[x][y];
        for (int i = 0; i < s[k].size(); i++)
            for (int x = (1 << 8) - 1; ~x; x--)
                for (int y = (1 << 8) - 1; ~y; y--) {
                    if ((y & s[k][i]) == 0) incTo(f[x | s[k][i]][y], f[x][y]);
                    if ((x & s[k][i]) == 0) incTo(g[x][y | s[k][i]], g[x][y]);
                }
        for (int x = 0; x < (1 << 8); x++)
            for (int y = 0; y < (1 << 8); y++)
                dp[x][y] = dec(inc(f[x][y], g[x][y]), dp[x][y]);
    }
    for (int x = 0; x < (1 << 8); x++)
        for (int y = 0; y < (1 << 8); y++) {
                incTo(ans, dp[x][y]);
                // if (dp[x][y]) printf("[%d %d] -> %lld\n", x, y, dp[x][y]);
            }
    print(ans, '\n');
}

} signed main() {
#ifdef MEMSET0_LOCAL_ENVIRONMENT
    freopen("1.in", "r", stdin);
#endif
    return ringo::main(), 0;
}

/*

sol:

显然要把每个数分解质因数，我们根据质因数与 $L = \sqrt{500} \approx 22$ 的大小分类讨论。

给每个小于 $L$ 的数状压，由于只需要知道是否有这个质因子而不关心质因子的大小，而小于 $L$ 的质数又只有 $2,3,5,7,11,13,17,19$ 这 $8$ 个，可以用一个 $2^8$ 的数来表示。

给每个大于 $L$ 的数开个桶，同一个桶里的数要么被 G 选要么被 W 选要么不选。桶里面放这个数小于 $L$ 的因子状压完的值。

用 $f[i][S][T]$ 表示枚举到第 $i$ 个桶，G 选择的质因子的表示为 $S$，W 选择的质因子的表示为 $T$ 的方案数，因为总共只有 $n \leq 500$ 个数，可以暴力的转移。总时间复杂度 $\mathcal O(n \times 2^{16})$。

*/