#include <bits/stdc++.h>
using namespace std;
const int N = 1e6 + 9, K = 10;
int k, tot = 1, n[K], pos[1 << K];
vector<tuple<int, int, int>> sta;
struct node : array<int, K> {
  node() { std::fill(this->begin(), this->end(), 0); }
  inline void move(const node &rhs) const {
    for (int x, i = 0; i < k; i++)
      if (x = rhs[i] - this->operator[](i)) {
        cout << i + 1 << ' ' << (x == 1 ? '+' : '-') << '\n';
      }
  }
  inline bool check(const node &rhs) const {
    bool fl = false;
    for (int i = 0; i < k; i++)
      if (rhs[i] != this->operator[](i)) {
        int x = rhs[i] - this->operator[](i);
        if (fl || (x != 1 && x != -1)) {
          return false;
        }
        fl = true;
      }
    return fl;
  }
} s, ans[N];
vector<pair<int, int>> solve2(int n, int m) {
  vector<pair<int, int>> res;
  for (int i = 0; i < n; i++) res.emplace_back(i, 0);
  for (int i = n - 1; i >= 1; i -= 2) {
    for (int j = 1; j <= m - 1; j++) res.emplace_back(i, j);
    for (int j = m - 1; j >= 1; j--) res.emplace_back(i - 1, j);
  }
  return res;
}
void solve(int x) {
  int popc = 0;
  for (int i = 0; i < k; i++) {
    popc += (x >> i) & 1;
  }
  if (popc == 2) {
    int n0, n1, i0 = -1, i1;
    for (int i = 0; i < k; i++)
      if ((x >> i) & 1) {
        if (i0 == -1) {
          n0 = n[i], i0 = i;
        } else {
          n1 = n[i], i1 = i;
        }
      }
    if (n0 & 1) {
      swap(n0, n1);
      swap(i0, i1);
    }
    auto tmp = solve2(n0, n1);
    for (int i = 0; i < tmp.size(); i++) {
      ans[i][i0] = tmp[i].first;
      ans[i][i1] = tmp[i].second;
    }
    return;
  } else {
    int tot = 1;
    for (int u = 0; u < k; u++)
      if ((x >> u) & 1) {
        tot *= n[u];
      }
    for (int u = 0; u < k; u++)
      if ((x >> u) & 1) {
        int y = x ^ (1 << u);
        if (!pos[y]) {
          continue;
        }
        solve(y);
        sta.emplace_back(x, u, tot);
        break;
      }
  }
}
int main() {
#ifdef memset0
  freopen("E.in", "r", stdin);
#endif
  cin >> k;
  for (int i = 0; i < k; i++) cin >> n[i], tot *= n[i];
  for (int i = 0; i < k; i++) cin >> s[i], --s[i];
  if (tot == 1) {
    cout << "Yes" << endl;
    return 0;
  }
  for (int x = 0; x < (1 << k); x++) {
    vector<int> bit;
    for (int i = 0; i < k; i++)
      if ((x >> i) & 1) {
        bit.push_back(n[i]);
      }
    if (bit.size() <= 1) {
      continue;
    } else if (bit.size() == 2) {
      if ((bit[0] & 1) && (bit[1] & 1)) {
        pos[x] = false;
      } else {
        pos[x] = true;
      }
    } else {
      for (int i = 0; i < k; i++)
        if (((x >> i) & 1) && pos[x ^ (1 << i)]) {
          pos[x] = true;
        }
    }
    // cout << x << " " << bit.size() << " " << pos[x] << endl;
  }
  int g = (1 << k) - 1;
  for (int i = 0; i < k; i++)
    if (n[i] == 1) {
      g ^= 1 << i;
    }
  if (!pos[g]) {
    cout << "No" << endl;
    return 0;
  }
  solve(g);
  for (auto [x, u, tot] : sta) {
    int m = n[u], p = 0;
    // fprintf(stderr, "x=%d u=%d tot=%d m=%d \n", x, u, tot, m);
    for (int i = 1; i < tot / m; i++) {
      ans[tot - i] = ans[i];
    }
    for (int j = 1; j <= m - 1; j++) {
      ans[++p] = ans[0];
      ans[p][u] = j;
    }
    for (int i = 1; i < tot / m; i++) {
      if (i & 1) {
        for (int j = m - 1; j >= 1; j--) {
          ans[++p] = ans[tot - i];
          ans[p][u] = j;
        }
      } else {
        for (int j = 1; j <= m - 1; j++) {
          ans[++p] = ans[tot - i];
          ans[p][u] = j;
        }
      }
    }
    // for (int i = 0; i < tot; i++)
    //   for (int j = 0; j < k; j++) cerr << ans[i][j] << " \n"[j + 1 == k];
  }

  cout << "Yes" << endl;
  for (int i = 0; i < tot; i++)
    if (ans[i] == s) {
      for (int j = i; j + 1 < tot; j++) ans[j].move(ans[j + 1]);
      ans[tot - 1].move(ans[0]);
      for (int j = 0; j < i; j++) ans[j].move(ans[j + 1]);
      break;
    }

  // cerr << "!!! ans !!!" << endl;
  // for (const auto &it : ans) {
  //   for (int i = 0; i < k; i++) cerr << it[i] << " \n"[i + 1 == k];
  // }
  // for (int i = 0; i + 1 < tot; i++) {
  //   assert(ans[i].check(ans[i + 1]));
  // }
  // vector<node> fin;
  // for (int i = 0; i < tot; i++)
  //   if (ans[i] == s) {
  //     for (int j = i; j < tot; j++) fin.push_back(ans[j]);
  //     for (int j = 0; j < i; j++) fin.push_back(ans[j]);
  //     fin.push_back(s);
  //   }
  // for (int i = 0; i + 1 < fin.size(); i++) {
  //   fin[i].move(fin[i + 1]);
  // }
  // cerr << "!!! fin !!!" << endl;
  // for (const auto &it : fin) {
  //   for (int i = 0; i < k; i++) cerr << it[i] << " \n"[i + 1 == k];
  // }
  // for (int i = 0; i + 1 < fin.size(); i++) {
  //   assert(fin[i].check(fin[i + 1]));
  // }
}