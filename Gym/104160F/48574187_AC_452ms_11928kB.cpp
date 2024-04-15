#include <bits/stdc++.h>
#ifndef popteam
#define endl '\n'
#endif
using namespace std;
const int N = 1e6 + 9;
long long b[N];
vector<int> solve(int n) {
    if (n <= 2) return {};
    long long res = (long long)n * (n - 3) / 2;
    if (res & 1) return {};
    res >>= 1;
    vector<int> ans;
    while (res) {
        int x = upper_bound(b + 1, b + N, res) - b - 1;
        // fprintf(stderr, "x=%d; b[x]=%lld; n=%d; res=%lld\n", x, b[x], n, res);
        res -= b[x];
        n -= x;
        ans.push_back(x);
        assert(n >= 0);
    }
    while (n--)
        ans.push_back(1);
    return ans;
}
int main() {
#ifdef popteam
    freopen("F.in", "r", stdin);
#endif
    for (int i = 1; i < N; i++) {
        b[i] = (long long)i * (i - 1) / 2;
    }
    int T, n, m;
    cin >> T;
    while (T--) {
        cin >> n >> m;
        auto it = solve(n);
        if (it.empty()) {
            it = solve(m);
            if (it.empty()) {
                cout << "No" << endl;
            } else {
                cout << "Yes" << endl;
                for (int i = 1; i <= n; i++) {
                    int fl = 0;
                    for (int x : it) {
                        for (int j = 1; j <= x; j++)
                            cout << fl << " ";
                        fl ^= 1;
                    }
                    cout << endl;
                }
            }
        } else {
            cout << "Yes" << endl;
            int fl = 0;
            for (int x : it) {
                for (int i = 1; i <= x; i++) {
                    for (int j = 1; j <= m; j++)
                        cout << fl << " \n"[j == m];
                }
                fl ^= 1;
            }
        }
    }
}