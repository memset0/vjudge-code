#include <algorithm>
#include <cctype>
#include <cstdio>
#include <cstring>
using namespace std;
#define lson l, m, rt << 1
#define rson m + 1, r, rt << 1 | 1
const int maxn = 22222;
struct Seg {
  int l, r, h, s;
  Seg() {}
  Seg(int a, int b, int c, int d) : l(a), r(b), h(c), s(d) {}
  bool operator<(const Seg &cmp) const { return h < cmp.h; }
} ss[maxn];
bool lbd[maxn << 2], rbd[maxn << 2]; // 标记这个节点的左右两个端点是否被覆盖（0表示没有，1表示有）
int numseg[maxn << 2];               // 这个区间有多少条线段（这个区间被多少条线段覆盖）
int cnt[maxn << 2];                  // 表示这个区间被重复覆盖了几次
int len[maxn << 2];                  // 这个区间被覆盖的长度
void PushUP(int rt, int l, int r) {
  if (cnt[rt]) // 整个区间被覆盖
  {
    lbd[rt] = rbd[rt] = 1;
    len[rt] = r - l + 1;
    numseg[rt] = 2;  // 每条线段有两个端点
  } else if (l == r) // 这是一个点而不是一条线段
  {
    len[rt] = numseg[rt] = lbd[rt] = rbd[rt] = 0;
  } else // 是一条没有整个区间被覆盖的线段，合并左右子的信息
  {
    lbd[rt] = lbd[rt << 1];     // 和左儿子共左端点
    rbd[rt] = rbd[rt << 1 | 1]; // 和右儿子共右端点
    len[rt] = len[rt << 1] + len[rt << 1 | 1];
    numseg[rt] = numseg[rt << 1] + numseg[rt << 1 | 1];
    if (lbd[rt << 1 | 1] && rbd[rt << 1]) numseg[rt] -= 2; // 如果左子的右端点和右子的左端点都被覆盖了即两条线重合
  }
}
void update(int L, int R, int c, int l, int r, int rt) {
  if (L <= l && r <= R) {
    cnt[rt] += c;
    PushUP(rt, l, r);
    return;
  }
  int m = (l + r) >> 1;
  if (L <= m) update(L, R, c, lson);
  if (m < R) update(L, R, c, rson);
  PushUP(rt, l, r);
}
int main() {
  int n;
  while (~scanf("%d", &n)) {
    int m = 0;
    int lbd = 10000, rbd = -10000;
    for (int i = 0; i < n; i++) {
      int a, b, c, d;
      scanf("%d%d%d%d", &a, &b, &c, &d);
      lbd = min(lbd, a);
      rbd = max(rbd, c);
      ss[m++] = Seg(a, c, b, 1);
      ss[m++] = Seg(a, c, d, -1);
    }
    sort(ss, ss + m);
    // 数据小可以不离散化
    int ret = 0, last = 0;
    for (int i = 0; i < m; i++) {
      if (ss[i].l < ss[i].r) update(ss[i].l, ss[i].r - 1, ss[i].s, lbd, rbd - 1, 1);
      ret += numseg[1] * (ss[i + 1].h - ss[i].h); // 竖线的长度 = 【下一条即将被扫到的横线的高度 - 现在扫到的横线的高度】*num
      ret += abs(len[1] - last);                  // 横线的长度 = 【现在这次总区间被覆盖的程度和上一次总区间被覆盖的长度之差的绝对值】
      last = len[1];                              // 每次都要更新上一次总区间覆盖的长度
    }
    printf("%d\n", ret);
  }
  return 0;
}