#include <bits/stdc++.h>
#define all(x) begin(x), end(x)
using namespace std;
const int N = 5e3 + 9;
int n, d, a[N], b[N];
vector<int> tmp;
long long check(int l, int r) {
    for (int i = 1; i <= n; i++) {
        if (a[i] < l) {
            b[i] = l;
        } else if (a[i] > r) {
            b[i] = r;
        } else {
            b[i] = a[i];
        }
    }
    long long sum = 0;
    for (int i = 1; i < n; i++) {
        int x = b[i] - b[i + 1];
        sum += x < 0 ? -x : x;
    }
    // fprintf(stderr, "l=%d r=%d >> %lld\n", l, r, sum);
    return sum;
}
int main() {
#ifdef popteam
    freopen("A.in", "r", stdin);
#endif
    cin.tie(0)->sync_with_stdio(0);
    cin >> n >> d;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        tmp.push_back(a[i]);
        tmp.push_back(a[i] - d);
    }
    sort(all(tmp));
    tmp.erase(unique(all(tmp)), tmp.end());
    long long ans = LLONG_MIN;
    for (int l : tmp) {
        ans = max(ans, check(l, l + d));
    }
    cout << ans << endl;
}