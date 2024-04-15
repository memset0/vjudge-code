// 不知道为什么 MLE，拉一个算了

#include <ctype.h>
#include <stdio.h>
#define sz 100001
struct site {
  int ed, next;
};
struct site dld[sz];
struct node {
  char yf, lz;
  int sum;
};
struct node tree[sz << 2];
int n, now, m;
int fa[sz], fsl[sz], col[sz], big[sz], bg[sz], dfn[sz];
int read();
int dfs(int);
void redfs(int, int);
void fix(int, int, int, int, int, char);
int main() {
  char in = 0;
  int x = 0, y = 0, tmp = 0;
  n = read();
  for (int i = 2; i <= n; ++i) {
    fa[i] = read() + 1;
    ++now;
    dld[now].ed = i;
    dld[now].next = fsl[fa[i]];
    fsl[fa[i]] = now;
  }
  now = 0;
  dfs(1);
  redfs(1, 1);
  for (int i = 1; i <= n; ++i) big[dfn[i]] = dfn[fa[i]];
  m = read();
  while (m) {
    --m;
    in = getchar();
    while (in < 'a') in = getchar();
    x = dfn[read() + 1];
    y = 0;
    if (in == 'i')
      while (x) {
        tmp = tree[1].sum;
        fix(1, n, col[x], x, 1, 1);
        y += tree[1].sum - tmp;
        x = big[col[x]];
      }
    else {
      tmp = tree[1].sum;
      fix(1, n, x, bg[x], 1, 0);
      y = tmp - tree[1].sum;
    }
    printf("%d\n", y);
  }
  return 0;
}

int read() {
  int x = 0;
  char c = 0;
  while (!isdigit(c = getchar()))
    ;
  do {
    x = (x << 3) + (x << 1) + (c & 15);
  } while (isdigit(c = getchar()));
  return x;
}

int dfs(int a) {
  int tmp = fsl[a], to = 1, mx = 0, tp = 0;
  while (tmp) {
    tp = dfs(dld[tmp].ed);
    if (mx < tp) {
      mx = tp;
      big[a] = dld[tmp].ed;
    }
    to += tp;
    tmp = dld[tmp].next;
  }
  return to;
}

void redfs(int a, int b) {
  ++now;
  dfn[a] = now;
  col[now] = dfn[b];
  if (big[a]) {
    redfs(big[a], b);
    int tmp = fsl[a];
    while (tmp) {
      if (dld[tmp].ed != big[a]) redfs(dld[tmp].ed, dld[tmp].ed);
      tmp = dld[tmp].next;
    }
  }
  bg[dfn[a]] = now;
}

void fix(int lf, int rt, int a, int b, int c, char d) {
  int mid = (lf + rt) >> 1;
  if (lf == a && rt == b) {
    tree[c].yf = 1;
    tree[c].lz = d;
    if (d) tree[c].sum = b - a + 1;
    else
      tree[c].sum = 0;
    return;
  }
  if (tree[c].yf) {
    if (tree[c].lz == d) return;
    tree[c << 1].yf = tree[(c << 1) | 1].yf = 1;
    tree[c << 1].lz = tree[(c << 1) | 1].lz = tree[c].lz;
    if (tree[c].lz) {
      tree[c << 1].sum = mid - lf + 1;
      tree[(c << 1) | 1].sum = rt - mid;
    } else
      tree[c << 1].sum = tree[(c << 1) | 1].sum = 0;
    tree[c].yf = 0;
  }
  c <<= 1;
  if (b <= mid) fix(lf, mid, a, b, c, d);
  else if (a > mid)
    fix(mid + 1, rt, a, b, c | 1, d);
  else {
    fix(lf, mid, a, mid, c, d);
    fix(mid + 1, rt, mid + 1, b, c | 1, d);
  }
  tree[c >> 1].sum = tree[c].sum + tree[c | 1].sum;
}