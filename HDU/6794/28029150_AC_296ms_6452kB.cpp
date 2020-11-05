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

const int N = 1e6 + 5;

ll s[N];
int used[N], a[N];
int T, n, p, ans;

int main() {
    read(T);
    while (T--) {
        memset(used, 0, sizeof(used));
        read(n); read(p); ans = 0;
        for (int i = 1; i <= n; i++) read(a[i]), s[i] = s[i - 1] + a[i];
        for (int l = 1, r; l <= n; l = r + 1) {
            used[s[l - 1] % p] = 1;
            r = l;
            while (r <= n) {
                if (used[s[r] % p]) {
                    ++ans;
                    for (int i = l - 1; i < r; i++) used[s[i] % p] = 0;
                    break;
                }
                used[s[r] % p] = 1; ++r;
            }
        }
        print(ans, '\n');
    }
    return 0;
}