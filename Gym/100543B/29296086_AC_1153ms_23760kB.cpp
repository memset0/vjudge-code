#include <bits/stdc++.h>
using namespace std;

const int N = 1e5 + 9;
int T, n;

struct Node {
  int x, y;
  Node() {}
  Node(int xx, int yy) { x = xx, y = yy; }
} p[N];

struct Vector {
  int x, y;
  Vector() {}
  Vector(Node xx, Node yy) {
    x = xx.x - yy.x;
    y = xx.y - yy.y;
  }
};

long long cal(Vector x, Vector y) {
  return (long long)x.x * y.y - (long long)x.y * y.x;
}

struct ConvexHull {
  vector<Node> s;
} ch[N * 4];

void CH_clear(ConvexHull &x) {
  x.s.clear();
  return;
}

void CH_insert(ConvexHull &x, Node p) {
  int cnt = x.s.size();
  while (cnt > 1 && cal(Vector(x.s[cnt - 1], x.s[cnt - 2]),
                        Vector(p, x.s[cnt - 2])) >= 0) {
    x.s.pop_back();
    cnt--;
  }
  x.s.push_back(p);
  return;
}

void CH_merge(ConvexHull &x, ConvexHull y) {
  for (int i = 0; i < y.s.size(); i++) {
    CH_insert(x, y.s[i]);
  }
  return;
}

bool CH_find(ConvexHull x, Node p1, Node p2) {
  Vector vec = Vector(p2, p1);
  int l = 0, r = x.s.size() - 1;
  if (l > r) {
    return 0;
  }
  while (l < r) {
    int mid = (l + r) >> 1;
    if (cal(Vector(x.s[mid], p1), vec) < cal(Vector(x.s[mid + 1], p1), vec)) {
      r = mid;
    } else {
      l = mid + 1;
    }
  }
  if (cal(Vector(x.s[l], p1), vec) < 0) {
    return 1;
  } else if (l < x.s.size() - 1 && cal(Vector(x.s[l], p1), vec) < 0) {
    return 1;
  }
  return 0;
}

void ST_build(int u, int l, int r) {
  if (l == r) {
    CH_clear(ch[u]);
    CH_insert(ch[u], p[l]);
    CH_insert(ch[u], p[l + 1]);
    return;
  }
  int mid = (l + r) >> 1;
  ST_build(u * 2, l, mid);
  ST_build(u * 2 + 1, mid + 1, r);
  ch[u] = ch[u * 2];
  CH_merge(ch[u], ch[u * 2 + 1]);
  return;
}

int ST_query(int u, int l, int r, int L, int R, Node p1, Node p2) {
  if (L <= l && r <= R) {
    if (!CH_find(ch[u], p1, p2)) {
      return 0;
    } else if (l == r) {
      return l;
    }
  }
  int mid = (l + r) >> 1, ans = 0;
  if (L <= mid) {
    ans = ST_query(u * 2, l, mid, L, R, p1, p2);
  }
  if (ans) {
    return ans;
  }
  if (R > mid) {
    return ST_query(u * 2 + 1, mid + 1, r, L, R, p1, p2);
  }
  return 0;
}

int main() {
  ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
  for (cin >> T; T; --T) {
    cin >> n;
    for (int i = 1; i <= n; i++) {
      cin >> p[i].x >> p[i].y;
    }
    ST_build(1, 1, n - 1);
    for (int i = 1; i < n; i++) {
      cout << ST_query(1, 1, n - 1, i + 1, n - 1, p[i], p[i + 1]) << ' ';
    }
    cout << '\n';
  }
}
