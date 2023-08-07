#include <bits/stdc++.h>
using namespace std;
map<string, int> id;
int p[4], score[5][4];
struct game {
  int x, y, a, b;
  int win, lose;
  bool ot;
} g[6];
inline int merge(int a, int b) {
  // cerr << "new " << b << endl;
  // if (b) exit(0);

  if (a == -1) return b;
  if (b == -1) return a;
  if (a == 2 && b == 2) return 2;
  if (a == 0 && b == 0) return 0;
  return 1;
}
int check() {
  for (int i = 0; i < 6; i++) {
    if (g[i].a > g[i].b) {
      g[i].win = g[i].x;
      g[i].lose = g[i].y;
    } else {
      g[i].win = g[i].y;
      g[i].lose = g[i].x;
    }
    // fprintf(stderr, "game[%d] win=%d lose=%d\n", i, g[i].win, g[i].lose);
  }
  memset(score, 0, sizeof(score));
  for (int i = 0; i < 4; i++) p[i] = i;
  for (int i = 0; i < 6; i++) {
    score[0][g[i].win] += 2;
    if (g[i].ot) score[0][g[i].lose] += 1;
    score[1][g[i].win]++;
    if (!g[i].ot) {
      score[2][g[i].win]++;
    }
    score[3][g[i].x] += g[i].a - g[i].b;
    score[3][g[i].y] += g[i].b - g[i].a;
    score[4][g[i].x] += g[i].a;
    score[4][g[i].y] += g[i].b;
  }
  int l = 0, r = 3;
  for (int k = 0; k < 5; k++) {
    sort(p + l, p + r + 1, [&](int a, int b) { return score[k][a] > score[k][b]; });
    // fprintf(stderr, "k=%d l=%d r=%d :: ", k, l, r);
    // for (int i = 0; i < 4; i++) cerr << p[i] << " \n"[i == 3];
    // for (int i = 0; i < 4; i++) cerr << score[k][i] << " \n"[i == 3];
    int ql = 1, qr = 1;
    while (ql > l && score[k][p[ql]] == score[k][p[ql - 1]]) --ql;
    while (qr < r && score[k][p[qr]] == score[k][p[qr + 1]]) ++qr;
    if (ql > 0 && p[0] == 0) return 2;
    if ((ql == qr || qr <= 1) && (p[0] == 0 || p[1] == 0)) return 2;
    if (qr - ql == 1) {
      for (int i = 0; i < 6; i++)
        if (g[i].win == p[qr] && g[i].lose == p[ql]) {
          swap(p[ql], p[qr]);
        }
      return p[0] == 0 || p[1] == 0 ? 2 : 0;
    }
    l = ql, r = qr;
  }
  for (int i = l; i <= r; i++)
    if (p[i] == 0) return 1;
  return 0;
}
int main() {
#ifdef memset0
  freopen("H4.in", "r", stdin);
#endif
  id["Russia"] = 0;
  id["Sweden"] = 1;
  id["Finland"] = 2;
  id["NA"] = 3;
  string x = "", y;
  for (int a, b, i = 1; i <= 5; i++) {
    if (!x.length()) {
      cin >> x;
    }
    cin >> y >> a >> b;
    g[i].x = id[x];
    g[i].y = id[y];
    cin >> x;
    if (x == "OT") {
      x = "";
      g[i].ot = true;
    }
    g[i].a = a;
    g[i].b = b;
  }
  if (!x.length()) {
    cin >> x;
  }
  cin >> y;
  g[0].x = id[x];
  g[0].y = id[y];
  // for (int i = 0; i < 6; i++) {
  //   cerr << i << " >> " << g[i].x << " " << g[i].y << " " << g[i].a << " " << g[i].b << " >> " << g[i].ot << endl;
  // }
  int ans = -1;
  for (int pa = 0; pa <= 100; pa++)
    for (int pb = 0; pb <= 100; pb++)
      if (pa != pb) {
        g[0].a = pa;
        g[0].b = pb;
        g[0].ot = false;
        ans = merge(ans, check());
        if (pa == pb + 1 || pa + 1 == pb) {
          g[0].ot = true;
          ans = merge(ans, check());
        }
      }
  assert(0 <= ans && ans <= 2);
  if (ans == 0) cout << "No chance" << endl;
  if (ans == 1) cout << "Believe in playoff!" << endl;
  if (ans == 2) cout << "Already in playoff!" << endl;
}