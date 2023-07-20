#include <bits/stdc++.h>
using namespace std;
int n;
long long ans = 0;
int main() {
  cin >> n, --n;
  for (int i = 1; i <= n; i++) {
    ans = (ans + (long long)(n - i + 1) * (n - i + 1) * i) % 1000000007;
  }
  cout << ans << endl;
}