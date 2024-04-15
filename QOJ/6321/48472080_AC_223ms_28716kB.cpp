#include "bits/stdc++.h"
using namespace std;
typedef long long ll;
const int MAXN = 500011, mod = 998244353;
int a[6][MAXN], fx[MAXN], diff = 0;
int ctrb[MAXN][6];
int cnt[6], f[6], pre[6];
int main() {
    int n;
    cin >> n;
    for (int k = 1; k <= 5; ++k)
        for (int i = 1; i <= n; ++i)
            cin >> a[k][i], fx[++diff] = a[k][i];
    sort(fx + 1, fx + diff + 1), diff = unique(fx + 1, fx + diff + 1) - fx - 1;
    for (int k = 1; k <= 5; ++k)
        for (int i = 1; i <= n; ++i) {
            a[k][i] = lower_bound(fx + 1, fx + diff + 1, a[k][i]) - fx;
            ++ctrb[a[k][i]][k];
        }
    for (int k = 1; k <= 5; ++k)
        cnt[k] = n;
    int ans = 0;
    for (int v = 1; v <= diff; ++v) {
        // printf("v=%d,real=%d\n", v, fx[v]);

        // for (int k = 1; k <= 5; ++k)
            // printf("cnt[%d]=%d\n", k, cnt[k]);
        memset(f, 0, sizeof f), memset(pre, 0, sizeof pre);
        f[0] = 1;
        for (int k = 1; k <= 5; ++k) {
            memcpy(pre, f, sizeof f), memset(f, 0, sizeof f);
            for (int j = 0; j <= 5; ++j)
                f[j] = (ll)pre[j] * (n - cnt[k]) % mod;
            for (int j = 1; j <= 5; ++j)
                f[j] = (f[j] + (ll)cnt[k] * pre[j - 1]) % mod;
        }
        int sum = ((ll)f[3] + f[4] + f[5]) % mod;
        // printf("sum=%d\n", sum);
        ans = (ans + (ll)sum * (fx[v] - fx[v - 1])) % mod;

        for (int k = 1; k <= 5; ++k)
            cnt[k] -= ctrb[v][k]; //, printf("cnt[%d]=%d\n", k, cnt[k]);
    }
    cout << ans << '\n';
    return 0;
}