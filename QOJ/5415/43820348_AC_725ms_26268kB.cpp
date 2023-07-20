#include <bits/stdc++.h>
using namespace std;
const int N = 5e5 + 9, M = 3e3 + 9;
int T, n, k, q, a[N];
bool tag[N];
long long preans, ans[M], f[N], g[N], ff[M], gg[M];
string s;
vector<pair<int, int>> qry[N];
vector<pair<long long, pair<int, int>>> segans;
long long solve(int l, int r) {
  // cerr << "solve " << l << " " << r << endl;
  multiset<long long> st;
  int al = a[l], ar = a[r];
  a[l] = a[r] = 0;
  f[l] = 0;
  for (int i = l + 1; i <= r; i++) {
    st.insert(f[i - 1]);
    if (i - k - 1 >= l) {
      st.erase(st.find(f[i - k - 1]));
    }
    f[i] = (*st.begin()) + a[i];
  }
  while (st.size()) st.erase(st.begin());
  g[r] = 0;
  for (int i = r - 1; i >= l; i--) {
    st.insert(g[i + 1]);
    if (i + k + 1 <= r) {
      st.erase(st.find(g[i + k + 1]));
    }
    g[i] = (*st.begin()) + a[i];
  }
  // for (int i = l; i <= r; i++) cerr << f[i] << " \n"[i == r];
  // for (int i = l; i <= r; i++) cerr << g[i] << " \n"[i == r];
  assert(f[r] == g[l]);
  for (int p = l + 1; p <= r - 1; p++) {
    for (const auto &[v, i] : qry[p]) {
      ans[i] = f[p] + g[p] - 2 * a[p] + v;
      ff[0] = gg[0] = ff[k] = gg[k] = 1e16;
      for (int i = 1; i < k; i++) {
        ff[i] = p - i >= l ? f[p - i] : (long long)1e16;
        gg[i] = p + i <= r ? g[p + i] : (long long)1e16;
        ff[i] = min(ff[i], ff[i - 1]);
        gg[i] = min(gg[i], gg[i - 1]);
      }
      for (int j = 1; j < k; j++) {
        ans[i] = min(ans[i], ff[j] + gg[k - j]);
      }
    }
  }
  a[l] = al, a[r] = ar;
	return f[r];
}
int main() {
#ifdef memset0
  freopen("B.in", "r", stdin);
#endif
  ios::sync_with_stdio(0), cin.tie(0);
  cin >> T;
  while (T--) {
    preans = 0, segans.clear();
    cin >> n >> k;
    for (int i = 1; i <= n; i++) {
      cin >> a[i];
      tag[i] = false;
      qry[i].clear();
    }
    cin >> s >> q;
    for (int p, v, i = 1; i <= q; i++) {
      cin >> p >> v;
      ans[i] = 0;
      qry[p].emplace_back(v, i);
    }
    for (int i = 1; i <= n; i++)
      if (s[i - 1] == '1') {
        tag[i] = true;
				preans += a[i];
      }
    tag[0] = tag[n + 1] = true;
    for (int l = 0, r; l < n + 1; l = r) {
      r = l + 1;
      while (!tag[r]) ++r;
      segans.emplace_back(solve(l, r), make_pair(l, r));
      preans += segans.back().first;
    }
    for (const auto &[w, seg] : segans) {
      const auto &[l, r] = seg;
      for (int p = l + 1; p <= r - 1; p++) {
        for (const auto &[v, i] : qry[p]) {
          ans[i] = preans - w + ans[i];
        }
      }
    }
    for (int p = 1; p <= n; p++)
      if (tag[p]) {
        for (const auto &[v, i] : qry[p]) {
          ans[i] = preans - a[p] + v;
        }
      }
    for (int i = 1; i <= q; i++) {
      cout << ans[i] << endl;
    }
  }
}