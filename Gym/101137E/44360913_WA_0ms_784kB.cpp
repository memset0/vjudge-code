#include <bits/stdc++.h>
using namespace std;
const int N = 2e5 + 9;
int n, a[N];
set<int> st;
vector<string> ans;
int main() {
#ifdef memset0
  freopen("E.in", "r", stdin);
#endif
  ios::sync_with_stdio(0), cin.tie(0);
  cin >> n;
  for (int i = 1; i <= n; i++) {
    cin >> a[i];
    st.insert(a[i]);
  }
  sort(a + 1, a + n + 1);
  // for  (int i = 1; i <= n; i++) cerr << a[i] << " \n"[i == n];
  for (int l = 1, r; l <= n; l = r + 1) {
    r = l;
    while (r + 1 <= n && a[r + 1] == a[r] + 1) ++r;
    if (r - l >= 3) {
      int fl = false;
      fl |= !st.count(a[l] - 2) && !st.count(a[r] + 2);
      fl |= !st.count(a[r] + 2) && st.count(a[l] - 2) && !st.count(a[l] - 4);
      fl |= r - l > 3 && !st.count(a[l] - 2) && st.count(a[r] + 2) && !st.count(a[r] + 4);
      fl |= r - l > 3 && !st.count(a[r] + 2) && st.count(a[l] - 2) && st.count(a[l] - 4) && !st.count(a[l] - 6);
      if (fl) {
        ans.push_back(to_string(a[l]) + "-" + to_string(a[r]));
        for (int i = l; i <= r; i++) a[i] = -1;
      }
    }
  }
  // for (int i = 1; i <= n; i++) cerr << a[i] << " \n"[i == n];

  auto solve = [&](vector<int> &a, char t) {
    for (int l = 0, r; l < a.size(); l = r + 1) {
      r = l;
      while (r + 1 < a.size() && a[r + 1] == a[r] + 2) ++r;
      if (l == r) {
        ans.push_back(to_string(a[l]));
      } else {
        ans.push_back(to_string(a[l]) + t + to_string(a[r]));
      }
    }
  };
  for (int k = 0; k < 2; k++) {
    vector<int> lst;
    for (int i = 1; i <= n; i++)
      if (a[i] != -1 && a[i] % 2 == k) lst.push_back(a[i]);
    solve(lst, k ? '#' : '%');
  }

  for (int i = 0; i < ans.size(); i++) {
    if (i) cout << ',';
    cout << ans[i];
  }
  cout << endl;
}

/*
11,21,20,14-18,4%10,1#5
14-18,4%10,20,1#5,11,21
*/