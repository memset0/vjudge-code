#include <bits/stdc++.h>
using namespace std;
const int N = 5e2 + 9, M = 2.5e7 + 9;
int T, n, m, k, a[N];
bitset<(M << 1)> dp;
struct atom {
  int res, id;
  atom(int res, int id) : res(res), id(id) {}
  inline bool operator<(const atom &rhs) const { return res == rhs.res ? id < rhs.id : res < rhs.res; }
};
multiset<atom> st;
void solve(int m, const vector<atom> &vec) {
  assert(m >= (int)vec.size() - 1);
  st.clear();
  for (const atom &x : vec) {
    st.insert(x);
  }
  for (int i = 1; i <= m; i++) {
    auto it = *st.begin();
    st.erase(st.begin());
    if (it.res >= k) {
      cout << it.id << " " << k << '\n';
      it.res -= k;
      if (it.res) {
        st.insert(it);
      }
    } else {
      auto jt = *--st.end();
      st.erase(--st.end());
      cout << it.id << " " << it.res << " " << jt.id << " " << k - it.res << '\n';
      jt.res -= k - it.res;
      if (jt.res) {
        st.insert(jt);
      }
    }
  }
}
void DP() {
  //    sum_(i=1)^n a_i = (n-1) * k
  // => sum_(i=1)^n (a_i - k) = -k
  dp.reset();
  dp[M] = 1;
  for (int i = 1; i <= n; i++) {
    int x = a[i] - k;
    if (x > 0) {
      dp |= dp << x;
    } else if (x < 0) {
      dp |= dp >> (-x);
    }
  }
  if (dp[M - k] == 0) {
    cout << -1 << endl;
    return;
  }
  vector<atom> vec[2];
  int u = M - k;
  for (int i = n; i >= 1; i--) {
    if (dp[u - (a[i] - k)]) {
      u -= a[i] - k;
      vec[0].emplace_back(a[i], i);
    } else {
      vec[1].emplace_back(a[i], i);
    }
  }
  solve((int)vec[0].size() - 1, vec[0]);
  solve((int)vec[1].size() - 1, vec[1]);
}
int main() {
#ifdef memset0
  freopen("1.in", "r", stdin);
#else
  freopen("dish.in", "r", stdin);
  freopen("dish.out", "w", stdout);
#endif
  ios::sync_with_stdio(0), cin.tie(0);
  cin >> T;
  while (T--) {
    cin >> n >> m >> k;
    for (int i = 1; i <= n; i++) {
      cin >> a[i];
    }
    if (m >= n - 1) {
      vector<atom> vec;
      for (int i = 1; i <= n; i++) vec.emplace_back(a[i], i);
      solve(m, vec);
    } else {
      DP();
    }
  }
}