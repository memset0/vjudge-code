// 打表程序
#include <bits/stdc++.h>
using namespace std;
const vector<int> pri = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71, 73, 79, 83, 89, 97};
const int P = 25;
const long long inf = 1e18;
int ans, cnt[P];
vector<pair<long long, int>> f, g;
void dfs2(int l, int r, long long x, int y, int s) {
  // fprintf(stderr, "G :: m=%d x=%lld y=%d s=%d\n", m, x, y, s);
  g.emplace_back(x, y);
  if (s == 0) return;
  for (int i = l; i <= r; i++)
    if (cnt[i]) {
      if ((__int128)x / pri[i] * pri[i + 1] > inf) continue;
      (x /= pri[i]) *= pri[i + 1];
      (y /= cnt[i] + 1) /= cnt[i + 1] + 1;
      --cnt[i], ++cnt[i + 1];
      // fprintf(stderr, "choose %d %d : %d %d\n", i, y, cnt[i], cnt[i + 1]);
      dfs2(i, i == r ? r + 1 : r, x, y * (cnt[i] + 1) * (cnt[i + 1] + 1), s - 1);
      ++cnt[i], --cnt[i + 1];
      (y *= cnt[i] + 1) *= cnt[i + 1] + 1;
      (x /= pri[i + 1]) *= pri[i];
    }
}
void dfs(int i, long long x, int y) {
  // fprintf(stderr, "F :: i=%d x=%lld y=%d\n", i, x, y);
  f.emplace_back(x, y);
  if (i) {
    dfs2(0, i - 1, x, y, 6);
  }
  for (int c = 1; c <= i ? cnt[i - 1] : 114514; c++) {
    if ((__int128)x * pri[i] > inf) break;
    x *= pri[i];
    cnt[i] = c;
    dfs(i + 1, x, y * (c + 1));
    cnt[i] = 0;
  }
}
inline void found(long long x) {
  cerr << x << endl;
  cout << x << "," << '\n';
  ++ans;
}
int main() {
#ifdef memset0
  freopen("A.in", "r", stdin);
  freopen("A-upload.cpp", "w", stdout);
#endif
  ios::sync_with_stdio(0), cin.tie(0);
  dfs(0, 1, 1);

  // vector<pair<long long, int>> t;
  // t.swap(f);
  // sort(t.begin(), t.end());
  // for (const auto &it : t) {
  //   if (f.empty() || it.second >= f.back().second) f.push_back(it);
  // }
  // for (const auto &it : f) {
  //   cout << it.first << " " << it.second << endl;
  // }

  sort(g.begin(), g.end());
  multiset<int> st;
  long long lst = -1;
  cout << "#include <bits/stdc++.h>\n"
       << "using namespace std;\n";
  cout << "vector<long long> ans = {" << endl;
  found(1);
  for (const auto &[x, y] : g) {
    if (x == lst) continue;
    // cerr << "! " << x << " " << y << endl;
    lst = x;
    auto it = st.upper_bound(y);
    if (it == st.end()) {
      st.insert(y);
      found(x);
    } else {
      ++it;
      if (it == st.end()) {
        st.insert(y);
        found(x);
      }
    }
  }
  cerr << "count: " << ans << endl;
  cout << "};\n"
       << "int main() {\n"
       << "#ifdef memset0\n"
       << "  freopen(\"A.in\", \"r\", stdin);\n"
       << "#endif\n"
       << "  int n;\n"
       << "  cin >> n, --n;\n"
       << "  cout << (n < ans.size() ? ans[n] : -1) << endl;\n"
       << "}\n"
       << endl;
}