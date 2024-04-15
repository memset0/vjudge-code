#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 5e5 + 9;
multiset<ll> rm[45];
int cnt[45];
int main() {
#ifdef popteam
    // freopen("I.in", "r", stdin);
#endif
    cin.tie(0)->sync_with_stdio(0);
    int task;
    cin >> task;
    while (task--) {
        for (int k = 0; k < 45; ++k)
            cnt[k] = 0, rm[k].clear();
        int n, ans = 0;
        cin >> n;
        for (int i = 1; i <= n; ++i) {
            ll x;
            cin >> x;
            x = std::__lg(x);
            ++cnt[x];
            // cout << "X=" << x << endl;
            if (x) rm[x].insert(1ll << (x - 1));
        }
        // cout << "Pass 27\n";
        for (int k = 0; k < 45; ++k)
            for (int r = 1; r <= cnt[k]; ++r) {
                // printf("Consider k=%d,r=%d\n", k, r);
                bool flag = 0;
                for (int v = k + 1; v < 45; ++v) {
                    auto it = rm[v].lower_bound(1ll << k);
                    if (it != rm[v].end()) {
                        // printf("v=%d\n", v);
                        ll p = (*it) - (1ll << k);
                        rm[v].erase(it);
                        if (p) rm[v].insert(p);
                        flag = 1;
                        break;
                    }
                }
                if (!flag) ++ans;
            }
        cout << ans << '\n';
    }
    return 0;
}