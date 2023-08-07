#include <bits/stdc++.h>
using namespace std;
const int N = 5e2 + 9;
int T, n, m, k, a[N];
struct atom {
  int res, id;
  inline bool operator<(const atom &rhs) const { return res == rhs.res ? id < rhs.id : res < rhs.res; }
};
multiset<atom> st;
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
    assert(m >= n - 1);
    st.clear();
    for (int i = 1; i <= n; i++) {
      cin >> a[i];
      st.insert({a[i], i});
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
}