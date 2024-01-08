#include <bits/stdc++.h>
using namespace std;
int main() {
  cin.tie(0)->sync_with_stdio(0);
  int n, m;
  cin >> n >> m;
  cout << fixed << setprecision(15);
  if (n == m) {
    cout << sqrt(2) * n << endl;
  } else {
    if (n > m) swap(n, m);
    cout << sqrt(m * m - n * n) << endl;
  }
}