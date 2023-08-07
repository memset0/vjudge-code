#include <cctype>
#include <cstdio>
#include <cstring>
#include <iostream>

using namespace std;

int T, n;
char s[101], t[101];
int v[11];

int main() {
  scanf("%d", &T);
  for (int o = 1; o <= T; ++o) {
    scanf("%s", s + 1);
    n = strlen(s + 1);
    s[n + 1] = '@';
    for (int i = 0; i <= 9; ++i) {
      v[i] = 0;
    }
    for (int i = 1; i <= n; ++i) {
      t[i] = s[i];
      if (isdigit(s[i])) v[s[i] ^ 48] = 1;
    }
    int ans = -1;
    for (int d = 0; d <= 9; ++d) {
      if (v[d]) continue;
      for (int i = 1; i <= n; ++i) {
        if (t[i] == '?') s[i] = '0' + d;
        else
          s[i] = t[i];
      }
      int g;
      for (g = 1; g <= n; ++g) {
        if (s[g] == '=') {
          break;
        }
      }
      int i = 1, f = 0, x = 0;
      if (s[i] == '-') f = 1, ++i;
      if (s[i] == '0' && isdigit(s[i + 1])) continue;
      if (f && s[i] == '0' && !isdigit(s[i + 1])) continue;
      while (isdigit(s[i])) {
        x = x * 10 + (s[i] ^ 48);
        ++i;
      }
      if (f) x = -x;
      char op = s[i];
      ++i;
      f = 0;
      int y = 0;
      if (s[i] == '-') f = 1, ++i;
      if (s[i] == '0' && isdigit(s[i + 1])) continue;
      if (f && s[i] == '0' && !isdigit(s[i + 1])) continue;
      while (isdigit(s[i])) {
        y = y * 10 + (s[i] ^ 48);
        ++i;
      }
      if (f) y = -y;
      int z = 0;
      f = 0, i = g + 1;
      if (s[i] == '-') f = 1, ++i;
      if (s[i] == '0' && (isdigit(s[i + 1]))) continue;
      if (f && s[i] == '0' && !isdigit(s[i + 1])) continue;
      while (i <= n) {
        z = z * 10 + (s[i] ^ 48);
        ++i;
      }
      if (f) z = -z;
      if (op == '+') {
        if (x + y == z) {
          ans = d;
          break;
        }
      } else if (op == '-') {
        if (x - y == z) {
          ans = d;
          break;
        }
      } else if (1ll * x * y == z) {
        ans = d;
        break;
      }
    }
    if (o != T) printf("%d\n", ans);
    else
      printf("%d", ans);
  }
  return 0;
}