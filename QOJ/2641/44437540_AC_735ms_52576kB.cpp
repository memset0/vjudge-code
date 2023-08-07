#include <bits/stdc++.h>
using namespace std;
const int N = 1e6 + 9;
int n;
char str[N], ans[N];
set<int> s;
int main() {
#ifdef memset0
  freopen("J2.in", "r", stdin);
#endif
  scanf("%s", str + 1);
  n = strlen(str + 1);
  for (int i = 1; i <= n; i++) s.insert(i);
  for (int i = 1; i <= n; i++) {
    int c = str[i] - '0';
    if (s.count(i)) {
      s.erase(i);
    } else {
      c++;
    }
    // fprintf(stderr, "i=%d c=%d\n", i, c);
    while (c >= 2) {
      if (!s.count(0)) s.insert(0);
      if (!s.count(n + 1)) s.insert(n + 1);
      // for (int x : s) cerr << ">" << x;
      // cerr << endl;
      // assert(s.lower_bound(i) != s.begin());
      // assert(s.upper_bound(i) != s.end());
      auto lt = --s.lower_bound(i);
      int l = *lt;
      s.erase(lt);
      auto rt = s.upper_bound(i);
      int r = *rt;
      s.erase(rt);
      // cerr << i << " " << c << " " << l << " " << r << endl;
      int x = min(r - i - 1, i - l - 1);
      l += x, r -= x;
      // assert(x >= 0);
      // cerr << i << " " << c << " " << l << " " << r << endl;
      if (l == i - 1 && r == i + 1) {
        c -= 2;
      } else if (l == i - 1) {
        c -= 1;
        // cerr << "insert " << r - 1 << endl;
        s.insert(r - 1);
      } else if (r == i + 1) {
        c -= 1;
        // cerr << "insert " << l + 1 << endl;
        s.insert(l + 1);
      } else {
        assert(false);
      }
    }
    if (c == 0) s.insert(i);
    // for (int i = 1; i <= n; i++) ans[i] = '1';
    // for (int x : s) ans[x] = '0';
    // for (int i = 1; i <= n; i++) putchar(ans[i]);
    // putchar('\n');
  }
  for (int i = 1; i <= n; i++) ans[i] = '1';
  for (int x : s)
    if (1 <= x && x <= n) {
      ans[x] = '0';
    }
  for (int i = 1; i <= n; i++) putchar(ans[i]);
  putchar('\n');
}

/*
10000000
01100000
10110000
10110000
10110000
10111010
10111101
10111111
10111111
*/