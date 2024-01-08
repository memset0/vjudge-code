#include <bits/stdc++.h>
using namespace std;
int main() {
  int n;
  set<int> st;
  for (int x, i = 0; i <= n; i++) {
    cin >> x;
    st.insert(x);
    if (st.count(x - 1)) {
      cout << x << " " << x - 1 << endl;
      return 0;
    }
    if (st.count(x + 1)) {
      cout << x << " " << x + 1 << endl;
      return 0;
    }
  }
}