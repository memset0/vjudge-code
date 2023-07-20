#include <bits/stdc++.h>
using namespace std;
int main() {
#ifdef memset0
  freopen("1.in", "r", stdin);
#endif
  ios::sync_with_stdio(0), cin.tie(0);
  int T;
  string a, b;
  cin >> T;
  for (int t = 1; t <= T; t++) {
    cout << "Case " << t << ":" << endl;
    cin >> a >> b;
    cout << a << " + " << b << " = ";
    vector<int> c(max(a.size(), b.size()) + 1);
    for (int i = 0; i < a.size(); i++) c[a.size() - i - 1] += a[i] - 48;
    for (int i = 0; i < b.size(); i++) c[b.size() - i - 1] += b[i] - 48;
    for (int i = 0; i + 1 < c.size(); i++)
      if (c[i] >= 10) {
        c[i + 1]++, c[i] -= 10;
      }
    while (c.size() > 1 && c.back() == 0) c.pop_back();
    for (auto it = c.rbegin(); it != c.rend(); it++) {
      cout << *it;
    }
    cout << endl << endl;
  }
}