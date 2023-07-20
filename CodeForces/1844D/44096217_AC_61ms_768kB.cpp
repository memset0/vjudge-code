#include <bits/stdc++.h>
#define ll long long
#define pb push_back
#define eb emplace_back
#define rep(i, l, r) for (int i = (l), i##end = (r); i <= i##end; i++)
#define per(i, r, l) for (int i = (r), i##end = (l); i >= i##end; i--)
using namespace std;

const int N = 2e5 + 9;
int T, n, a[N];

void solve(int n) {
  if (n == 1) {
    putchar('a'), putchar('\n');
    return;
  }
  vector<int> lim;
  for (int i = 1; i < n; i++)
    if (n % i == 0) {
      lim.push_back(i);
    }
  for (int i = 2; i <= 26; i++) {
    bool fl = true;
    for (int x : lim)
      if (i == x) {
        fl = false;
        break;
      }
    if (fl) {
      for (int j = 1; j <= n; j++) {
        putchar((j - 1) % i + 'a');
      }
      putchar('\n');
      return;
    }
  }
  exit(-1);
}

int main() {
#ifdef memset0
  freopen("D.in", "r", stdin);
#endif
  cin >> T;
  while (T--) {
    cin >> n;
    solve(n);
  }
}