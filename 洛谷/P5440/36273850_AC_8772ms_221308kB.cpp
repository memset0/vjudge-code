// luogu-judger-enable-o2
// =================================
//   author: memset0
//   date: 2019.06.29 15:45:34
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

const int N = 1e8 + 5, M = 7e6 + 10;
char str[10];
bool f[N], vis[N];
int T, ans, tot, pri[M];
int day[13] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

void dfs(int dep, int x) {
    if (dep == 7 && (x % 100 == 0 || x % 100 >= 13)) return;
    if (dep == 9) { ans += f[x]; return; }
    if (str[dep] == '-') {
        for (int i = 0; i <= 9; i++) dfs(dep + 1, x * 10 + i);
    } else {
        dfs(dep + 1, x * 10 + str[dep] - '0');
    }
}

void main() {
    vis[0] = vis[1] = 1;
    for (int i = 2; i < N; i++) {
        if (!vis[i]) pri[++tot] = i;
        for (int j = 1, k; j <= tot && i * pri[j] < N; j++) {
            vis[i * pri[j]] = true;
            if (i % pri[j] == 0) break;
        }
    }
    for (int x = 1; x < 10000; x++)
        for (int y = 1; y <= 12; y++)
            for (int z = 1; z < 40; z++)
                if (!vis[x * 10000 + y * 100 + z] && !vis[y * 100 + z] && !vis[z]) {
                    if ((!(x % 4) && x % 100) || !(x % 400)) day[2]++;
                    if (z <= day[y]) f[x * 10000 + y * 100 + z] = true;
                    if ((!(x % 4) && x % 100) || !(x % 400)) day[2]--;
                }
    for (scanf("%d", &T); T; T--, ans = 0) {
        scanf("%s", str + 1);
        dfs(1, 0);
        print(ans, '\n');
    }
}

} signed main() {
#ifdef MEMSET0_LOCAL_ENVIRONMENT
	freopen("1.in", "r", stdin);
#endif
    ringo::main();
    std::cerr << "clock: " << clock() / (double)CLOCKS_PER_SEC << std::endl;
	return 0;
}