#include <bits/stdc++.h>
using namespace std;
long long a[101010], cnt = 1, sum = 0;
char c[101010];
int main() {
  scanf("%lld", &a[cnt]);
  a[cnt] %= 10000;
  while (cin >> c[cnt]) {
    cin >> a[++cnt];
    a[cnt] %= 10000;
  }
  for (int i = cnt; i >= 1; i--) {
    if (c[i] == '*') {
      a[i] *= a[i + 1];
      a[i] %= 10000;
      a[i + 1] = 0;
    }
  }
  for (int i = 1; i <= cnt; i++) {
    sum += a[i];
    sum %= 10000;
  }
  printf("%lld\n", sum);
}