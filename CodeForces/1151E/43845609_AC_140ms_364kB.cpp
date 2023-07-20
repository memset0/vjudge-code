#include <bits/stdc++.h>
using namespace std;

int main() {
  int n;
  cin >> n;
  vector<int> a(n);
  long long ans = 0;
  for (auto &i : a) {
    cin >> i;
    ans += i * (n - i + 1ll);
  }
  for (int i = 1; i < n; ++i) {
    int u = a[i], v = a[i - 1];
    if (u > v) swap(u, v);
    ans -= u * (n - v + 1ll);
  }
  cout << ans << endl;
}