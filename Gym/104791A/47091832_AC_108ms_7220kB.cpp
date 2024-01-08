#include <bits/stdc++.h>
using namespace std;
int main() {
  cin.tie(0)->sync_with_stdio(0);
  long long t;
  cin >> t;
  while (t--) {
    long long n, c;
    cin >> n >> c;
    vector<long long> v;
    for (long long i = 0; i < n; i++) {
      long long x;
      cin >> x;
      v.push_back(x);
    }
    long long cnt = 0;
    long long num = c;
    for (long long i = 0; i < n; i++) {
      if (v[i] < num) num -= v[i];
      else {
        cnt++;
        num = c;
      }
    }
    cout << cnt + 1 << endl;
  }
}