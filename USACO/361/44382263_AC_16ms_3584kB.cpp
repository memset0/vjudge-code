#include <bits/stdc++.h>
using namespace std;
const int N = 1.5e4 + 9;
struct love {
  int milk, time;
} you[N];
int cmp(love x, love y) { return x.milk > y.milk; }
int n, ans, tot, a[N];
int main() {
  freopen("msched.in", "r", stdin);
  freopen("msched.out", "w", stdout);
  ios::sync_with_stdio(0), cin.tie(0);
  cin >> n;
  for (int i = 1; i <= n; i++) {
    cin >> you[i].milk >> you[i].time;
  }
  sort(you + 1, you + 1 + n, cmp);
  for (int i = 1; i <= n; i++) {
    tot = 0;
    for (int j = you[i].time; j >= 1; j--) {
      if (a[j] == 0) {
        a[j] = 1;
        tot = 1;
        break;
      }
    }
    if (tot == 1) ans += you[i].milk;
  }
  cout << ans << endl;
}