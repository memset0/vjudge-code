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

const int N = 1e6 + 5, MX = 1e6, md = 998244353, inv2 = (md + 1) >> 1;

inline int add(int x, int y) {
    x += y;
    if (x >= md) x -= md;
    return x;
}

inline int sub(int x, int y) {
    x -= y;
    if (x < 0) x += md;
    return x;
}

inline int mul(int x, int y) { return 1ll * x * y % md; }

inline int fpow(int x, int y) {
    int ans = 1;
    while (y) {
        if (y & 1) ans = mul(ans, x);
        y >>= 1; x = mul(x, x);
    }
    return ans;
}

int fac[N], inv[N], pw[N];
int T, x, y, z;

inline int C(int n, int m) {
    if (n < 0 || m < 0 || n < m) return 0;
    return mul(fac[n], mul(inv[m], inv[n - m]));
}

int main() {
    fac[0] = pw[0] = 1;
    for (int i = 1; i <= MX; i++) fac[i] = mul(fac[i - 1], i), pw[i] = mul(pw[i - 1], inv2);
    inv[MX] = fpow(fac[MX], md - 2);
    for (int i = MX; i >= 1; i--) inv[i - 1] = mul(inv[i], i);
    read(T);
    while (T--) {
        read(x); read(y); read(z);
        if ((x + y + z) % 3 != 0) {
            print(-1, '\n');
            continue;
        }
        if (x < y) swap(x, y);
        if (x < z) swap(x, z);
        if (y < z) swap(y, z);
        int ans = 0;
        for (int i = 0; i <= x - y; i++) {
            int now = x - i, cnty = now - y, cntz = now - z;
            if (0 <= cnty && cnty <= i && z + i - cnty <= now) {
                ans = add(ans, mul(mul(C(i, cnty), pw[i]), i + (now - (z + i - cnty)) / 3 * 4));
            }
            if (0 <= cntz && cntz <= i && y + i - cntz < now) {
                ans = add(ans, mul(mul(C(i, cntz), pw[i]), i + (now - (y + i - cntz)) / 3 * 4));
            }
            --cnty; --cntz;
            if (0 <= cnty && cnty <= i && z + i - cnty < now - 1) {
                ans = add(ans, mul(mul(C(i, cnty), pw[i + 1]), i + 3 + (now - 1 - (z + i - cnty)) / 3 * 4));
            }
            if (0 <= cntz && cntz <= i && y + i - cntz < now - 1) {
                ans = add(ans, mul(mul(C(i, cntz), pw[i + 1]), i + 3 + (now - 1 - (y + i - cntz)) / 3 * 4));
            }
        }
        print(ans, '\n');
    }
    return 0;
}