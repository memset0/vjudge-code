#include <bits/stdc++.h>
#define rep(i, l, r) for (int i = (l), i##end = (r); i <= i##end; i++)
#define per(i, l, r) for (int i = (l), i##end = (r); i >= i##end; i--)
using namespace std;
int a, b, s;
int main() {
#ifdef memset0
  freopen("1.in", "r", stdin);
#endif
  ios::sync_with_stdio(0), cin.tie(0);
  while (true) {
    cin >> a >> b, s = 1, a %= 1000;
    if (!a && !b) break;
    while (b) {
      if (b & 1) s = s * a % 1000;
      a = a * a % 1000, b >>= 1;
    }
    cout << s << endl;
  }
}