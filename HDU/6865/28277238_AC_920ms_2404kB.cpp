#include <cstdio>

int T, n, m, k, a[400001], b[200001], S[101], nxt[400001];
int Base[41];
void add(int x) {
  for (int i = 29; ~i; --i)
    if (x & (1 << i)) {
      if (!Base[i]) {
        Base[i] = x;
        return;
      } else
        x ^= Base[i];
    }
}
void solve() {
  for (int i = 29; ~i; --i)
    for (int j = 29; ~j; --j)
      if (i != j && Base[i] & (1 << j))
        Base[i] ^= Base[j];
}
int main() {
  scanf("%d", &T);
  for (int fd = 1; fd <= T; fd++) {
    scanf("%d%d%d", &n, &m, &k);
    for (int i = 1; i <= n; i++)
      scanf("%d", a + i);
    for (int i = 1; i <= m; i++)
      scanf("%d", b + i);
    for (int i = 0; i < 30; i++)
      Base[i] = 0;
    for (int i = 1; i <= k; i++)
      scanf("%d", S + i), add(S[i]);
    solve();
    for (int i = 1; i <= n; i++) {
      int tem = a[i];
      a[i] = 0;
      for (int j = 0; j < 30; j++)
        if (tem & (1 << j))
          a[i] ^= Base[j] ^ (1 << j);
    }
    for (int i = 1; i <= m; i++) {
      int tem = b[i];
      b[i] = 0;
      for (int j = 0; j < 30; j++)
        if (tem & (1 << j))
          b[i] ^= Base[j] ^ (1 << j);
    }
    //        for(int i=1;i<=n;i++)printf("%d ",a[i]);putchar('\n');
    //        for(int i=1;i<=m;i++)printf("%d ",b[i]);putchar('\n');
    a[n + 1] = b[m + 1] = -1;
    for (int i = 2, j = 0; i <= m; i++) {
      while (j && b[i] != b[j + 1])
        j = nxt[j];
      if (b[i] == b[j + 1])
        ++j;
      nxt[i] = j;
    }
    int ans = 0;
    for (int i = 1, mat = 0, Mul = 1; i <= n; i++) {
      while (mat && a[i] != b[mat + 1])
        mat = nxt[mat];
      if (a[i] == b[mat + 1])
        ++mat;
      //            printf("%d %d\n",i,mat);
      if (mat == m)
        (ans += Mul) %= 1000000007;
      if (i >= m)
        Mul = 1ll * Mul * 2 % 1000000007;
    }
    printf("%d\n", ans);
  }
}