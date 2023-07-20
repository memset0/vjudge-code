#include <bits/stdc++.h>
#define rep(i, l, r) for (int i = (l), i##end = (r); i <= i##end; i++)
#define per(i, r, l) for (int i = (r), i##end = (l); i >= i##end; i--)
using namespace std;

const int N = 1e5 + 9;
int T, n, s[N], d[N];
bool found;
multiset<int> st;
vector<int> pos;
vector<pair<int, int>> op;
vector<tuple<int, int, int>> eqs;

void dfs(int k) {
  if (k == op.size()) {
    found = true;
    return;
  }
  vector<int> cur(st.begin(), st.end());
  sort(cur.begin(), cur.end());
  cur.erase(unique(cur.begin(), cur.end()), cur.end());
  // fprintf(stderr, "k=%d :: [%d] ", k, (int)cur.size());
  // for (int x : cur) cerr << x << " ";
  // cerr << endl;

  int v = op[k].first;
  for (int u : cur) {
    int s = u - v + 1;
    // fprintf(stderr, "k=%d u=%d v=%d s=%d\n", k, u, v, s);
    if (s < 0) continue;
    long long m2 = (long long)s * s - 4ll * u;
    if (m2 < 0) continue;
    int m = sqrt(m2);
    if ((long long)m * m != m2) continue;
    if ((s & 1) != (m & 1)) continue;
    int x = (s + m) >> 1;
    int y = (s - m) >> 1;
    st.erase(st.find(u));
    st.insert(x);
    st.insert(y);
    eqs.emplace_back(u, x, y);
    dfs(k + 1);
    if (found) {
      return;
    }
    st.erase(st.find(x));
    st.erase(st.find(y));
    st.insert(u);
    eqs.pop_back();
  }
}

vector<int> construct(int u, int i, int pre) {
  for (; i < eqs.size(); i++)
    if (!pos[i] && get<0>(eqs[i]) == u) {
      pos[i] = -1;
      vector<int> l = construct(get<1>(eqs[i]), i + 1, pre);
      vector<int> r = construct(get<2>(eqs[i]), i + 1, pre + l.size());
      pos[i] = pre + l.size();
      vector<int> res;
      for (int x : l) res.push_back(x);
      for (int x : r) res.push_back(x);
      return res;
    }
  return vector<int>{u};
}

int main() {
#ifdef memset0
  freopen("B.in", "r", stdin);
#endif
  ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
  cin >> n;
  rep(i, 0, n - 1) cin >> s[i];
  if (n == 1) {
    cout << s[0] << endl;
    return 0;
  }
  rep(i, 1, n - 1) {
    d[i] = s[i] - s[i - 1];
    if (d[i] != -1) {
      op.emplace_back(d[i] + 1, i);
    }
  }
  reverse(op.begin(), op.end());
  st.insert(s[n - 1]);
  dfs(0);
  if (!found) {
    cout << -1 << endl;
    cerr << "NOT FOUND" << endl;
    return 0;
  }
  pos.resize(eqs.size());
  // for (auto &[u, x, y] : eqs) cerr << u << " = " << x << " * " << y << endl;
  auto a = construct(s[n - 1], 0, 0);
  while (a.size() < n) {
    a.push_back(1);
  }
  rep(i, 0, n - 1) cout << a[i] << " \n"[i + 1 == n];
  reverse(pos.begin(), pos.end());
  int x = n - 1, y = 0;
  rep(i, 1, n - 1) {
    if (d[i] == -1) {
      cout << x << endl;
      x--;
    } else {
      cout << pos[y] << endl;
      y++;
    }
  }
}