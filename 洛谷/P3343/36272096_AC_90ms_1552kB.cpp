// luogu-judger-enable-o2
// luogu-judger-enable-o2
// luogu-judger-enable-o2
// =================================
//   author: memset0
//   date: 2019.06.22 19:41:31
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
	x = 0; char c = getchar(); bool f = 0;
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

#define in(k, S) (((S) >> ((k) - 1)) & 1)
const int N = 20, M = 100, P = 1024;
int n, m;
double ans, inv[M], dp[P][M];
std::vector<int> G[N];
std::vector<std::pair<int, int>> E;

void main() {
    read(n), read(m);
    for (int i = 1, u, v; i <= m; i++) {
        read(u), read(v);
        E.push_back(std::make_pair(u, v));
        G[u].push_back(v), G[v].push_back(u);
    }
    for (int i = 0; i <= m; i++) inv[i] = 1 / (double)(i + 1);
    for (int S = 1; S < (1 << n); S += 2) {
        std::vector<int> bit;
        for (int i = 1; i <= n; i++)
            if (in(i, S))
                bit.push_back(i);
        for (int T_ = 1; T_ < (1 << bit.size()) - 1; T_ += 2) {
            int T = 0;
            for (int i = 0; i < bit.size(); i++)
                if (in(i + 1, T_))
                    T |= 1 << (bit[i] - 1);
            int cnt = 0;
            for (auto it : E)
                if (in(it.first, S) && in(it.second, S) && (in(it.first, T) + in(it.second, T) == 1))
                    ++cnt;
            // printf("S ");
            // for (int i = 1; i <= n; i++) print(in(i, S));
            // printf(" | T ");
            // for (int i = 1; i <= n; i++) print(in(i, T));
            // printf(" | T_ ");
            // for (int i = 1; i <= n; i++) print(in(i, T_));
            // printf(" => ");
            // for (int i = 1; i <= n; i++) if (in(i, T)) print(i, ' ');
            // printf("| ");
            // for (int i = 1; i <= n; i++) if (!in(i, T) && in(i, S)) print(i, ' ');
            // printf("=> %d\n", cnt);
            for (int k = 0; k + cnt <= m; k++)
                dp[S][k] += inv[k + cnt] - dp[T][k + cnt];
        }
        if (S != (1 << n) - 1) {
            int cnt = 0;
            for (auto it : E)
                if (in(it.first, S) + in(it.second, S) == 1)
                    ++cnt;
            ans += inv[cnt] - dp[S][cnt];
        }
    }
    // for (int S = 0; S < (1 << n); S++) {
    //     for (int i = 1; i <= n; i++)
    //         print(in(i, S));
    //     printf(" : ");
    //     for (int i = 0; i <= m; i++)
    //         printf("%.3lf%c", dp[S][i], " \n"[i == m]);
    // }
    printf("%.6lf\n", ans);
}

} signed main() {
#ifdef MEMSET0_LOCAL_ENVIRONMENT
	freopen("1.in", "r", stdin);
#endif
	return ringo::main(), 0;
}