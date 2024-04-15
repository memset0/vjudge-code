#include <bits/stdc++.h>
#define all(x) begin(x), end(x)
using namespace std;
const int N = 1e5 + 9;
long long n;
int m;
int solve(const vector<pair<long long, int>> &s, long long n) {
    // cerr << "solve " << n << endl;
    // for (const auto &[x, v] : s)
    //     cerr << "> " << x << " " << v << endl;
    if (n == 1) return 0;
    vector<pair<long long, int>> a, b, c;
    for (const auto &[x, v] : s) {
        if (x <= (n >> 1)) {
            a.emplace_back(x, v);
        } else {
            b.emplace_back(n - x + 1, v);
        }
    }
    reverse(all(b));
    int ans = 0;
    for (int i = 0, j = 0; i < a.size() || j < b.size();) {
        if (i < a.size() && j < b.size() && a[i].first == b[j].first) {
            if (a[i].second + b[j].second == 1) { // 01/10
                c.emplace_back(a[i].first, 2);
                ans++;
            } else if (a[i].second == 2 || b[j].second == 2) { // 02/12/20/21/22
                c.emplace_back(a[i].first, a[i].second + b[j].second - 2);
            } else {
                c.emplace_back(a[i].first, a[i].second);
            }
            i++, j++;
        } else if (i < a.size() && (j == b.size() || a[i].first < b[j].first)) {
            if (a[i].second == 1) {
                c.emplace_back(a[i].first, 2);
                ans++;
            } else {
                c.emplace_back(a[i].first, 0);
            }
            i++;
        } else {
            if (b[j].second == 1) {
                c.emplace_back(b[j].first, 2);
                ans++;
            } else {
                c.emplace_back(b[j].first, 0);
            }
            j++;
        }
    }
    return ans + solve(c, n >> 1);
}
int main() {
#ifdef popteam
    freopen("J.in", "r", stdin);
#endif
    cin.tie(0)->sync_with_stdio(0);
    cin >> n >> m;
    vector<pair<long long, int>> a;
    for (int i = 1; i <= m; i++) {
        long long x;
        cin >> x;
        a.emplace_back(x, 1);
    }
    cout << solve(a, n) << endl;
}