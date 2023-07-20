#include <bits/stdc++.h>
#define ull get_hash
using namespace std;

const int N = 1e6 + 9;
int T, n, k;
string a[N];
vector<pair<int, int>> pos;

inline string get_string(int x) {
  if (x == -1) return "";
  auto [i, j] = pos[x];
  return string(a[i].begin(), a[i].begin() + j + 1);
}

inline bool check(string v) {
  // cerr << "=== check " << v << " ===" << endl;
  int m = k;
  vector<string> res;
  for (int i = 1; i <= n; i++) {
    int jj = -1;
    bool gt = false, lt = false;
    for (int j = 0; j < v.length() && j < a[i].length(); j++)
      if (a[i][j] > v[j]) {
        gt = true, jj = j;
        break;
      } else if (a[i][j] < v[j]) {
        lt = true;
        break;
      }
    if (!gt && !lt) {
      if (a[i].length() > v.length()) gt = true, jj = v.length();
      if (a[i].length() < v.length()) lt = true;
    }
    // cerr << i << " : " << gt << " " << lt << " " << jj << endl;
    if (lt || (!gt && !lt)) {
      m--;
      continue;
    }
    res.push_back(string(a[i].begin(), a[i].begin() + jj + 1));
  }
  // cerr << "! m = " << m << endl;
  // for (int i = 0; i < res.size(); i++) cerr << res[i] << endl;
  sort(res.begin(), res.end());
  for (int i = 0; i < res.size(); i++)
    if (i == 0 || res[i] != res[i - 1]) {
      m--;
    }
  // cerr << "! m = " << m << endl;
  return m <= 0;
}

int main() {
#ifdef memset0
  freopen("E.in", "r", stdin);
#endif
  cin >> T;
  while (T--) {
    pos.clear();

    cin >> n >> k;
    for (int i = 1; i <= n; i++) {
      cin >> a[i];
    }
    sort(a + 1, a + n + 1);
    for (int i = 1; i <= n; i++) {
      bool fl = i > 1;
      for (int j = 0; j < a[i].length(); j++) {
        if (fl && a[i][j] != a[i - 1][j]) {
          fl = false;
        }
        if (!fl) {
          pos.emplace_back(i, j);
          // cerr << ">> " << i << " " << j << " " << get_string((int)pos.size() - 1) << endl;
        }
      }
    }
    int l = 0, r = (int)pos.size(), mid, ans = -114514;
    while (l <= r) {
      mid = (l + r) >> 1;
      (check(get_string(mid - 1))) ? (ans = r = mid - 1) : (l = mid + 1);
    }
    assert(ans != -114514);
    string out = get_string(ans);
    cout << (out.length() ? out : "EMPTY") << endl;
  }
}