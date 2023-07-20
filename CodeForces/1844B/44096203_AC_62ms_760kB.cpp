#include <bits/stdc++.h>
#define ll long long
#define pb push_back
#define eb emplace_back
#define rep(i, l, r) for (int i = (l), i##end = (r); i <= i##end; i++)
#define per(i, r, l) for (int i = (r), i##end = (l); i >= i##end; i--)
using namespace std;

const int N = 2e5 + 9;
int T, n, a[N];

int main() {
#ifdef memset0
  freopen("A.in", "r", stdin);
#endif
  // tag[1] = tag[2] = true;
  // for (int i = 2; i < N; i++)
  //   if (tag[i]) {
  //     for (int j = i + i; j < N; j += i) {
  //       tag[i] = false;
  //     }
  //   }
  cin >> T;
  while (T--) {
    cin >> n;
    fill(a + 1, a + n + 1, 0);
    a[(n + 1) >> 1] = 1;
    if (n > 1) a[n] = 2;
    if (n > 2) a[1] = 3;
    int cnt = 4;
    rep(i, 1, n) if (!a[i]) a[i] = cnt++;
    rep(i, 1, n) cout << a[i] << " \n"[i == n];
  }
}