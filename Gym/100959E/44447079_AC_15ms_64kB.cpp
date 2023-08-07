#include <bits/stdc++.h>
using namespace std;
const int N = 1e3 + 9;
int n, a[N];
long long sum;
int main() {
#ifdef memset0
  freopen("E.in", "r", stdin);
#endif
  ios::sync_with_stdio(0), cin.tie(0);
  cin >> n;
  multiset<long long> st;
  for (int i = 1; i <= n; i++) {
    cin >> a[i];
    st.insert(a[i]);
  }
  int ans = 0;
  while (true) {
    auto it = st.upper_bound(sum);
    if (it == st.end()) break;
    // cerr << "! " << *it << endl;
    ++ans;
    sum += *it;
  }
  cout << ans << endl;
}