#include <bits/stdc++.h>
using namespace std;
const int N = 1e3 + 9;
pair<int, int> a[N];
priority_queue<pair<int, int>> Q;
int m, n;
int main() {
  ios::sync_with_stdio(0), cin.tie(0);
  cin >> m >> n;
  for (int i = 1; i <= n; i++) cin >> a[i].first;
  for (int i = 1; i <= n; i++) {
    cin >> a[i].second;
    m -= a[i].second;
  }
  sort(a + 1, a + n + 1);
  int k = n;
  for (int i = n; i >= 1; i--) {
    while (k && a[k].first >= i) Q.push(a[k--]);
    if (Q.empty()) continue;
    m += Q.top().second;
    Q.pop();
  }
  cout << m << endl;
}