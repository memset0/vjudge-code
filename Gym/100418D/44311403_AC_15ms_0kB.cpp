#include <bits/stdc++.h>
using namespace std;
const int mod = 1e9 + 7;
int n;
__int128 ans;
int main() {
#ifdef memset0
  freopen("D.in", "r", stdin);
#endif

  cin >> n;
  __int128 sqn = (long long)n * n;
  ans = sqn * (sqn - 1) >> 2;
  // cerr << (long long)ans << endl;
  ans -= (__int128)n * (n - 1) * (n * 2 - 1) / 6;

  // cerr << (long long)ans << endl;
  ans %= mod;
  ans <<= 1;
  ans %= mod;
  cout << (int)ans << endl;
}