#include <bits/stdc++.h>
#ifndef popteam
#define endl '\n'
#endif
#define all(x) begin(x), end(x)
using namespace std;
typedef long long ll;
const int N = 60;
const int mod = 998244353;
int n, lm, f[N + 5][N + 5][N + 5], g[N + 5][N + 5][2], ans;
ll c;
int main() {
#ifdef popteam
    freopen("G.in", "r", stdin);
#endif
    cin.tie(0)->sync_with_stdio(0);
    cin >> n >> c;
    c -= (1ll << n - 1);
    while ((1ll << lm + 1) <= c)
        ++lm;
    if (c < 0) return cout << "0", 0;
    for (int k = 0; k <= lm; ++k) {
        for (int i = 0; i <= k && i < n; ++i)
            for (int j = i; j < n; ++j) {
                f[i][j][k] = (k == i);
                for (int t = i; t <= j; ++t)
                    f[i][j][k] = (f[i][j][k] + 1ll * f[i][t][k - 1] * f[t][j][k - 1]) % mod;
            }
    }
    g[lm + 1][n - 1][1] = 1;
    for (int i = lm; i >= 0; --i)
        for (int j = 0; j < n; ++j) {
            if ((c >> i) & 1) {
                g[i][j][1] = (g[i][j][1] + 1ll * g[i + 1][j][1] * f[j][j][i]) % mod;
                g[i][j][0] = (g[i][j][0] + g[i + 1][j][1] + 1ll * g[i + 1][j][0] * (1 + f[j][j][i])) % mod;
            } else {
                g[i][j][1] = (g[i][j][1] + g[i + 1][j][1]) % mod;
                g[i][j][0] = (g[i][j][0] + 1ll * g[i + 1][j][0] * (1 + f[j][j][i])) % mod;
            }
            for (int k = j - 1; k >= 0; --k) {
                if ((c >> i) & 1) {
                    g[i][k][1] = (g[i][k][1] + 1ll * g[i + 1][j][1] * f[k][j][i]) % mod;
                    g[i][k][0] = (g[i][k][0] + 1ll * g[i + 1][j][0] * f[k][j][i]) % mod;
                } else {
                    g[i][k][0] = (g[i][k][0] + 1ll * g[i + 1][j][0] * f[k][j][i]) % mod;
                }
            }
        }
    for (int i = 0; i < n; ++i)
        ans = (ans + 1ll * g[0][i][0] + g[0][i][1]) % mod;
    cout << ans;
}