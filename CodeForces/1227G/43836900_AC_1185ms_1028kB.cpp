#include <bits/stdc++.h>
using namespace std;

const int N = 1e3 + 9;
int n, cnt, a[N], id[N];
bool ans[N][N], out[N];

int main() {
#ifdef memset0
  freopen("1.in", "r", stdin);
#endif
  ios::sync_with_stdio(0), cin.tie(0);
  cin >> n;
  for (int i = 1; i <= n; i++) {
    cin >> a[i];
    id[i] = i;
  }
  sort(id + 1, id + n + 1, [&](int i, int j) { return a[i] < a[j]; });

  int m = 1;
  vector<int> todo;
  for (int l = 1, r, x; l <= n; l = r + 1) {
    x = a[id[l]], r = l;
    while (r < n && a[id[r + 1]] == x) ++r;
    cerr << l << " " << r << " " << x << endl;
    if (l == r) {
      todo.push_back(l);
    } else if (r - l + 1 > x) {
      const auto fit = [&](int k) { return k > r ? k - r - 1 + l : k; };
      for (int i = l; i <= r; i++) {
        for (int j = 1; j <= x; j++) {
          ans[m][id[fit(i + j - 1)]] = true;
        }
        m++;
      }
    } else {
      int sz = min<int>(r - l, x);
      cerr << ">>sz " << sz << endl;
      const auto fit = [&](int k) {
        while (k > m + sz) k = k - sz - 1;
        return k;
      };
      for (int i = l; i <= r; i++) {
        for (int j = 1; j <= sz; j++) {
          fprintf(stderr, "[%d][%d] -> %d -> %d\n", i, j, m + j - 1 + i - l, fit(m + j - 1 + i - l));
          ans[fit(m + j - 1 + i - l)][id[i]] = true;
        }
      }
      m += sz + 1;
      if (x > sz) {
        const auto fit2 = [&](int k) { return k > n + 1 ? k - n - 1 : k; };
        for (int i = l; i <= r; i++)
          for (int j = 1; j <= x - sz; j++) {
            ans[fit2(m + j - 1)][id[i]] = true;
          }
      }
    }
  }
  cerr << "!! m = " << m << endl;

  int k = todo.size();
  todo.insert(todo.begin(), -1);
  const auto fit = [&](int k) {
    while (k > n + 1) k = k - n - 2 + m;
    return k;
  };
  for (int i = 1; i <= k; i++) {
    int x = a[id[todo[i]]];
    int mn = max(x - i, 0);
    assert(mn < m);
    fprintf(stderr, "[%d] %d %d %d \n", todo[i], i, x, mn);
    for (int j = 1; j <= mn; j++) {
      ans[j][id[todo[i]]] = true;
      --x;
    }
    // cerr<<"!! "<<x<<endl;
    for (int j = 1; j <= x; j++) {
      ans[fit(m + j - 1)][id[todo[i]]] = true;
    }
  }
  // for (int i = 1; i <= n + 1; i++) {
  //   for (int j = 1; j <= n; j++) cerr << (ans[i][j] ? '1' : '0');
  //   cerr << endl;
  // }

  for (int i = 1; i <= n + 1; i++) {
    out[i] = false;
    for (int j = 1; j <= n; j++)
      if (ans[i][j]) {
        out[i] = true;
        ++cnt;
        break;
      }
  }
  printf("%d\n", cnt);
  for (int i = 1; i <= n + 1; i++)
    if (out[i]) {
      for (int j = 1; j <= n; j++) putchar(48 + ans[i][j]);
      putchar('\n');
    }
}//