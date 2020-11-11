#include <bits/stdc++.h>
using namespace std;

const int a[26] = {1, 2, 3, 1, 2, 3, 1, 2, 3, 1, 2, 3, 1,
                   2, 3, 1, 2, 3, 4, 1, 2, 3, 1, 2, 3, 4};
int sum, n;
char c;
int main() {
  scanf("%d\n", &n);
  for (int i = 1; i <= n; i++) {
    sum = 0;
    while ((c = getchar()) != '\n') {
      sum += (c == ' ' ? 1 : a[c - 'a']);
    }
    printf("Case #%d: %d\n", i, sum);
  }
  return 0;
}