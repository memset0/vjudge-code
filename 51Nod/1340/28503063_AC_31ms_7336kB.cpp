#include <bits/stdc++.h>
using namespace std;

const int N = 55;

int T, n, m1, m2, tot, num, vv;
long long dis[N][N * 2], inf;

struct atom {
  long long x, v;
} lis[N * N * N * 2];
inline bool cmp(const atom &x, const atom &y) { return x.x < y.x; }

struct line {
  long long l, r, k, b;
  long long f(long long x) { return k * x + b; }
} s1[N * N * N * 2], t1[N * N * N * 2];

inline long long min(long long x, long long y) { return x < y ? x : y; }
inline long long max(long long x, long long y) { return x > y ? x : y; }

long long up(long long tb, long long tk) {
  if (tk < 0)
    tk = -tk, tb = -tb;
  long long tt = tb / tk;
  return tt + (tt * tk < tb);
}

long long down(long long tb, long long tk) {
  if (tk < 0)
    tk = -tk, tb = -tb;
  long long tt = tb / tk;
  return tt - (tt * tk > tb);
}

void push(line *a, int &num, line t) {
  while (num && t.f(a[num].l) <= a[num].f(a[num].l))
    num--;
  if (num)
    t.l = down(-(a[num].b - t.b), a[num].k - t.k) + 1, a[num].r = t.l - 1;
  a[++num] = t;
}

void put(long long l, long long r) {
  lis[++num] = (atom){l, 1};
  lis[++num] = (atom){r + 1, -1};
}

void check(line s1, line t1) {
  long long l = max(s1.l, t1.l), r = min(s1.r, t1.r);
  if (l > r)
    return;
  line t = {0, 0, s1.k - t1.k, s1.b - t1.b};
  if (t.f(l) < 0 && t.f(r) < 0)
    return;
  put(t.f(l) >= 0 ? l : up(-t.b, t.k), t.f(r) >= 0 ? r : down(-t.b, t.k));
}

struct edge {
  long long x, y, v, k;
  void BF() {
    for (int i = 0; i <= 2 * n; i++)
      if (i + k >= 0 && i + k <= 2 * n)
        dis[y][i + k] = min(dis[y][i + k], dis[x][i] + v);
  }
  void calc() {
    int n1 = 0, n2 = 0;
    for (int i = 2 * n; i >= 0; i--) {
      if (dis[x][i] < inf / 2)
        push(s1, n1, (line){n, inf, i + k - n, dis[x][i] + v});
      if (dis[y][i] < inf / 2)
        push(t1, n2, (line){n, inf, i - n, dis[y][i]});
    }
    for (int k1 = 1, k2 = 1; k1 <= n1 && k2 <= n2;
         s1[k1].r <= t1[k2].r ? k1++ : k2++)
      check(s1[k1], t1[k2]);
  }
} E[N << 2];

int main() {
  for (scanf("%d", &T); T--;) {
    scanf("%d%d%d", &n, &m1, &m2);
    memset(dis, 1, sizeof(dis));
    memset(lis, 0, sizeof(lis));
    inf = dis[0][0], dis[0][n] = 0;
    tot = 0;
    for (int i = 0; i < n; i++)
      E[++tot] = (edge){(i + 1) % n, i, -1, i == n - 1};
    long long x, y, v;
    for (int i = 1; i <= m1; i++) {
      scanf("%lld%lld%lld", &x, &y, &v);
      E[++tot] = (edge){y, x, -v, (x > y)};
    }
    for (int i = 1; i <= m2; i++) {
      scanf("%lld%lld%lld", &x, &y, &v);
      E[++tot] = (edge){x, y, v, -(x > y)};
    }
    for (int i = 1; i < n; i++)
      for (int j = 1; j <= tot; j++)
        E[j].BF();
    for (int i = 1; i <= tot; i++)
      E[i].calc();
    sort(lis + 1, lis + 1 + num, cmp);
    lis[num + 1] = (atom){inf + 1, 0};
    long long sum = 0, ans = 0;
    for (int i = 1; i <= num; i++)
      ans += ((sum += lis[i].v) == tot) * (lis[i + 1].x - lis[i].x);
    printf("%lld\n", ans >= inf / 4 ? -1 : ans);
  }
}