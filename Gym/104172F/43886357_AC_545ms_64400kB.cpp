#include <bits/stdc++.h>
using namespace std;
const int N = 2e5 + 9;
const int B = 100000000, K = 8;
// const int B = 100, K = 2;
int T, n, k;
string s;
vector<int> pos[8];
struct bignum {
  vector<int> a;
  explicit bignum() { a.push_back(0); }
  explicit bignum(int l, int r) {
    for (int i = r; i >= l; i -= K) {
      a.push_back(0);
      for (int j = K - 1; j >= 0; j--)
        if (i - j >= l) {
          a.back() = a.back() * 10 + s[i - j - 1] - '0';
        }
    }
  }
  inline string to_string() {
    string r = "";
    for (auto it = a.rbegin(); it != a.rend(); it++) {
      string s = "";
      int x = *it;
      while (x) {
        s = (char)(48 + x % 10) + s;
        x /= 10;
      }
      if (it != a.rbegin()) {
        while (s.length() < K) s = '0' + s;
      }
      r += s;
    }
    return r;
  }
  friend inline bignum operator+(const bignum &a, const bignum &b) {
    bignum c = a;
    c.a.resize(max(a.a.size(), b.a.size()) + 1);
    for (int i = 0; i < b.a.size(); i++) c.a[i] += b.a[i];
    for (int i = 0; i < c.a.size(); i++)
      if (c.a[i] >= B) {
        c.a[i + 1] += c.a[i] / B;
        c.a[i] %= B;
      }
    while (c.a.size() > 1 && c.a.back() == 0) c.a.pop_back();
    return c;
  }
  friend inline bool operator<(const bignum &a, const bignum &b) {
    if (a.a.size() != b.a.size()) {
      return a.a.size() < b.a.size();
    }
    for (int i = (int)a.a.size() - 1; i >= 0; i--) {
      if (a.a[i] != b.a[i]) return a.a[i] < b.a[i];
    }
    return false;
  }
} dp[N][8];
int main() {
#ifdef memset0
  freopen("F.in", "r", stdin);
#endif
  cin >> T;
  while (T--) {
    cin >> n >> k >> s, ++k;
    for (int i = 1; i < k; i++) {
      pos[i].clear();
      int x = n * i / k;
      if (1 <= x && x <= n) pos[i].push_back(x);
      if (1 <= x - 2 && x - 2 <= n) pos[i].push_back(x - 2);
      if (1 <= x - 1 && x - 1 <= n) pos[i].push_back(x - 1);
      if (1 <= x + 1 && x + 1 <= n) pos[i].push_back(x + 1);
      if (1 <= x + 2 && x + 2 <= n) pos[i].push_back(x + 2);
      if (1 <= x + 3 && x + 3 <= n) pos[i].push_back(x + 3);
      sort(pos[i].begin(), pos[i].end());
    }
    pos[0] = {0}, pos[k] = {n};
    for (int i = 1; i <= k; i++) {
      for (int r : pos[i]) {
        dp[r][i].a.clear();
        for (int l : pos[i - 1])
          if (l < r) {
            bignum x(l + 1, r);
            if (!dp[r][i].a.size()) {
              dp[r][i] = dp[l][i - 1] + x;
            } else {
              dp[r][i] = min(dp[r][i], dp[l][i - 1] + x);
            }
            // printf("%d : %d -> %d ", i, l, r), x.out(), cout << "  ", dp[r][i].out(), cout << endl;
          }
      }
    }
    cout << dp[n][k].to_string() << endl;
  }
}