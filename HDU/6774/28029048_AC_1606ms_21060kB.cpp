#include <bits/stdc++.h>
#define rep(i, a, b) for (int i = a; i <= b; i++)
#define per(i, a, b) for (int i = a; i >= b; i--)
using namespace std;
 
typedef unsigned long long ull;
typedef pair <int, int> pii;
typedef long long ll;

template <typename _T>
inline void read(_T &f) {
    f = 0; _T fu = 1; char c = getchar();
    while (c < '0' || c > '9') { if (c == '-') { fu = -1; } c = getchar(); }
    while (c >= '0' && c <= '9') { f = (f << 3) + (f << 1) + (c & 15); c = getchar(); }
    f *= fu;
}

template <typename T>
void print(T x) {
    if (x < 0) putchar('-'), x = -x;
    if (x < 10) putchar(x + 48);
    else print(x / 10), putchar(x % 10 + 48);
}

template <typename T>
void print(T x, char t) {
    print(x); putchar(t);
}

const int N = 1e5 + 5;

char a[N], b[N];
int f[N][25], mx[N][25], maxn[25];
int T, n, m, q;

int main() {
    read(T);
    while (T--) {
        memset(f, 0, sizeof(f)); memset(mx, 0, sizeof(mx));
        scanf("%s%s", a + 1, b + 1);
        n = strlen(a + 1); m = strlen(b + 1);
        for (int i = 1; i <= m; i++) {
            for (int j = 1; j <= n; j++) {
                if (a[j] == b[i]) {
                    f[j][1] = j;
                    for (int k = 2; k <= m; k++) f[j][k] = max(f[j][k], mx[j - 1][k - 1]);
                }
                for (int k = 1; k <= m; k++) f[j][k] = max(f[j][k], f[j - 1][k]);
            }
            memset(maxn, 0, sizeof(maxn));
            for (int j = 1; j <= n; j++) {
                for (int k = 1; k <= m; k++) {
                    maxn[k] = max(maxn[k], f[j][k]);
                    mx[j][k] = max(mx[j][k], maxn[k]);
                }
            }
        }
        read(q);
        while (q--) {
            int l, r, ans = 0;
            read(l); read(r);
            for (int i = m; i >= 1; i--) {
                if (f[r][i] >= l) {
                    ans = i;
                    break;
                }
            }
            print(r - l + 1 + m - 2 * ans, '\n');
        }
    }
    return 0;
}