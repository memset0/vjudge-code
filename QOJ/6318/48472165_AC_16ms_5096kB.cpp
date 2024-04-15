#include "bits/stdc++.h"
using namespace std;
const int MAXN = 200011, V = 10000, INF = 1e9 + 233;
void umax(int &a, int t) {
    if (t > a) a = t;
}
int pre[V], f[V], a[MAXN];
vector<int> seq[V];
void init() {
    seq[0].emplace_back(0);
    for (int i = 1; i < 10000; ++i) {
        vector<int> now;
        int t = i;
        while (t)
            now.emplace_back(t % 10), t /= 10;
        sort(now.begin(), now.end());
        do {
            int v = 0;
            for (auto x : now)
                v = v * 10 + x;
            // if (i == 120) printf("v=%d\n", v);
            seq[i].emplace_back(v);
        } while (next_permutation(now.begin(), now.end()));
    }
}
int main() {
    init();
    memset(f, 0xcf, sizeof f);
    int n, x;
    cin >> n >> x;
    f[x] = 0;
    for (int i = 1; i <= n; ++i) {
        // printf("i=%d\n", i);
        cin >> a[i];
        memcpy(pre, f, sizeof f);
        // memcpy(pre,f,sizeof f)memset(f,0xcf,sizeof f);
        for (int x = 0; x < V; ++x)
            for (auto y : seq[x])
                umax(pre[y], f[x]);
        memcpy(f, pre, sizeof f);
        for (int x = a[i]; x < V; ++x)
            umax(f[x - a[i]], pre[x] + 1);
        // for (int x = 0; x < V; ++x)
        //     if (f[x] > 0) printf("F[%d]=%d\n", x, f[x]);
    }
    int ans = 0;
    for (int x = 0; x < V; ++x)
        umax(ans, f[x]);
    cout << ans << '\n';
    return 0;
}