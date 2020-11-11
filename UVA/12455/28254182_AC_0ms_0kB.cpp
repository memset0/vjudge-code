#include <bits/stdc++.h>
using namespace std;

const int N = 1e3 + 5;
int t, n, p, x, ok[N];

int main() {
  cin >> t;
  while (t--) {
    cin >> n >> p;
    memset(ok, 0, sizeof(ok));
    ok[0] = 1;
    for (int i = 1; i <= p; i++) {
      cin >> x;
      for (int j = 1000; j >= x; j--) {
        if (ok[j - x]) {
          ok[j] = 1;
        }
      }
    }
    if (ok[n]) {
      cout << "YES\n";
    } else {
      cout << "NO\n";
    }
  }
  return 0;
}