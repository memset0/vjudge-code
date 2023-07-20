#include <bits/stdc++.h>
#define each(x, a) for (auto &x : (a))
#define rep(i, l, r) for (int i = (l), i##end = (r); i <= i##end; i++)
#define per(i, r, l) for (int i = (r), i##end = (l); i >= i##end; i--)
using namespace std;

const int N = 1e5 + 9;
int k, n, a[N];

int main() {
#ifdef memset0
  freopen("E.in", "r", stdin);
#endif
  ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
  cin >> n >> k;
  for (int i = 1; i <= n; i++) {
    cin >> a[i];
    if (a[i] < k) {
      printf("Python 3.%d will be faster than C++\n", i);
      return 0;
    }
  }
  if (a[n - 1] > a[n]) {
    int t = a[n - 1] - a[n];
    int m = a[n] - k;
    // cerr << "! " << m << " " << t << endl;
    printf("Python 3.%d will be faster than C++\n", n + m / t + 1);
    return 0;
  }
  cout << "Python will never be faster than C++" << endl;
}