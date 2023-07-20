#include <bits/stdc++.h>
using namespace std;
int main() {
#ifdef memset0
  freopen("1.in", "r", stdin);
#endif
  vector<int> pre(1000);
  for (int i = 1; i <= 9; i++)
    for (int j = 0; j <= 9; j++)
      for (int k = 0; k <= 9; k++)
        if (i * 100 + j * 10 + k == i * i * i + j * j * j + k * k * k) {
          pre[i * 100 + j * 10 + k] = true;
        }
  int l, r;
  while (cin >> l >> r) {
    vector<int> ans;
    for (int i = l; i <= r; i++)
      if (pre[i]) {
        ans.push_back(i);
      }
    if (!ans.size()) {
      cout << "no" << endl;
    } else {
      for (int x : ans) cout << x << " ";
      cout << endl;
    }
  }
}