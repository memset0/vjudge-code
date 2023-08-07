#include <bits/stdc++.h>
#define rep(i, l, r) for (int i = (l), i##end = (r); i <= i##end; i++)
#define per(i, l, r) for (int i = (r), i##end = (l); i >= i##end; i--)
using namespace std;
const int N = 2e5 + 10;
int T, n, k;
long long ans, pre[N];
struct node {
  int x, y;
  inline node operator-(const node &rhs) const { return {x - rhs.x, y - rhs.y}; }
  inline long long operator*(const node &rhs) const { return (long long)x * rhs.y - (long long)y * rhs.x; }
  inline bool operator<(const node &rhs) const { return this->operator*(rhs) < 0; }
  inline bool operator==(const node &rhs) const { return this->operator*(rhs) == 0; }
  inline bool operator<=(const node &rhs) const { return this->operator*(rhs) <= 0; }
} a[N];
template <class T> constexpr T abs(T x) { return x < 0 ? -x : x; }
inline long long s(const node &a, const node &b, const node &c) { return (b - a) * (c - a); }
int main() {
#ifdef memset0
  freopen("E.in", "r", stdin);
#endif
  cin >> T;
  while (T--) {
    cin >> n >> k;
    for (int i = 1; i <= n; i++) {
      cin >> a[i].x >> a[i].y;
      a[n + i] = a[i];
    }
    for (int i = 2; i <= (n << 1); i++) {
      pre[i] = pre[i - 1] + s(a[1], a[i - 1], a[i]);
    }
    ans = 0;
    for (int i = 1, j = i + k + 1; i <= n; i++) {
      while (j < i + k + 1) j++;
      while (j + 1 < i + n && abs(s(a[i], a[i + k], a[j + 1])) > abs(s(a[i], a[i + k], a[j]))) j++;
      long long cov = pre[i + k] - pre[i] + s(a[1], a[i + k], a[i]);
      ans = max(ans, abs(cov) + abs(s(a[i], a[i + k], a[j])));
    }
    if (ans & 1) {
      cout << (ans >> 1) << ".5" << endl;
    } else {
      cout << (ans >> 1) << endl;
    }
  }
}