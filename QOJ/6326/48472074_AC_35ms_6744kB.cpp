#include <bits/stdc++.h>
#define all(x) begin(x), end(x)
using namespace std;
const int N = 3e5;
int n, L[N + 10], R[N + 10];
int ar[N + 10], sz;
bool Above(int l, int p, int h, int r) { return 1ll * (r - l) * (h - R[l]) > 1ll * (p - l) * (R[r] - R[l]); }
int main() {
#ifdef popteam
    freopen("J.in", "r", stdin);
#endif
    cin.tie(0)->sync_with_stdio(0);
    cin >> n;
    for (int i = 1; i <= n; ++i)
        cin >> L[i];
    for (int i = 1; i <= n; ++i)
        cin >> R[i];
    ar[sz = 1] = 1;
    for (int i = 2; i <= n; ++i) {
        while (sz > 1 && Above(ar[sz - 1], ar[sz], R[ar[sz]], i))
            --sz;
        ar[++sz] = i;
    }
    for (int i = 1; i < sz; ++i) {
        for (int j = ar[i] + 1; j < ar[i + 1]; ++j)
            if (Above(ar[i], j, L[j], ar[i + 1])) {
                cout << "No";
                return 0;
            }
    }
    cout << "Yes";
}