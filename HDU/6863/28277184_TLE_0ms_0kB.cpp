#include <algorithm>
#include <cstdio>

int T, n;
char s[10000010], tem[10000010];
int e[10000010], f[10000010];
int main() {
  //    freopen("in.txt","r",stdin);
  scanf("%d", &T);
  for (int fd = 1; fd <= T; fd++) {
    scanf("%d", &n);
    scanf("%s", s + 1);
    for (int i = 2, mx = 0, p = 0; i <= n; i++) {
      if (mx >= i)
        e[i] = std::min(mx - i + 1, e[i - p + 1]);
      else
        e[i] = 0;
      while (s[e[i] + 1] == s[e[i] + i] && i + e[i] <= n)
        ++e[i];
      if (e[i] + i - 1 >= mx)
        mx = e[i] + i - 1, p = i;
    }
    for (int i = 1; i <= n; i++)
      s[n + i] = s[i];
    //        for(int i=1;i<=n<<1;i++)printf("%c",s[i]);putchar('\n');
    bool did = 0;
    for (int i = 2; i <= n; i++)
      if (n % i == 0) {
        int u = n / i;
        int end = n + u, start = end - n + 1;
        char *x, *y;
        for (register int j = end - 1, mn = 0x7f7f7f, p = 0; j >= start; --j) {
          int &z = f[j];
          if (mn <= j)
            z = std::min(j - mn + 1, f[end - p + j]);
          else
            z = 0;
          if (z == j - mn + 1 || !z) {
            x = s + end - z, y = s + j - z;
            while (j - z >= start && *x == *y)
              ++z, --x, --y;
            if (j - z + 1 <= mn)
              mn = j - z + 1, p = j;
          }
        }
        bool bad = 1;
        for (int j = u + 1; j <= n; j += u) {
          bool cando = 0;
          for (int k = j + 1; k < j + u; ++k) {
            if (e[k] >= (j + u - k) && f[k - 1] >= (k - j)) {
              cando = 1;
              break;
            }
          }
          if (e[j] >= u)
            cando = 1;
          if (f[j + u - 1] >= u)
            cando = 1;
          if (!cando) {
            bad = 0;
            break;
          }
        }
        if (bad) {
          puts("Yes");
          did = 1;
          break;
        }
      }
    if (!did)
      puts("No");
  }
}