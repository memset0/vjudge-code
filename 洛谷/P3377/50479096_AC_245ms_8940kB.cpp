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
      int fx = find(x), fy = find(y);
      if (fx == fy || mrk[x] || mrk[y]) continue;
      // if (q[fx].valize() < q[fy].valize()) swap(x, y), swap(fx, fy);
      fa[fy] = fx, q[fx].join(q[fy]);
    } else {
      cin >> x;
      if (mrk[x]) {
        cout << -1 << endl;
        continue;
      }
      int fx = find(x);
      cout << q[fx].top().val << endl;
      mrk[q[fx].top().id] = 1;
      q[fx].pop();
    }
  }
}