#include <bits/stdc++.h>
const int mod = 998244353;
int n, ans;
int main() {
  scanf("%d", &n);
  static const int R[16] = {0,   4,  8,   -1, 16,  -10, 4,  -12,
                            -48, 26, -44, 15, -16, -4,  -4, -1};
  int A[16] = {0,    0,    0,     24,    4,      240,    204,     1316,
               2988, 6720, 26200, 50248, 174280, 436904, 1140888, 3436404};
  for (int i = 16; i <= n; ++i) {
    int x = 0;
    for (int j = 0; j < 16; ++j)
      x = (x + (long long)R[(i - j - 1) & 15] * A[j]) % mod;
    A[i & 15] = x;
  }
  printf("%d\n", (A[n & 15] + mod) % mod);
}