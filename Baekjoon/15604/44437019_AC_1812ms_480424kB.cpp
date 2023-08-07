#include <bits/stdc++.h>
typedef std::string str;
typedef long long ll;
typedef unsigned un;
typedef std::pair<int, int> pii;
using std::max;
using std::min;
bool umax(int &a, int t) {
  if (t > a) return a = t, 1;
  return 0;
}
bool umin(int &a, int t) {
  if (t < a) return a = t, 1;
  return 0;
}

const int MAXN = 1000011, MAXV = 1e7 + 11, INF = 1e9 + 233;
int lst[MAXV];
int n;
int a[MAXN], fa[MAXN], lb[MAXN], rb[MAXN];

int cc = 0;
struct Segment_Tree {
  struct one {
    int mina, sec, tag;
    pii b;
    void pushtag(int k) { mina = max(mina, k), tag = max(tag, k); }
  } t[MAXN << 2 | 1];
#define rt t[num]
#define tl t[num << 1]
#define tr t[num << 1 | 1]
  void pushdown(un num) { tl.pushtag(rt.tag), tr.pushtag(rt.tag); }
  void pushup(un num) {
    if (tl.mina < tr.mina) {
      rt.mina = tl.mina, rt.b = tl.b;
      rt.sec = min(tl.sec, tr.mina);
    } else if (tl.mina > tr.mina) {
      rt.mina = tr.mina, rt.b = tr.b;
      rt.sec = min(tr.sec, tl.mina);
    } else
      rt.mina = tl.mina, rt.sec = min(tl.sec, tr.sec), rt.b = max(tl.b, tr.b);
  }
  void init(un l = 1, un r = n, un num = 1) {
    if (l == r) {
      rt.mina = lb[l], rt.sec = INF, rt.b = pii(rb[l], l);
      return;
    }
    un mid = (l + r) >> 1;
    init(l, mid, num << 1), init(mid + 1, r, num << 1 | 1);
    pushup(num);
  }
  void chkmax(un ql, un qr, int a, un l = 1, un r = n, un num = 1) {
    ++cc;
    if (a < rt.mina) return;
    if (ql <= l && r <= qr && a < rt.sec) {
      rt.pushtag(a);
      return;
    }
    pushdown(num);
    un mid = (l + r) >> 1;
    if (ql <= mid) chkmax(ql, qr, a, l, mid, num << 1);
    if (qr > mid) chkmax(ql, qr, a, mid + 1, r, num << 1 | 1);
    pushup(num);
  }
  pii query(un ql, un qr, int k, un l = 1, un r = n, un num = 1) {
    // printf("[%u,%u] (%d,%d,%d)\n",l,r,rt.mina,rt.b.first,rt.b.second);
    if (ql <= l && r <= qr) return rt.mina == k ? rt.b : pii(0, 0);
    pushdown(num);
    un mid = (l + r) >> 1;
    // printf("mid=%d\n",mid);
    // getchar();
    pii res(0, 0);
    if (ql <= mid) res = max(res, query(ql, qr, k, l, mid, num << 1));
    if (qr > mid) res = max(res, query(ql, qr, k, mid + 1, r, num << 1 | 1));
    return res;
  }
} sgt;
std::vector<int> fac[MAXV];
bool vis[MAXV];
int pos[MAXV];
void sieve(int m) {
  std::vector<int> pri;
  for (int i = 2; i <= m; i++) {
    if (!vis[i]) {
      pri.push_back(i);
    }
    for (int j = 0; j < pri.size() && (long long)i * pri[j] <= m; j++) {
      vis[i * pri[j]] = true;
      if (i % pri[j] == 0) break;
    }
  }
  for (int i = 1; i <= n; i++)
    if (fac[a[i]].empty()) {
      int x = a[i];
      for (int j = 0; (long long)pri[j] * pri[j] <= x; j++)
        if (x % pri[j] == 0) {
          while (x % pri[j] == 0) {
            x /= pri[j];
          }
          fac[a[i]].push_back(pri[j]);
        }
      if (x > 1) {
        fac[a[i]].push_back(x);
      }
      std::sort(fac[a[i]].begin(), fac[a[i]].end());
      // for (int x : fac[a[i]]) std::cerr << x << " ";
      // std::cerr << std::endl;
    }
}
void solve(int l, int r, int pre) {
  if (l > r) return;
  // printf("[%d,%d]\n",l,r);
  sgt.chkmax(l, r, l);
  pii v = sgt.query(l, r, l);
  // printf("v=(%d,%d)\n",v.first,v.second);
  if (v.first >= r) {
    int p = v.second;
    fa[p] = pre;
    // printf("p=%d\n",p);
    // getchar();
    solve(l, p - 1, p), solve(p + 1, r, p);
    return;
  }
  puts("impossible");
  // fprintf(stderr,"cc=%d\n",cc);
  // std::cerr << "clock: " << clock() / (double)CLOCKS_PER_SEC << std::endl;
  exit(0);
}
int main() {
  scanf("%d", &n);
  int root = 0;
  for (int i = 1; i <= n; ++i) scanf("%d", &a[i]);

  sieve(10000000);
  for (int i = 1; i <= n; ++i) {
    lb[i] = 1;
    int x = a[i];
    for (auto y : fac[x]) umax(lb[i], lst[y] + 1), lst[y] = i;
    // printf("%d ",lb[i]);
  }
  // puts("");
  memset(lst, 0x3f, sizeof lst);
  for (int i = n; i; --i) {
    rb[i] = n;
    int x = a[i];
    for (auto y : fac[x]) umin(rb[i], lst[y] - 1), lst[y] = i;
  }
  sgt.init();
  solve(1, n, 0);
  for (int i = 1; i <= n; ++i) printf("%d ", fa[i]);
  puts("");
  // fprintf(stderr,"cc=%d\n",cc);
  // std::cerr << "clock: " << clock() / (double)CLOCKS_PER_SEC << std::endl;

  return 0;
}