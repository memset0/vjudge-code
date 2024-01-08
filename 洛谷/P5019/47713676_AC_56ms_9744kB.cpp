// luogu-judger-enable-o2
#include <bits/stdc++.h>
#define il inline
#define rg register
#define ll long long
#define getc getchar
#define putc putchar
#define rep(i,l,r) for (register int i = l; i <= r; ++i)
namespace ringo {

template < class T >
il void read(T &x) {
    x = 0; rg char c = getc(); rg bool f = 0;
    while (!isdigit(c)) f ^= c == '-', c = getc();
    while (isdigit(c)) x = x * 10 + c - '0', c = getc();
    if (f) x = -x;
}

template < class T >
il void print(T x) {
    if (x < 0) putc('-'), x = -x;
    if (x > 9) print(x / 10);
    putc(x % 10 + '0');
}

const int maxn = 100010, inf = 10010;
int n, ans;
int a[maxn], lg2[maxn], f[maxn][20];

int min_a(int l, int r) {
    if (a[l] < a[r]) return l;
    else return r;
}

void solve(int l, int r, int dep) {
    if (l > r) return;
    if (l == r) {
        ans += a[l] - dep;
        return;
    }
    int lg = lg2[r - l];
    int loc = min_a(f[l][lg], f[std::max(r - (1 << lg), l)][lg]);
//	printf("solve %d %d %d => %d %d %d\n", l, r, dep, loc, lg, r - (1 << lg));
    ans += a[loc] - dep;
    solve(l, loc - 1, a[loc]);
    solve(loc + 1, r, a[loc]);
}

void main() {
//	freopen("3.txt", "r", stdin);
    
    read(n); rep(i, 1, n) read(a[i]);
    a[n + 1] = inf;
    for (int i = 1; i <= 20; i++)
        if ((1 << i) <= n)
            lg2[1 << i] = i;
    for (int i = 1; i <= n; i++)
        if (!lg2[i])
            lg2[i] = lg2[i - 1];
    for (int i = 1; i <= n; i++)
        f[i][0] = a[i] < a[i + 1] ? i : i + 1;
    for (int i = 1, l, r; i < 20; i++)
        for (int j = 1; j <= n; j++) {
            l = f[j][i - 1];
            r = f[std::min(j + (1 << (i - 1)), n)][i - 1];
            f[j][i] = a[l] < a[r] ? l : r;
        }
//	for (int i = 0; i < 20; i++) {
//		for (int j = 1; j <= n; j++)
//			printf("%d ", f[j][i]);
//		puts("");
//	}
    solve(1, n, 0);
    print(ans), putc('\n');
}
    
} int main() { return ringo::main(), 0; }

