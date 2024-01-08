#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
typedef long double LD;
typedef pair<int, int> pii;

#pragma GCC optimize("Ofast")

const int N = 5e5 + 5;

#define int long long

struct node {
  int l, r;
  int v[2], tag;
} t[N * 2];

int tcnt = 0;

int build(int l, int r) {
  int x = ++tcnt;
  if (l < r) {
    int mid = (l + r) / 2;
    t[x].l = build(l, mid);
    t[x].r = build(mid + 1, r);
  }
  return x;
}

int n, m;
LL K;
vector<LL> a;
vector<int> ls;

void t0(int x) {
  t[x].v[0] += t[x].v[1];
  t[x].v[1] = 0;
  t[x].tag = -1;
}

void t1(int x) {
  t[x].v[1] += t[x].v[0];
  t[x].v[0] = 0;
  t[x].tag = 1;
}

void pushdown(int x) {
  if (t[x].tag == 1) {
    t1(t[x].l);
    t1(t[x].r);
  } else if (t[x].tag == -1) {
    t0(t[x].l);
    t0(t[x].r);
  }
  t[x].tag = 0;
}
void pushup(int x) {
  t[x].v[0] = t[t[x].l].v[0] + t[t[x].r].v[0];
  t[x].v[1] = t[t[x].l].v[1] + t[t[x].r].v[1];
}

void upd(int x, int l, int r, int p, int v) {
  if (l == r) {
    t[x].v[v]++;
    return;
  }
  if (t[x].tag) pushdown(x);
  int mid = (l + r) / 2;
  if (p <= mid) upd(t[x].l, l, mid, p, v);
  else
    upd(t[x].r, mid + 1, r, p, v);
  pushup(x);
}

void suf(int x, int l, int r, int k) {
  assert(x);
  if (t[x].v[1] == k) {
    t0(x);
    return;
  }
  if (l == r) {
    t[x].v[0] += k;
    t[x].v[1] -= k;
    return;
  }
  pushdown(x);
  int mid = (l + r) / 2;
  int rk = min(t[t[x].r].v[1], k);
  suf(t[x].r, mid + 1, r, rk);
  if (rk < k) suf(t[x].l, l, mid, k - rk);
  pushup(x);
}
int qry(int x, int l, int r, int k, int ty) {
  if (l == r) return l;
  pushdown(x);
  int mid = (l + r) / 2;
  if (t[t[x].r].v[ty] >= k) return qry(t[x].r, mid + 1, r, k, ty);
  else
    return qry(t[x].l, l, mid, k - t[t[x].r].v[ty], ty);
}

int id(int x) { return (int)(lower_bound(ls.begin(), ls.end(), x) - ls.begin()); }
int L;
void make(LL cur) {
  while (a.size() && a.back() / K >= cur - 1) {
    int v = (int)(a.back() / K - (cur - 1));
    assert(0 <= v && v <= 1);
    upd(1, 0, L, id((int)(a.back() % K)), v);
    a.pop_back();
  }
}
void work() {
  cin >> n >> m >> K;
  a.resize(n);
  for (int i = 0; i < n; i++) cin >> a[i], ls.push_back((int)(a[i] % K));
  sort(a.begin(), a.end());
  sort(ls.begin(), ls.end());
  ls.resize(unique(ls.begin(), ls.end()) - ls.begin());
  L = (int)ls.size() - 1;
  build(0, L);

  LL cur = a.back() / K;
  make(cur);
  for (int i = 0; i < m; i++) {
    char op[2];
    cin >> op;
    if (op[0] == 'A') {
      int k;
      LL ans;
      cin >> k;
      if (k <= t[1].v[1]) ans = cur * K + ls[qry(1, 0, L, k, 1)];
      else {
        k -= t[1].v[1];
        if (k <= t[1].v[0]) {
          ans = (cur - 1) * K + ls[qry(1, 0, L, k, 0)];
        } else {
          k -= t[1].v[0];
          ans = a[a.size() - k];
        }
      }
      cout << ans << '\n';
    } else {
      LL w;
      cin >> w;
      while (w) {
        if (w <= t[1].v[1]) {
          suf(1, 0, L, (int)(w));
          w = 0;
        } else if (t[1].v[1]) {
          w -= t[1].v[1];
          suf(1, 0, L, t[1].v[1]);
        } else {
          LL round = min(a.size() ? cur - 1 - a.back() / K : LLONG_MAX, w / t[1].v[0] + 1);
          w -= (round - 1) * t[1].v[0];
          cur -= round;
          t1(1);
          make(cur);
        }
      }
    }
  }
}

#undef int

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  int T = 1;
  //	cin >> T;
  for (int ca = 1; ca <= T; ca++) { work(); }
}