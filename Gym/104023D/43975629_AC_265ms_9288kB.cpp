#include <bits/stdc++.h>
#define rep(i, l, r) for (int i = (l), i##end = (r); i <= i##end; i++)
#define per(i, r, l) for (int i = (r), i##end = (l); i >= i##end; i--)
using namespace std;

const int N = 1e5 + 9;
const int mov[6][2] = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}, {1, -1}, {-1, -1}};
int T, n, tot, dp[1 << 19];
vector<int> a[5], id[5];
pair<int, int> pos[20];
vector<tuple<int, int, int, int>> cho;

inline void push(int i1, int j1, int i2, int j2, int i3, int j3) {
  cho.emplace_back(1 << id[i1][j1], 1 << id[i2][j2], 1 << id[i3][j3], a[i2][j2]);
  cho.emplace_back(1 << id[i3][j3], 1 << id[i2][j2], 1 << id[i1][j1], a[i2][j2]);
}

int main() {
#ifdef memset0
  freopen("D.in", "r", stdin);
#endif
  ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
  a[0].resize(3);
  a[1].resize(4);
  a[2].resize(5);
  a[3].resize(4);
  a[4].resize(3);
  for (int i = 0; i < 5; i++)
    for (int j = 0; j < a[i].size(); j++) {
      cin >> a[i][j];
      pos[tot] = make_pair(i, j);
      id[i].push_back(tot++);
      // fprintf(stderr, "(%d,%d) -> %d\n", i, j, id[i][j]);
    }
  // for (int i = 0; i < 5; i++)
  //   for (int j = 0; j < a[i].size(); j++) {
  //     for (int k = 0; k < 6; k++) {
  //       int ii = i + mov[k][0];
  //       int jj = j + mov[k][1];
  //       if (ii < 0 || jj < 0 || ii >= 5 || jj >= a[ii].size()) continue;
  //       int iii = ii + mov[k][0];
  //       int jjj = jj + mov[k][1];
  //       if (iii < 0 || jjj < 0 || iii >= 5 || jjj >= a[iii].size()) continue;
  //       fprintf(stderr, "(%d,%d) (%d,%d) (%d,%d)\n", i, j, ii, jj, iii, jjj);
  //       cho.emplace_back(1 << id[i][j], 1 << id[ii][jj], 1 << id[iii][jjj], a[ii][jj]);
  //     }
  //   }
  rep(x, 0, 4) rep(y, 0, (int)a[x].size() - 3) push(x, y, x, y + 1, x, y + 2);
  rep(y, 0, 2) push(0, y, 1, y, 2, y), push(2, y, 3, y, 4, y);
  rep(y, 0, 2) push(0, y, 1, 1 + y, 2, 2 + y), push(2, 2 + y, 3, 1 + y, 4, y);
  rep(y, 0, 2) push(1, y, 2, 1 + y, 3, 1 + y), push(1, 1 + y, 2, 1 + y, 3, y);
  cerr << "tot = " << tot << endl;
  vector<pair<int, int>> xs;
  for (int x = 0; x < (1 << 19); x++) {
    int cnt = 0;
    for (int i = 0; i < 19; i++)
      if ((x >> i) & 1) cnt++;
    xs.emplace_back(cnt, x);
  }
  sort(xs.begin(), xs.end());
  for (const auto &[_, x] : xs) {
    for (int i = 0; i < 19; i++)
      if ((x >> i) & 1) {
        dp[x] = max(dp[x], dp[x ^ (1 << i)]);
      }
    for (const auto &[a, b, c, w] : cho)
      if ((x & a) && (x & b) && !(x & c)) {
        // if (x == 1568 || x == 17408) {
        //   cerr << bitset<19>(x) << " " << bitset<19>(x ^ a ^ b ^ c) << " " << dp[x ^ a ^ b ^ c] << "+" << w << " : " << (x ^ a ^ b ^ c) << endl;
        // }
        dp[x] = max(dp[x], dp[x ^ a ^ b ^ c] + w);
      }
  }
  cin >> T;
  while (T--) {
    int x = 0;
    for (int i = 0; i < 5; i++) {
      string s;
      cin >> s;
      for (int j = 0; j < s.length(); j++) {
        if (s[j] == '#') {
          x |= 1 << id[i][j];
          // fprintf(stderr, "x (%d,%d) -> %d\n", i, j, id[i][j]);
        }
      }
    }
    // for (int i = 0; i < 19; i++) cerr << ((x >> i) & 1);
    // cerr << " => " << x << " => ";
    cout << dp[x] << endl;
  }
}

/*
000 0100 01000 0000 000 0100000000000000000 0+7 : 131072
000 0000 01100 0100 000 0000100010000000000 7+6 : 17408
000 0000 01100 0100 000 0000000100000100000 0+8 : 2080
000 0000 01100 0100 000 0000000010000000100 0+7 : 1028
000 0000 01100 0100 000 0000000000100100000 3+6 : 288
000 0000 01100 0100 000 0000000001000000010 0+7 : 514
000 0010 00110 0000 000 => 1568 => 13
000 0000 01100 0010 000 => 17152 => 13
111 1111 11111 1111 111 => 524287 => 100
*/