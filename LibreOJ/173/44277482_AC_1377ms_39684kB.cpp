// https://loj.ac/p/173

#include <bits/stdc++.h>
using ll = long long;
using namespace std;
namespace Runs {
const int N = 1e6 + 10, p0 = 998244353, p1 = 1e9 + 7, px = 131131;
int n, c, top, la[N], h0[N], h1[N], pw0[N], pw1[N], stk[N];
string s;
vector<tuple<int, int, int>> runs;
template <const int p> constexpr int dec(int a, int b) { return (a -= b) < 0 ? a + p : a; }
template <const int p> constexpr int inc(int a, int b) { return (a += b) >= p ? a - p : a; }
template <const int p> void initpow(int *pw) {
  pw[0] = 1;
  for (int i = 1; i <= n; i++) pw[i] = (ll)pw[i - 1] * px % p;
}
template <const int p> void init(int *h) {
  h[0] = 0;
  for (int i = 1; i <= n; i++) h[i] = ((ll)h[i - 1] * px + s[i - 1]) % p;
}
inline bool equal(int l0, int r0, int l1, int r1) {
  if (((ll)h0[l0] * pw0[r0 - l0 + 1] - h0[r0 + 1] - (ll)h0[l1] * pw0[r1 - l1 + 1] + h0[r1 + 1]) % p0) return false;
  if (((ll)h1[l0] * pw1[r0 - l0 + 1] - h1[r0 + 1] - (ll)h1[l1] * pw1[r1 - l1 + 1] + h1[r1 + 1]) % p1) return false;
  return true;
}
inline bool diff(int la, int ra, int lb, int rb) {
  int na = ra - la + 1, nb = rb - lb + 1, n = std::min(na, nb), l = 1, r = n, mid, res = 0;
  while (l <= r) {
    mid = (l + r) >> 1;
    equal(la, la + mid - 1, lb, lb + mid - 1) ? (res = mid, l = mid + 1) : (r = mid - 1);
  }
  return res == n ? na < nb : s[la + res] < s[lb + res];
}
inline int lcs(int i, int j) {
  int l = 1, r = std::min(i, j) + 1, mid, res = 0;
  while (l <= r) {
    mid = (l + r) >> 1;
    equal(i - mid + 1, i, j - mid + 1, j) ? (res = mid, l = mid + 1) : (r = mid - 1);
  }
  return res;
}
inline int lcp(int i, int j) {
  int l = 1, r = n - std::max(i, j), mid, res = 0;
  while (l <= r) {
    mid = (l + r) >> 1;
    equal(i, i + mid - 1, j, j + mid - 1) ? (res = mid, l = mid + 1) : (r = mid - 1);
  }
  return res;
}
void lyndon(int *res) {
  stk[top = 1] = res[n - 1] = n - 1;
  for (int i = n - 2; i >= 0; i--) {
    stk[++top] = i;
    while (top > 1 && diff(i, stk[top], stk[top] + 1, stk[top - 1])) top--;
    res[i] = stk[top];
  }
}
} // namespace Runs
using namespace Runs;
int main() {
#ifdef memset0
  freopen("runs.in", "r", stdin);
#endif
  ios::sync_with_stdio(0), cin.tie(0);
  cin >> s, n = s.length();
  initpow<p0>(pw0);
  initpow<p1>(pw1);
  for (int _ = 0; _ < 2; _++) {
    for (int i = 0; i < n; i++) s[i] = 128 - s[i];
    init<p0>(h0);
    init<p1>(h1);
    lyndon(la);
    for (int i = 0, j, l, r; i < n; i++) {
      j = la[i], l = i - lcs(i - 1, j), r = j + lcp(i, j + 1);
      if (r - l + 1 >= (j - i + 1 << 1)) runs.emplace_back(std::make_tuple(l, r, j - i + 1));
    }
  }
  sort(runs.begin(), runs.end());
  runs.erase(unique(runs.begin(), runs.end()), runs.end());
  cout << runs.size() << endl;
  for (int i = 0; i < runs.size(); i++) {
    cout << get<0>(runs[i]) + 1 << ' ' << get<1>(runs[i]) + 1 << ' ' << get<2>(runs[i]) << '\n';
  }
}