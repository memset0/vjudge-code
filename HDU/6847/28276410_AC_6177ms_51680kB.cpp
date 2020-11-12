#include <algorithm>
#include <cstdio>

int f[1000001][21], sum[1000001][21], T, t, a, c, m, nxt[1000001];
int getval(int x, int y) {
  int cnt = 0;
  for (int i = 20; ~i; --i)
    if (y >= (1 << i))
      cnt += sum[x][i], x = f[x][i], y -= 1 << i;
  return cnt;
}
long long gcd(long long a, long long b) { return (!b) ? a : gcd(b, a % b); }
int main() {
  scanf("%d", &T);
  for (int fd = 1; fd <= T; fd++) {
    scanf("%d%d%d%d", &t, &a, &c, &m);
    for (int i = 0; i < m; i++) {
      nxt[i] = (1ll * i * a + c) % m;
    }
    for (int i = 0; i < m; i++) {
      f[i][0] = nxt[nxt[i]];
      sum[i][0] = (i % 2 == 0);
    }
    for (int j = 1; j <= 20; j++)
      for (int i = 0; i < m; i++) {
        sum[i][j] = sum[i][j - 1] + sum[f[i][j - 1]][j - 1];
        f[i][j] = f[f[i][j - 1]][j - 1];
      }
    long long ans = 0;
    for (int i = 0; i < m; i++) {
      int tem = i;
      if (i % 2)
        tem = nxt[tem];
      ans +=
          getval(tem, ((std::min(i, (t << 1) - i) + 1) >> 1) +
                          (std::min(i, (t << 1) - i) % 2 == 0 && i % 2 == 0));
      //            printf("%d
      //            %d\n",i,getval(tem,((std::min(i,(t<<1)-i)+1)>>1)+(std::min(i,(t<<1)-i)%2==0&&i%2==0)));
    }
    ans = (1ll * ans * 2 - (t + 1));
    long long h = 1ll * (t + 1) * (t + 1), _gcd = gcd(ans, h);
    printf("%lld/%lld\n", ans / _gcd, h / _gcd);
  }
}