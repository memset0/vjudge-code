#include <bits/stdc++.h>
using namespace std;
#define int long long
const int N = 1e6 + 7;
int n, k, a[N], b[N], c[N], op[N];
signed main() {
  scanf("%lld", &n);
  for (int i = 1; i <= n; i++) scanf("%lld", &a[i]);
  for (int i = 1; i <= n; i++) scanf("%lld", &b[i]);
  for (int i = 1; i <= n; i++) scanf("%lld", &c[i]);
  long long S = 0;
  for (int i = 1; i <= n; i++) S += min(a[i], b[i]);
  if (S == 0) {
    long long C = 0;
    for (int i = 1; i <= n; i++) {
      if (a[i] == 0) printf("%lld ", a[i]);
      else
        printf("%lld ", a[i] + c[i]), C += a[i] + c[i];
    }
    cout << endl;
    cout << C << endl;
  } else {
    long long R = 0;
    for (int j = 1; j <= n; j++) {
      if (a[j] == 0 && b[j] > 0) R += min(b[j], 1 + c[j]) - 1;
      else
        R += min(a[j] + c[j], b[j]);
    }
    for (int j = 1; j <= n; j++) {
      if (a[j] == 0 && b[j] > 0) R -= min(b[j], 1 + c[j]) - 1;
      else
        R -= min(a[j] + c[j], b[j]);
      if (R + a[j] == 0) printf("0 ");
      else
        printf("%lld ", R + a[j] + c[j]);
      if (a[j] == 0 && b[j] > 0) R += min(b[j], 1 + c[j]) - 1;
      else
        R += min(a[j] + c[j], b[j]);
    }
    cout << endl;
    long long C = 0, W = 0, E = 0;
    for (int j = 1; j <= n; j++) {
      if (a[j] == 0 && b[j] > 0) W += min(1 + c[j], b[j]) - 1, E += a[j] + c[j];
      else if (a[j] > 0)
        W += min(a[j] + c[j], b[j]), E += a[j] + c[j];
      else
        op[++k] = c[j], E += a[j];
    }
    sort(op + 1, op + k + 1);
    for (int x = 1; x <= min(k, W); x++) E += op[k - x + 1];
    cout << E << endl;
  }
  return 0;
}
