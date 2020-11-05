#pragma GCC optimize(2)
#pragma GCC optimize(3)
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

std::mt19937 rng(20050108 ^ std::chrono::steady_clock::now().time_since_epoch().count());
template <class T> inline T rand(T l, T r) { return std::uniform_int_distribution <T> (l,r)(rng);}


const int N = 405, md = 1e9 + 7, INF = 0x7fffffff;

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

set <int> wxw;
pii s1[N][N], s2[N][N];
int lc[N * N * 60], rc[N * N * 60]; ull sum[N * N * 60];
int a[N][N], rt1[N][N], rt2[N][N], rt3[N][N], ans1[N][N], ans2[N][N], ans3[N][N], val[N * N], pw[N * N];
int T, n, q, tot;

void ins(int &u, int pre, int l, int r, int x, int y) {
    u = ++tot; lc[u] = lc[pre]; rc[u] = rc[pre]; sum[u] = sum[pre] + val[x] * y;
    if (l == r) return;
    int mid = (l + r) >> 1;
    if (mid >= x) ins(lc[u], lc[pre], l, mid, x, y);
    else ins(rc[u], rc[pre], mid + 1, r, x, y);
}

int query(int rt1, int rt2, int rt3, int rt4, int l, int r) {
    if (l == r) return (sum[rt1] + sum[rt2]) < (sum[rt3] + sum[rt4]);
    int mid = (l + r) >> 1;
    if (sum[rc[rt1]] + sum[rc[rt2]] != sum[rc[rt3]] + sum[rc[rt4]]) return query(rc[rt1], rc[rt2], rc[rt3], rc[rt4], mid + 1, r);
    return query(lc[rt1], lc[rt2], lc[rt3], lc[rt4], l, mid);
}

bool get(pii a, pii b) { return query(rt1[a.first][a.second], rt3[a.first][a.second], rt1[b.first][b.second], rt3[b.first][b.second], 1, n * n); }

pii getpii(pii a, pii b) { return get(a, b) ? b : a; }

int main() {
    read(T);
    while (T--) {
        memset(lc, 0, sizeof(lc)); memset(rc, 0, sizeof(rc)); memset(sum, 0, sizeof(sum)); memset(ans1, 0, sizeof(ans1)); memset(ans2, 0, sizeof(ans2)); memset(rt1, 0, sizeof(rt1)); memset(rt2, 0, sizeof(rt2)); memset(rt3, 0, sizeof(rt3)); tot = 0;
        read(n); read(q);
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= n; j++) {
                read(a[i][j]);
                // a[i][j] = rand(1, 160000);
            }
        }
        pw[0] = 1;
        for (int i = 1; i <= n * n; i++) pw[i] = mul(pw[i - 1], n * n);
        // cout << pw[6] + pw[1] + pw[5] + pw[6] + pw[7] << endl;
        // cout << pw[7] + pw[5] + pw[7] + pw[6] + pw[5] << endl;
        wxw.clear();
        for (int i = 1; i <= n * n; i++) {
            int x = rand(1, INF);
            while (wxw.count(x)) x = rand(1, INF);
            val[i] = x; wxw.insert(x);
        }
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= n; j++) {
                int opt = query(rt1[i - 1][j], 0, rt1[i][j - 1], 0, 1, n * n);
                if (opt == 0) ans1[i][j] = add(ans1[i - 1][j], pw[a[i][j]]), ins(rt1[i][j], rt1[i - 1][j], 1, n * n, a[i][j], 1);
                else ans1[i][j] = add(ans1[i][j - 1], pw[a[i][j]]), ins(rt1[i][j], rt1[i][j - 1], 1, n * n, a[i][j], 1);
            }
        }
        for (int i = n; i >= 1; i--) {
            for (int j = n; j >= 1; j--) {
                int opt = query(rt2[i + 1][j], 0, rt2[i][j + 1], 0, 1, n * n);
                // if (i == 3 && j == 3) cout << pw[7] << endl;
                if (opt == 0) ans2[i][j] = add(ans2[i + 1][j], pw[a[i][j]]), ins(rt2[i][j], rt2[i + 1][j], 1, n * n, a[i][j], 1);
                else ans2[i][j] = add(ans2[i][j + 1], pw[a[i][j]]), ins(rt2[i][j], rt2[i][j + 1], 1, n * n, a[i][j], 1);
            }
        }
        // cerr << "ok" << endl;
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= n; j++) {
                ins(rt3[i][j], rt2[i][j], 1, n * n, a[i][j], -1);
                ans3[i][j] = sub(add(ans1[i][j], ans2[i][j]), pw[a[i][j]]);
                // fprintf(stderr, "{%d, %d} : %d %d %d %d\n", i, j, ans1[i][j], ans2[i][j], ans3[i][j], a[i][j]);
            }
        }
        for (int i = 0; i <= n + 1; i++) {
            for (int j = 0; j <= n + 1; j++) s1[i][j] = s2[i][j] = make_pair(0, 0);
        }
        for (int i = 1; i <= n; i++) {
            for (int j = n; j >= 1; j--) {
                s1[i][j] = make_pair(i, j);
                if (i != 1 && get(s1[i][j], s1[i - 1][j])) s1[i][j] = s1[i - 1][j];
                if (j != n && get(s1[i][j], s1[i][j + 1])) s1[i][j] = s1[i][j + 1];
            }
        }
        for (int i = n; i >= 1; i--) {
            for (int j = 1; j <= n; j++) {
                s2[i][j] = make_pair(i, j);
                if (i != n && get(s2[i][j], s2[i + 1][j])) s2[i][j] = s2[i + 1][j];
                if (j != 1 && get(s2[i][j], s2[i][j - 1])) s2[i][j] = s2[i][j - 1];
            }
        }
        while (q--) {
            int xl, xr, yl, yr;
            read(xl); read(xr); read(yl); read(yr);
            pii res = getpii(s1[xl - 1][yr + 1], s2[xr + 1][yl - 1]);
            print(ans3[res.first][res.second], '\n');
        }
    }
    return 0;
}