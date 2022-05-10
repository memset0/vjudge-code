#include <bits/stdc++.h>
using namespace std;
int n, m;
inline int query(int l, int r) {
  static int res;
  if (l == r)
    return 0;
  cout << "? " << l << ' ' << r << endl;
  return cin >> res, res;
}
int main() {
  cin >> n;
  if (n == 1) {
    cout << "! 1" << endl;
    return 0;
  }
  int l = 1, r = n;
  m = query(l, r);
  while (l < r) {
    int mid = (l + r) >> 1;
    if (m <= mid) {
      if (query(1, mid) == m) {
        r = mid;
      } else {
        l = mid + 1;
      }
    } else {
      if (query(mid + 1, n) == m) {
        l = mid + 1;
      } else {
        r = mid;
      }
    }
  }
  cout << "! " << l << endl;
}