#include <bits/stdc++.h>
using namespace std;
const int N = 1e3 + 9, M = 1e6 + 9, mod = 998244353;
int n, m, fac[M], inv[M], ifac[M];
inline int sub(int x, int y) {
    x -= y;
    return x < 0 ? x + mod : x;
}
inline int add(int x, int y) {
    x += y;
    return x >= mod ? x - mod : x;
}
int C(int n, int m) { return (long long)fac[n] * ifac[m] % mod * ifac[n - m] % mod; }
int power(int a, int b) {
    int s = 1;
    for (; b; b >>= 1, a = (long long)a * a % mod)
        if (b & 1) s = (long long)s * a % mod;
    return s;
}
vector<int> rev, rt;
void getRevRoot(int n) {
    int m = __lg(n); // log(n)/log(2)+1e-8;
    rev.resize(n);
    for (int i = 1; i < n; i++) {
        rev[i] = rev[i >> 1] >> 1 | (i & 1) << (m - 1);
    }
    static int len = 1;
    if (len < n) {
        rt.resize(n);
        for (; len < n; len <<= 1) {
            int uni = power(3, (mod - 1) / (len << 1));
            rt[len] = 1;
            for (int i = 1; i < len; i++) {
                rt[i + len] = (long long)rt[i + len - 1] * uni % mod;
            }
        }
    }
}
void ntt(vector<int> &f, int n) {
    f.resize(n);
    for (int i = 0; i < n; i++) {
        if (i < rev[i]) swap(f[i], f[rev[i]]);
    }
    for (int len = 1; len < n; len *= 2) {
        for (int i = 0; i < n; i += len * 2) {
            for (int j = 0; j < len; j++) {
                int x = f[i + j];
                int y = (long long)f[i + j + len] * rt[j + len] % mod;
                f[i + j] = add(x, y);
                f[i + j + len] = sub(x, y);
            }
        }
    }
}
vector<int> operator*(vector<int> f, vector<int> g) {
    int n = 1, m = (int)(f.size() + g.size()) - 1;
    while (n < m)
        n <<= 1;
    int invn = power(n, mod - 2);
    getRevRoot(n), ntt(f, n), ntt(g, n);
    for (int i = 0; i < n; i++)
        f[i] = (long long)f[i] * g[i] % mod;
    reverse(f.begin() + 1, f.end()), ntt(f, n);
    f.resize(m);
    for (int i = 0; i < m; i++)
        f[i] = (long long)f[i] * invn % mod;
    return f;
}
vector<int> power(vector<int> a, int b) {
    vector<int> s = {1};
    for (; b; b >>= 1, a = a * a)
        if (b & 1) s = s * a;
    return s;
}
int main() {
#ifdef popteam
    freopen("G.in", "r", stdin);
#endif
    inv[0] = inv[1] = fac[0] = ifac[0] = 1;
    for (int i = 2; i < M; i++) {
        inv[i] = (long long)(mod - mod / i) * inv[mod % i] % mod;
    }
    for (int i = 1; i < M; i++) {
        fac[i] = (long long)fac[i - 1] * i % mod;
        ifac[i] = (long long)ifac[i - 1] * inv[i] % mod;
    }
    cin >> n >> m;
    vector<int> a(m + 1);
    for (int i = 0; i <= m; i++) {
        a[i] = (long long)C(m, i) * C(m, i) % mod * fac[i] % mod;
    }
    // for (int i = 0; i <= m; i++)
    //     cerr << a[i] << " \n"[i == m];
    vector<int> f = power(a, n);
    // for (int i = 0; i <= n * m; i++)
    //     cerr << f[i] << " \n"[i == n * m];
    int ans = 0;
    for (int i = 0; i <= n * m; i++) {
        ans = (ans + (long long)fac[n * m - i] * (i & 1 ? mod - 1 : 1) % mod * f[i]) % mod;
    }
    cout << ans << endl;
}/////