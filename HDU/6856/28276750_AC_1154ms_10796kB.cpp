#include <bits/stdc++.h>
using namespace std;
const int N = 1e6 + 7;
int n, l, r, l1, r1, l2, r2, a[N], dp[N];
struct node {
  int a, b, t;
} q1[N], q2[N];
inline int read() {
  int num = 0;
  char g = getchar(), t = '+';
  while (g < 48 || 57 < g)
    t = g, g = getchar();
  while (47 < g && g < 58)
    num = num * 10 + g - 48, g = getchar();
  if (t == '-')
    return -num;
  return num;
}
inline bool check(node a, node b) {
  if (a.a < b.a)
    return 1;
  if (a.a == b.a && a.b >= b.b)
    return 1;
  return 0;
}
inline void push(int v) {
  node w;
  w.a = dp[v], w.b = a[v], w.t = v;
  if (dp[v] % 2 == 0) {
    while (r1 >= l1 && check(q1[r1], w))
      r1--;
    q1[++r1] = w;
  } else {
    while (r2 >= l2 && check(q2[r2], w))
      r2--;
    q2[++r2] = w;
  }
}
inline void pop(int v) {
  if (q1[l1].t == v && l1 <= r1)
    l1++;
  if (q2[l2].t == v && l2 <= r2)
    l2++;
}
inline void update(int v) {
  if (l1 <= r1) {
    dp[v] = max(dp[v],
                q1[l1].a + ((a[v] - q1[l1].b) > 0) - ((a[v] - q1[l1].b) < 0));
  }
  if (l2 <= r2) {
    dp[v] = max(dp[v],
                q2[l2].a + ((a[v] - q2[l2].b) > 0) - ((a[v] - q2[l2].b) < 0));
  }
}
int main() {
  int t = read();
  while (t--) {
    n = read(), l = read(), r = read(), l1 = 1, r1 = 0, l2 = 1, r2 = 0;
    for (int i = 1; i <= n; i++)
      a[i] = read(), a[i] += a[i - 1], dp[i] = -n;
    for (int i = l; i <= n; i++) {
      push(i - l), update(i);
      if (i - r >= 0)
        pop(i - r);
    }
    cout << dp[n] << endl;
  }
}