#include <bits/stdc++.h>
using namespace std;
const int N = 5000, M = 1e4;
const int mod = 998244353;
int n, m, u, v;
int nw, dfn[N + 10], low[N + 10], q[N + 10], sz, iq[N + 10];
int cnt, fr[N + 10], tt[N + 10], en[N + 10];
int dp[N + 10][N + 10], siz[N + 10], td[N + 10];
int p2[(N * (N + 1) >> 1) + 10], ans;
vector<int> e[N + 10], te[N + 10];
int C2(int x) { return x * (x - 1) >> 1; }
void Tarjan(int x, int fa) {
    dfn[x] = low[x] = ++nw;
    q[++sz] = x, iq[x] = 1;
    for (int i : e[x]) {
        if (!dfn[i])
            Tarjan(i, x), low[x] = min(low[x], low[i]);
        else if (fa != i && iq[i])
            low[x] = min(low[x], dfn[i]);
    }
    // cout << "DFN " << x << "=" << dfn[x] << " low=" << low[x] << "\n";
    if (dfn[x] == low[x]) {
        ++cnt;
        while (q[sz] != x)
            fr[q[sz]] = cnt, iq[q[sz--]] = 0;
        fr[q[sz]] = cnt, iq[q[sz--]] = 0;
    }
}
void Merge(int x, int y) {
    for (int i = 0; i <= siz[x]; ++i)
        td[i] = dp[x][i], dp[x][i] = 0;
    for (int i = 1; i <= siz[x]; ++i)
        for (int j = 1; j <= siz[y]; ++j) {
            dp[x][i + j] = (dp[x][i + j] + 1ll * td[i] * dp[y][j] % mod * p2[i * j - (!!j)]) % mod;
            dp[x][i] = (dp[x][i] - 1ll * td[i] * dp[y][j] % mod + mod) % mod;
        }
    siz[x] += siz[y];
}
void DP(int x, int fa) {
    siz[x] = tt[x];
    int t = p2[C2(siz[x]) - en[x]];
    dp[x][siz[x]] = t;
    for (int i : te[x])
        if (i != fa) {
            DP(i, x);
            Merge(x, i);
        }
    /*for (int i = 0; i <= siz[x]; ++i)
        cout << "DP " << x << " " << i << "=" << dp[x][i] << "\n";*/
}
int main() {
    cin.sync_with_stdio(0), cin.tie(0);
    cin >> n >> m;
    p2[0] = 1;
    for (int i = 1; i <= C2(n); ++i)
        p2[i] = (p2[i - 1] << 1) % mod;
    for (int i = 1; i <= m; ++i) {
        cin >> u >> v, e[u].push_back(v), e[v].push_back(u);
    }
    Tarjan(1, 0);
    // cout << "CNT=" << cnt << "\n";
    for (int i = 1; i <= n; ++i) {
        ++tt[fr[i]];
        for (int j : e[i])
            if (fr[i] != fr[j])
                te[fr[i]].push_back(fr[j]);
            else
                ++en[fr[i]];
    }
    for (int i = 1; i <= cnt; ++i)
        en[i] >>= 1;
    DP(1, 0);
    for (int i = 1; i <= n; ++i)
        ans = (ans + dp[1][i]) % mod;
    cout << ans;
    return 0;
}
/*
3 2
1 2
2 3

4 4
1 2
2 3
3 4
4 1

9 11
1 4
1 5
4 5
5 2
2 3
3 6
6 2
2 7
7 8
7 9
8 9

*/