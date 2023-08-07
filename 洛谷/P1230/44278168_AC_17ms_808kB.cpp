#include <bits/stdc++.h>
using namespace std;
using pii = pair<int, int>;
const int N = 1e3 + 9;
pii a[N];
priority_queue<pii> Q;
int m, n;
int main() {
  ios::sync_with_stdio(0), cin.tie(0);
  cin >> m >> n;
  for (int i = 1; i <= n; i++) cin >> a[i].second;
  for (int i = 1; i <= n; i++) {
    cin >> a[i].first;
    m -= a[i].first;
  }
  sort(a + 1, a + n + 1, [](const pii &a, const pii &b) { return a.second < b.second; });
  int k = n;
  for (int i = n; i >= 1; i--) {
    while (k && a[k].second >= i) Q.push(a[k--]);
    if (Q.empty()) continue;
    m += Q.top().first;
    Q.pop();
  }
  cout << m << endl;
}