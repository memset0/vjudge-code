#include <bits/stdc++.h>
using namespace std;

const int n = 22680, N = n + 9;
int T;
long long l, r, f[N];

long long solve(long long a) { return f[n] * (a / n) + f[a % n]; }

int main() {
  ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
  for (int i = 1; i <= n; i++)
    if (i * ((i - 1) % 9 + 1) <= n) {
      f[i * ((i - 1) % 9 + 1)] = 1;
    }
  for (int i = 1; i <= n; i++) {
    f[i] += f[i - 1];
  }
  cin >> T;
  while (T--) {
    cin >> l >> r;
    cout << solve(r) - solve(l - 1) << endl;
  }
}