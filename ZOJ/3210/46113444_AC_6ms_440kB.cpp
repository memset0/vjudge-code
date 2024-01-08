#include <bits/stdc++.h>
using namespace std;
int main() {
#ifdef memset0
  freopen("1.in", "r", stdin);
#endif
  cin.tie(0)->sync_with_stdio(0);
  int T, n;
  cin >> T;
  while (T--) {
    cin >> n;
    vector<int> a(n), b(n);
    for (int i = 0; i < n; i++) cin >> a[i];
    for (int i = 0; i < n; i++) cin >> b[i];
    bool f1 = false, f2 = false;
    if (a == b) { f1 = true; }
    reverse(b.begin(), b.end());
    if (a == b) { f2 = true; }
    if (f1 && f2) { cout << "both" << endl; }
    if (f1 && !f2) { cout << "queue" << endl; }
    if (!f1 && f2) { cout << "stack" << endl; }
    if (!f1 && !f2) { cout << "neither" << endl; }
  }
}//