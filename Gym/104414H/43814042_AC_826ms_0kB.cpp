#include <bits/stdc++.h>
using namespace std;
int T;
long long n, k, g;
vector<int> b;
vector<pair<int, int>> a;
long long gcd(long long a, long long b) { return b == 0 ? a : gcd(b, a % b); }
inline unsigned long long sqrt(unsigned long long x) {
  unsigned long long y = (unsigned long long)(sqrt((double)x) - 0x1p-20);
  if (2 * y < x - y * y) ++y;
  return y;
}
inline long long sqrt(long long x) { return (long long)sqrt((unsigned long long)x); }
vector<pair<int, int>> factor(int x) {
  vector<pair<int, int>> a;
  for (int i = 2; i * i <= x; i++)
    if (x % i == 0) {
      a.emplace_back(i, 0);
      while (x % i == 0) {
        a.back().second++;
        x /= i;
      }
    }
  if (x > 1) a.emplace_back(x, 1);
  return a;
}
void dfs(int i, int w) {
  if (i == a.size()) {
    b.push_back(w);
    return;
  }
  for (int j = 0; j <= a[i].second; j++) {
    dfs(i + 1, w);
    w *= a[i].first;
  }
}
int main() {
#ifdef memset0
  freopen("H.in", "r", stdin);
#endif
  cin >> T;
  while (T--) {
    cin >> n >> k;
    g = gcd(n, k);
    a = factor((int)g);
    b.clear();
    dfs(0, 1);
    for (int g : b) {
      // cerr << ">>" << g << endl;
      long long nn = n / g, kk = k / g, mms = nn * nn - 4 * kk;
      if (mms >= 0) {
        long long mm = sqrt(mms);
        if (mm * mm == mms) {
          if ((nn + mm) % 2 == 0) {
            long long x = (nn + mm) >> 1;
            long long y = (nn - mm) >> 1;
            if (gcd(x, y) == 1) {
              if (x > y) swap(x, y);
              cout << (x * g) << " " << (y * g) << endl;
            }
          }
        }
      }
    }
  }
}