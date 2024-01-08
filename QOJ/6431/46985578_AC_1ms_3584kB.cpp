#include <bits/stdc++.h>
using namespace std;
int n, m, k, l;
int main() {
  cin.tie(0)->sync_with_stdio(0);
  cin >> n >> k >> l;
  if (k << 1 > n) {
    for (int i = 1; i < n; ++i) cout << 'D';
    for (int i = n - k; i; --i) cout << 'U';
  } else {
    for (int i = 1; i < n; ++i) cout << 'U';
    for (int i = 1; i < k; ++i) cout << 'D';
  }
  if (l << 1 > n) {
    for (int i = 1; i < n; ++i) cout << 'R';
    for (int i = n - l; i; --i) cout << 'L';
  } else {
    for (int i = 1; i < n; ++i) cout << 'L';
    for (int i = 1; i < l; ++i) cout << 'R';
  }
  cout << '\n';
}