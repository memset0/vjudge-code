#include <bits/stdc++.h>
using namespace std;
const int N = 1e2 + 9;
int n, m;
struct segment {
  int l, r;
  segment(int x, int y) {
    l = x, r = y;
    if ((r - l + n) % n > (l - r + n) % n || ((r - l + n) % n == (l - r + n) % n && l > r)) { swap(l, r); }
  }
  bool operator==(const segment &rhs) const { return l == rhs.l && r == rhs.r; }
  bool includes(int x) {
    if (l < r) {
      return l < x && x < r;
    } else {
      return (l < x && x < n) || (0 <= x && x < r);
    }
  }
};
vector<segment> seg;
bool check(const segment &cur) {
  // fprintf(stderr, "check : %d %d\n", cur.l + 1, cur.r + 1);
  for (auto &rhs : seg) {
    if (rhs == cur) return false;
    // fprintf(stderr, "> %d %d : %d %d\n", rhs.l + 1, rhs.r + 1, rhs.includes(cur.l), rhs.includes(cur.r));
    if (rhs.l != cur.l && rhs.r != cur.r && rhs.l != cur.r && rhs.r != cur.l && (rhs.includes(cur.l) + rhs.includes(cur.r) == 1)) return false;
  }
  return true;
}
int main() {
#ifdef memset0
  freopen("B.in", "r", stdin);
#endif
  cin.tie(0)->sync_with_stdio(0);
  cin >> n >> m;
  for (int x, y, i = 0; i < m; i++) {
    cin >> x >> y;
    seg.push_back(segment(x - 1, y - 1));
  }
  for (int len = 1; len <= n / 2; len++)
    for (int i = 0; i < n; i++) {
      segment cur(i, (i + len) % n);
      if (check(cur)) { seg.push_back(cur); }
    }
  cout << (seg.size() - m) << endl;
  // for (auto it : seg) cerr << (it.l + 1) << " " << (it.r + 1) << endl;
}