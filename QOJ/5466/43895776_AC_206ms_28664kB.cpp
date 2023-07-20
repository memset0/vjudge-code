#include <bits/stdc++.h>
using namespace std;
const int N = 2e5 + 9;
int T, n, m, k, res, a[N], b[N], loc[N];
bool tag[N];
struct node {
  int l, r, mid;
  int max, len;
} p[N << 2];
void build(int u, int l, int r) {
  p[u].l = l, p[u].r = r, p[u].mid = (l + r) >> 1;
  p[u].len = r - l + 1;
  if (l == r) {
    p[u].max = a[l];
    return;
  }
  build(u << 1, l, p[u].mid);
  build(u << 1 | 1, p[u].mid + 1, r);
  p[u].max = max(p[u << 1].max, p[u << 1 | 1].max);
}
void modify(int u, int k) {
  p[u].len--;
  if (p[u].l == p[u].r) {
    p[u].max = 0;
    return;
  }
  if (k <= p[u].mid) {
    modify(u << 1, k);
  } else {
    modify(u << 1 | 1, k);
  }
  p[u].max = max(p[u << 1].max, p[u << 1 | 1].max);
}
int queryL(int u, int k, int x) {
  if (p[u].r <= k && p[u].max <= x) {
    res += p[u].len;
    return p[u].max;
  }
  if (p[u].l == p[u].r) return p[u].max;
  if (k <= p[u].mid) return queryL(u << 1, k, x);
  int t = queryL(u << 1 | 1, k, x);
  if (t <= x) return max(t, queryL(u << 1, k, x));
  return t;
}
int queryR(int u, int k, int x) {
  if (p[u].l >= k && p[u].max <= x) {
    res += p[u].len;
    return p[u].max;
  }
  if (p[u].l == p[u].r) return p[u].max;
  if (k > p[u].mid) return queryR(u << 1 | 1, k, x);
  int t = queryR(u << 1, k, x);
  if (t <= x) return max(t, queryR(u << 1 | 1, k, x));
  return t;
}
int main() {
#ifdef memset0
  freopen("L.in", "r", stdin);
  // freopen("L.out", "w", stdout);
#endif
  ios::sync_with_stdio(0), cin.tie(0);
  cin >> T;
  while (T--) {
    cin >> n >> m >> k;
    fill(tag + 1, tag + n + 1, true);
    for (int i = 1; i <= n; i++) {
      cin >> a[i];
      loc[a[i]] = i;
    }
    for (int i = 1; i <= m; i++) {
      cin >> b[i];
      tag[loc[b[i]]] = false;
    }
    multiset<int> st;
    for (int x, i = 1; i <= k; i++) {
      cin >> x;
      st.insert(-x);
    }
    vector<pair<int, int>> task;
    vector<int> c(1);
    for (int i = 1; i <= n; i++)
      if (tag[i]) {
        task.emplace_back(a[i], i);
      } else {
        c.push_back(a[i]);
      }
    bool possible = true;
    for (int i = 1; i <= m; i++)
      if (b[i] != c[i]) {
        possible = false;
      }
    sort(task.begin(), task.end());
    build(1, 1, n);
    for (int lx, rx, k = (int)task.size() - 1; possible && k >= 0; k--) {
      int i = task[k].second;
      res = 0, queryL(1, i, a[i]), lx = res;
      res = 0, queryR(1, i, a[i]), rx = res;
      // fprintf(stderr, "i=%d : %d %d\n", i, lx, rx);
      modify(1, i);
      int cur = lx + rx - 1;
      auto it = st.lower_bound(-cur);
      if (it != st.end()) {
        st.erase(it);
      } else {
        possible = false;
      }
    }
    cout << (possible ? "YES" : "NO") << endl;
  }
}