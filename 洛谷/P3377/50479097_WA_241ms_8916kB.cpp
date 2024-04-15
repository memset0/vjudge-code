#include <bits/stdc++.h>
#include <ext/pb_ds/priority_queue.hpp>
#define endl '\n'
using namespace std;
const int N = 1e5 + 9;
int n, m, fa[N];
bool mrk[N];
struct atom {
  int val, id;
  inline bool operator<(const atom &rhs) const { return val == rhs.val ? id > rhs.id : val > rhs.val; }
};
__gnu_pbds::priority_queue<atom> q[N];
int find(int n) { return fa[n] == n ? n : fa[n] = find(fa[n]); }
int main() {
#ifdef memset0
  freopen("heap.in", "r", stdin);
#endif
  cin.tie(0)->sync_with_stdio(0);
  cin >> n >> m;
  for (int x, i = 1; i <= n; i++) {
    cin >> x;
    q[i].push({x, i});
    fa[i] = i;
  }
  for (int x, y; m--;) {
    cin >> x;
    if (x == 1) {
      cin >> x >> y;
      x = find(x), y = find(y);
      if (x == y || mrk[x] || mrk[y]) continue;
      fa[y] = x;
      q[x].join(q[y]);
    } else {
      cin >> x;
      if (mrk[x]) {
        cout << -1 << endl;
        continue;
      }
      x = find(x);
      cout << q[x].top().val << endl;
      mrk[q[x].top().id] = 1;
      q[x].pop();
    }
  }
}