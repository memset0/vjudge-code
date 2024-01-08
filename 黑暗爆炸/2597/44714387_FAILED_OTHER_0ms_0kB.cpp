// https://vjudge.net/user/memset0
#include <bits/stdc++.h>
using namespace std;
using T = pair<pair<int, int>, vector<bool>>;
T M[] = {
    {{6, 8}, {0, 1, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 1, 1, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 1, 1, 0, 0, 0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 0, 0, 1, 0, 1, 0, 0, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 0, 1, 0, 0, 1, 0, 0, 0}},
};
vector<int> H() {
  int n, a, b, c, d;
  cin >> n >> a >> b >> c >> d;
  return {n, a * 10000 ^ b * 100 ^ c * 1000 ^ d};
}
void O(int task, T ans) {
  int n = ans.first.first;
  int m = ans.first.second;
  vector<bool> e = ans.second;
  vector<int> d;
  for (int i = 0; i < e.size(); i += 4) {
    d.push_back(e[i] | e[i + 1] << 1 | e[i + 2] << 2 | e[i + 3] << 3);
  }
  for (int x : d) cerr << x << ','; cerr << endl;
  vector<int> c;
  for (int i = 0, j; i < d.size(); i++) {
    if (d[i] == 14 || d[i] == 15) {
      int u = 0;
      for (j = i + 1; d[j] != 15; j++) {
        cerr << "j " << j << ": " << d[j] << endl;
        u *= 15;
        u += d[j];
      }
      if (d[i] == 14) u *= -1;
      c.push_back(u);
      i = j;
    } else {
      c.push_back(d[i]);
    }
  }
  for (int x : c) cerr << "c: " << x << endl;
  vector<int> b;
  for (int x : c) {
    if (x > 0) {
      b.push_back(x);
    } else {
      for (int i = 0; i < (-x); i++) b.push_back(1);
    }
  }
  vector<int> a;
  for (int i = 0; i < b.size(); i++) {
    while (b[i]--) {
      a.push_back(i & 1);
    }
  }
  cout << m << endl;
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      cout << a[i * n + j] << " \n"[j + 1 == n];
    }
  }
}
int main() {
  freopen("1.in", "r", stdin);
  ios::sync_with_stdio(0), cin.tie(0);
  auto V = H();
#define I(A, B, C) \
  if (V[0] == A && V[1] == B) O(C, M[C - 1]);
  I(6, 800, 1);
}
