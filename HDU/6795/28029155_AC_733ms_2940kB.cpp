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

const int N = 1e5 + 5, md = 1e9 + 7;

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

int a[N], f[N], x[N], y[N];
int T, n, sx, sy, sxy, syy, ans;

int find(int x) { return f[x] == x ? x : f[x] = find(f[x]); }

void add(int id) {
    ans = add(ans, mul(syy, add(x[id], y[id])));
    ans = add(ans, mul(sxy, y[id]));
    sxy = add(sxy, add(mul(x[id], sy), mul(y[id], sx)));
    syy = add(syy, mul(y[id], sy));
    sx = add(sx, x[id]);
    sy = add(sy, y[id]);
}

void del(int id) {
    sx = sub(sx, x[id]);
    sy = sub(sy, y[id]);
    sxy = sub(sxy, add(mul(x[id], sy), mul(y[id], sx)));
    syy = sub(syy, mul(y[id], sy));
    ans = sub(ans, mul(syy, add(x[id], y[id])));
    ans = sub(ans, mul(sxy, y[id]));
}

int main() {
    read(T);
    while (T--) {
        read(n); sx = sy = sxy = syy = ans = 0;
        for (int i = 1; i <= n; i++) {
            read(a[i]); f[i] = i;
            if (a[i] ==    1) x[i] = 1, y[i] = 0;
            if (a[i] == 2) x[i] = 0, y[i] = 1;
        }
        for (int i = 1; i <= n; i++) add(i);
        print(ans, '\n');
        for (int i = 1; i < n; i++) {
            int x, y;
            read(x); read(y);
            x = find(x); y = find(y);
            del(x); del(y);
            ::x[y] += ::x[x]; ::y[y] += ::y[x];
            f[x] = y; add(y);
            print(ans, '\n');
        }
    }
    return 0;
}