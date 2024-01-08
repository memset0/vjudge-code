// AC onsite
#include <bits/stdc++.h>
#define rep(i, a, b) for (int i = (a); i <= (b); i++)
#define per(i, a, b) for (int i = (a); i >= (b); i--)
#define op(x) ((x & 1) ? x + 1 : x - 1)
#define odd(x) (x & 1)
#define even(x) (!odd(x))
#define lc(x) (x << 1)
#define rc(x) (lc(x) | 1)
#define lowbit(x) (x & -x)
#define mp(x, y) make_pair(x, y)
typedef long long ll;
typedef unsigned long long ull;
typedef double db;
using namespace std;
const int MAXN = 5e5 + 10, base = 19260817;
int n, q;
string s;
ull h[MAXN], rh[MAXN], pw[MAXN];
ull H(int l, int r) { return h[r] - h[l - 1] * pw[r - l + 1]; }
ull rH(int l, int r) { return rh[l] - rh[r + 1] * pw[r - l + 1]; }
int f[MAXN]; // 以i为回文中心
int g[MAXN]; // 以mid(i,i+1)中间为回文中心
int ans, cnt;
#define mid ((l + r) >> 1)
struct Seg {
  int mn[MAXN << 2], mx[MAXN << 2]; // min i-f,max i+f
  void pu(int x) {
    mn[x] = min(mn[lc(x)], mn[rc(x)]);
    mx[x] = max(mx[lc(x)], mx[rc(x)]);
  }
  void build(int x, int l, int r, int *f) {
    if (l == r) {
      mn[x] = l - f[l], mx[x] = l + f[l];
      return;
    }
    build(lc(x), l, mid, f), build(rc(x), mid + 1, r, f);
    pu(x);
  }
  int q1(int x, int l, int r, int ql, int qr, int v) { // 最大的位置满足<=v
    if (ql > qr || ql > r || qr < l) return 0;
    if (mn[x] > v) return 0;
    if (l == r) return l;
    int val = q1(rc(x), mid + 1, r, ql, qr, v);
    if (val) return val;
    return q1(lc(x), l, mid, ql, qr, v);
  }
  int q2(int x, int l, int r, int ql, int qr, int v) { // 最小的位置满足>=v
    if (ql > qr || ql > r || qr < l) return n + 1;
    if (mx[x] < v) return n + 1;
    if (l == r) return l;
    int val = q2(lc(x), l, mid, ql, qr, v);
    if (val != n + 1) return val;
    return q2(rc(x), mid + 1, r, ql, qr, v);
  }
} sf, sg;
#undef mid
void pchk(int len, int num) {
  if (ans > len) {
    ans = len, cnt = num;
  } else if (ans == len) {
    cnt += num;
  }
}
void qry(int L, int R) {
  if (H(L, R) == rH(L, R)) {
    cout << "0 0\n";
    return;
  }
  int l = 1, r = R - L + 1, len = 0;
  ans = 1e9, cnt = 0;
  while (l <= r) {
    int mid = (l + r) >> 1;
    if (H(L, L + mid - 1) == rH(R - mid + 1, R)) len = mid, l = mid + 1;
    else
      r = mid - 1;
  }
  int lp = L + len, rp = R - len, rest = (R - L + 1) - 2 * len;
  assert(lp <= rp);
  int mid = (L + R + 1) / 2;
  // 左半边
  int fp = sf.q1(1, 1, n, lp, mid - 1, lp), gp = sg.q1(1, 1, n, lp, mid - 1, lp - 1);
  int j = max(fp, gp);
  if (j) {
    if (fp <= gp) pchk(rest - 2 * (j - lp + 1), lp - max(j - g[j] + 1, L) + 1);
    else
      pchk(rest - 2 * (j - lp) - 1, lp - max(j - f[j], L) + 1);
  }
  // 右半边
  fp = sf.q2(1, 1, n, mid, rp, rp), gp = sg.q2(1, 1, n, mid, rp, rp);
  j = min(fp, gp);
  if (j != n + 1) {
    if (fp <= gp) pchk(rest - 2 * (rp - j) - 1, min(j + f[j], R) - rp + 1);
    else
      pchk(rest - 2 * (rp - j), min(j + g[j], R) - rp + 1);
  }
  //
  assert(ans < 1e9 && cnt);
  cout << ans << " " << cnt << "\n";
}
int main() {
  cin.tie(0)->sync_with_stdio(0);
  cin >> n >> s >> q;
  s.insert(s.begin(), '\0');
  for (int i = 0; i < 10; i++) s.insert(s.end(), '\0');
  pw[0] = 1;
  rep(i, 1, n) h[i] = h[i - 1] * base + (s[i] - 'a' + 1), pw[i] = pw[i - 1] * base;
  per(i, n, 1) rh[i] = rh[i + 1] * base + (s[i] - 'a' + 1);
  rep(i, 1, n) {
    int L = 1, R = min(i - 1, n - i);
    while (L <= R) {
      int mid = (L + R) >> 1;
      if (H(i - mid, i - 1) == rH(i + 1, i + mid)) f[i] = mid, L = mid + 1;
      else
        R = mid - 1;
    }
    L = 1, R = min(i, n - i);
    while (L <= R) {
      int mid = (L + R) >> 1;
      if (H(i - mid + 1, i) == rH(i + 1, i + mid)) g[i] = mid, L = mid + 1;
      else
        R = mid - 1;
    }
  }
  sf.build(1, 1, n, f), sg.build(1, 1, n, g);
  //
  rep(i, 1, q) {
    int L, R;
    cin >> L >> R;
    qry(L, R);
  }
  return 0;
}