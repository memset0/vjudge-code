#include <bits/stdc++.h>
#define logvec(v)                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                      \
    cerr << #v << ": ";                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                \
    for (int i = 0; i < v.size(); i++)                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                 \
        cerr << v[i] << " \n"[i + 1 == v.size()];
#define all(x) begin(x), end(x)
using namespace std;
const int N = 2e5 + 9, K = 50, V = 1e6 + 9, mod = 998244353;
int n, t, a[N], fac[N], ifac[N], inv[N], f[N][K], g[N][K], h[K][K], dp[K];
bool vis[V];
long long m;
vector<int> pri;
vector<long long> uni;
vector<pair<long long, int>> p;

void upd(int &x, int y) {
    x += y;
    if (x >= mod) x -= mod;
}
int sub(int x, int y) {
    x -= y;
    return x < 0 ? x + mod : x;
}
int add(int x, int y) {
    x += y;
    return x >= mod ? x - mod : x;
}
int C(int n, int m) {
    if (n < m) return 0;
    return (long long)fac[n] * ifac[m] % mod * ifac[n - m] % mod;
}
int power(int a, int b) {
    int s = 1;
    for (; b; b >>= 1, a = (long long)a * a % mod)
        if (b & 1) s = (long long)s * a % mod;
    return s;
}

vector<pair<long long, int>> factor(long long x) {
    vector<pair<long long, int>> fac;
    for (int p : pri)
        if (x % p == 0) {
            fac.emplace_back(p, 0);
            while (x % p == 0) {
                x /= p;
                fac.back().second++;
            }
        }
    if (x > 1) fac.emplace_back(x, 1);
    return fac;
}
void dfs(int u, long long s) {
    if (u == p.size()) {
        uni.emplace_back(s);
        return;
    }
    for (int i = 0; i <= p[u].second; i++) {
        dfs(u + 1, s);
        s *= p[u].first;
    }
}

int find(long long x) {
    assert(x >= 1 && x <= m);
    int k = lower_bound(all(uni), x) - uni.begin();
    assert(x == uni[k]);
    return k;
}
vector<int> solve(int l, int r) {
    if (l == r) {
        return {1, a[l]};
    }
    int mid = (l + r) >> 1;
    vector<int> lv = solve(l, mid);
    vector<int> rv = solve(mid + 1, r);
    vector<int> v(min((size_t)K, lv.size() + rv.size() - 1));
    for (int i = 0; i < lv.size(); i++)
        for (int j = 0; j < rv.size() && i + j < v.size(); j++) {
            v[i + j] = (v[i + j] + (long long)lv[i] * rv[j]) % mod;
        }
    return v;
}

int main() {
#ifdef popteam
    // freopen("L.in", "r", stdin);
    // freopen("L2.in", "r", stdin);
    freopen("L-big.txt", "r", stdin);
#endif
    inv[0] = inv[1] = fac[0] = ifac[0] = 1;
    for (int i = 2; i < N; i++) {
        inv[i] = (long long)(mod - mod / i) * inv[mod % i] % mod;
    }
    for (int i = 1; i < N; i++) {
        fac[i] = (long long)fac[i - 1] * i % mod;
        ifac[i] = (long long)ifac[i - 1] * inv[i] % mod;
    }
    for (int i = 2; i < V; i++) {
        if (!vis[i]) pri.push_back(i);
        for (int j = i; j < V; j += i)
            vis[j] = true;
    }

    cin.tie(0)->sync_with_stdio(0);
    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        if (++a[i] == mod) a[i] = 0;
    }

    p = factor(m);
    dfs(0, 1);
    sort(all(uni));
    // logvec(uni);

    int zero = 0, all = 1;
    for (int i = 1; i <= n; i++)
        if (a[i] == 0) {
            swap(a[++zero], a[i]);
        } else {
            all = (long long)all * a[i] % mod;
            a[i] = power(a[i], mod - 2);
        }
    // cerr << "zero = " << zero << endl;
    // cerr << "all = " << all << endl;
    // for (int i = 1; i <= n; i++)
    //     cerr << a[i] << " \n"[i == n];
    vector<int> p = zero < n ? solve(zero + 1, n) : vector<int>{};
    for (int i = 0; i < K - zero; i++)
        dp[i + zero] = i < p.size() ? p[i] : 0;
    for (int i = 0; i < K; i++) {
        // fprintf(stderr, "dp[%d] = %d => %d\n", i, dp[i], (int)((long long)dp[i] * all % mod));
        dp[i] = (long long)dp[i] * all % mod;
    }

    f[0][0] = g[0][0] = 1;
    for (int i = 1; i < uni.size(); i++) {
        int j = upper_bound(all(uni), m / uni[i]) - uni.begin() - 1;
        j = min((int)uni.size() - 1, j + 5);
        for (; j >= 0; j--)
            if (m % (uni[i] * uni[j]) == 0) {
                long long t = m / uni[j];
                for (int y = 1; y < K; y++) {
                    if (t % uni[i]) break;
                    t /= uni[i];
                    int k = find(m / t);
                    // fprintf(stderr, ">> i=%d j=%d k=%d y=%d\n", i, j, k, y);
                    for (int x = y; x < K; x++) {
                        upd(f[k][x], (long long)f[j][x - y] * ifac[y] % mod);
                        upd(g[k][x], (long long)g[j][x - y] * power((uni[i] - 1) % mod, y) % mod * ifac[y] % mod);
                    }
                }
            }
    }
    for (int i = 0; i < uni.size(); i++)
        for (int j = 0; j < K; j++)
            if (f[i][j] || g[i][j]) {
                f[i][j] = (long long)f[i][j] * fac[j] % mod;
                g[i][j] = (long long)g[i][j] * fac[j] % mod;
                // fprintf(stderr, "i=%d j=%d >> f=%d g=%d\n", i, j, f[i][j], g[i][j]);
            }
    for (int x = 0; x < K; x++)
        for (int y = 0; x + y < K; y++) {
            for (int i = 0; i < uni.size(); i++) {
                int j = find(m / uni[i]);
                if (f[i][x] && g[j][y]) {
                    upd(h[x][y], (long long)f[i][x] * g[j][y] % mod);
                    // fprintf(stderr, "f[%d][%d](%d) * g[%d][%d](%d) -> %d\n", i, x, f[i][x], j, y, g[j][y], h[x][y]);
                }
            }
        }
    int ans = 0;
    for (int x = 0; x < K; x++)
        for (int y = 0; x + y < K && x + y <= n; y++)
            if (h[x][y] && dp[y]) {
                // fprintf(stderr, "x=%d y=%d h=%d C=%d dp=%d\n", x, y, h[x][y], C(n - y, x), dp[y]);
                upd(ans, (long long)h[x][y] * C(n - y, x) % mod * dp[y] % mod);
            }
    cout << ans << endl;
}