#include <bits/stdc++.h>
int a[100006];
int main() {
  int b, k;
  scanf("%d%d", &b, &k);
  for (int i = 1; i <= k; i++)
    scanf("%d", &a[i]);
  if (b & 1) {
    int r = 0;
    for (int i = k; i > 0; i--) {
      if (a[i] & 1) {
        r ^= 1;
      }
    }
    if (r)
      puts("odd");
    else
      puts("even");
  } else {
    if (a[k] & 1)
      puts("odd");
    else
      puts("even");
  }
}