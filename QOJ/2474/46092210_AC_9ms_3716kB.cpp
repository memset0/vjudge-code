#include <bits/stdc++.h>
using namespace std;
namespace mem {
enum OPER {
  SUNS,
  BIGGEST_BIRD,
  FLOCK_PERIMETER,
  HOUSE_VIEW_UP,
  BLOCKS_3X3,
  ANIMALS1,
  FREEDOM,
  CHUPACABRA,
  PEAKS,
  DRAKE_GRILL,
  MINIMUM_FREQUENCY,
  EMPTY_FIELDS,
  ANIMALS2,
  HOUSE_VIEW_DOWN,
  GIRLL_DRAKE,
  HOUSE_AND_GRILLS,
};
vector<OPER> opers = {
    SUNS,              //
    BIGGEST_BIRD,      //
    FLOCK_PERIMETER,   //
    HOUSE_VIEW_UP,     //
    BLOCKS_3X3,        //
    ANIMALS1,          //
    FREEDOM,           //
    CHUPACABRA,        //
    PEAKS,             //
    DRAKE_GRILL,       //
    MINIMUM_FREQUENCY, //
    EMPTY_FIELDS,      //
    ANIMALS2,          //
    HOUSE_VIEW_DOWN,   //
    GIRLL_DRAKE,       //
    HOUSE_AND_GRILLS,  //
};
map<OPER, string> names = {
    {SUNS, "SUNS"},                           //
    {BIGGEST_BIRD, "BIGGEST_BIRD"},           //
    {FLOCK_PERIMETER, "FLOCK_PERIMETER"},     //
    {HOUSE_VIEW_UP, "HOUSE_VIEW_UP"},         //
    {BLOCKS_3X3, "BLOCKS_3X3"},               //
    {ANIMALS1, "ANIMALS1"},                   //
    {FREEDOM, "FREEDOM"},                     //
    {CHUPACABRA, "CHUPACABRA"},               //
    {PEAKS, "PEAKS"},                         //
    {DRAKE_GRILL, "DRAKE_GRILL"},             //
    {MINIMUM_FREQUENCY, "MINIMUM_FREQUENCY"}, //
    {EMPTY_FIELDS, "EMPTY_FIELDS"},           //
    {ANIMALS2, "ANIMALS2"},                   //
    {HOUSE_VIEW_DOWN, "HOUSE_VIEW_DOWN"},     //
    {GIRLL_DRAKE, "GIRLL_DRAKE"},             //
    {HOUSE_AND_GRILLS, "HOUSE_AND_GRILLS"},   //
};
map<OPER, int> values = {
    {SUNS, 100},             //
    {BIGGEST_BIRD, 500},     //
    {FLOCK_PERIMETER, 60},   //
    {HOUSE_VIEW_UP, 10},     //
    {BLOCKS_3X3, 1},         //
    {ANIMALS1, 15},          //
    {FREEDOM, 7},            //
    {CHUPACABRA, 200},       //
    {PEAKS, 50},             //
    {DRAKE_GRILL, 500},      //
    {MINIMUM_FREQUENCY, 10}, //
    {EMPTY_FIELDS, 1},       //
    {ANIMALS2, 1},           //
    {HOUSE_VIEW_DOWN, 5},    //
    {GIRLL_DRAKE, 50},       //
    {HOUSE_AND_GRILLS, 3},   //
};
const int N = 55;
const int nxt[8][2] = {{1, 0}, {-1, 0}, {0, -1}, {0, 1}, {1, 1}, {-1, -1}, {1, -1}, {-1, 1}};
int n;
char a[N][N];
bool vis[N][N], checked[N][N], current[N][N], illuminated[N][N];
vector<pair<int, int>> indexs;
constexpr int absi(int x) { return x < 0 ? -x : x; }
bool is_border(int x, int y) { return x < 1 || y < 1 || x > n || y > n; }
bool is_empty(int x, int y) { return !is_border(x, y) && a[x][y] == ' '; }
bool is_chupacabra(int x, int y) { return !is_border(x, y) && a[x][y] == '!'; }
bool is_bird(int x, int y) { return !is_border(x, y) && (a[x][y] == 'v' || a[x][y] == 'D'); }
bool is_animal(int x, int y) { return !is_border(x, y) && (a[x][y] == '!' || a[x][y] == 'v' || a[x][y] == 'D'); }
int get(OPER op) {
  int res = 0;
  if (op == SUNS) {
    for (const auto &[i, j] : indexs)
      if (a[i][j] == '*') {
        for (int t = 0; t < 8; t++) {
          for (int x = i + nxt[t][0], y = j + nxt[t][1]; !is_border(x, y); x += nxt[t][0], y += nxt[t][1]) {
            if (!is_empty(x, y)) {
              illuminated[x][y] = true;
              break;
            }
          }
        }
      }
    for (const auto &[i, j] : indexs)
      if (illuminated[i][j] && a[i][j] != '*') {
        res++;
        // cerr << "illuminated " << i << " " << j << endl;
      }
  } else if (op == BIGGEST_BIRD) {
    for (const auto &[i, j] : indexs)
      if (is_bird(i, j) && !checked[i][j]) {
        queue<pair<int, int>> q;
        q.push({i, j});
        memset(current, 0, sizeof(current));
        checked[i][j] = current[i][j] = true;
        while (q.size()) {
          auto [ux, uy] = q.front();
          q.pop();
          for (int i = 0; i < 4; i++) {
            int vx = ux + nxt[i][0];
            int vy = uy + nxt[i][1];
            if (is_bird(vx, vy) && !checked[vx][vy]) {
              checked[vx][vy] = current[vx][vy] = true;
              q.push({vx, vy});
            }
          }
        }
        int mx = 0;
        for (int i = 1; i <= n; i++)
          for (int l = 1, r = 1; l <= n; l = r + 1, r = l) {
            if (!current[i][l]) continue;
            while (r + 1 <= n && current[i][r + 1]) ++r;
            mx = max(mx, r - l + 1);
          }
        // for (int j = 1; j <= n; j++)
        //   for (int l = 1, r = 1; l <= n; l = r + 1, r = l) {
        //     if (!current[l][j]) continue;
        //     while (r + 1 <= n && current[r + 1][j]) ++r;
        //     mx = max(mx, r - l + 1);
        //   }
        res += mx;
      }
  } else if (op == FLOCK_PERIMETER) {
    for (const auto &[i, j] : indexs)
      if (is_bird(i, j)) {
        int cur = 0;
        cur += !is_bird(i - 1, j);
        cur += !is_bird(i + 1, j);
        cur += !is_bird(i, j - 1);
        cur += !is_bird(i, j + 1);
        res += cur;
      }
  } else if (op == HOUSE_VIEW_UP) {
    for (const auto &[i, j] : indexs)
      if (a[i][j] == '^') {
        for (int k = i - 1; k >= 1; k--)
          if (a[k][j] == ' ') {
            ++res;
          } else {
            break;
          }
      }
  } else if (op == BLOCKS_3X3) {
    set<tuple<char, char, char, char, char, char, char, char, char>> st;
    for (int i = 1; i + 2 <= n; i++)
      for (int j = 1; j + 2 <= n; j++) {
        st.insert(make_tuple(a[i + 0][j + 0], //
                             a[i + 1][j + 0], //
                             a[i + 2][j + 0], //
                             a[i + 0][j + 1], //
                             a[i + 1][j + 1], //
                             a[i + 2][j + 1], //
                             a[i + 0][j + 2], //
                             a[i + 1][j + 2], //
                             a[i + 2][j + 2]));
      }
    res = (int)st.size();
  } else if (op == ANIMALS1) {
    for (const auto &[i, j] : indexs)
      if (is_animal(i, j)) {
        res += is_empty(i - 1, j);
        res += is_empty(i + 1, j);
        res += is_empty(i, j - 1);
        res += is_empty(i, j + 1);
      }
  } else if (op == FREEDOM) {
    auto is_freedom = [&](int x, int y) {
      queue<pair<int, int>> q;
      memset(vis, 0, sizeof(vis));
      q.push({x, y});
      vis[x][y] = true;
      while (q.size()) {
        auto [ux, uy] = q.front();
        q.pop();
        for (int i = 0; i < 4; i++) {
          int vx = ux + nxt[i][0];
          int vy = uy + nxt[i][1];
          if (is_border(vx, vy)) return true;
          if (is_empty(vx, vy) && !vis[vx][vy]) {
            vis[vx][vy] = true;
            q.push({vx, vy});
          }
        }
      }
      return false;
    };
    for (const auto &[i, j] : indexs) {
      if (a[i][j] != ' ') {
        if (is_freedom(i, j)) {
          ++res;
        }
      }
      // cerr << (a[i][j] != ' ' && is_freedom(i, j)) << " \n"[j == n];
    }
  } else if (op == CHUPACABRA) {
    for (const auto &[i, j] : indexs)
      if (is_bird(i, j)) {
        bool fl = false;
        if (is_chupacabra(i - 1, j - 2)) fl = true;
        if (is_chupacabra(i + 1, j - 2)) fl = true;
        if (is_chupacabra(i - 1, j + 2)) fl = true;
        if (is_chupacabra(i + 1, j + 2)) fl = true;
        if (is_chupacabra(i - 2, j - 1)) fl = true;
        if (is_chupacabra(i + 2, j - 1)) fl = true;
        if (is_chupacabra(i - 2, j + 1)) fl = true;
        if (is_chupacabra(i + 2, j + 1)) fl = true;
        if (fl) {
          ++res;
        }
      }
  } else if (op == PEAKS) {
    vector<pair<int, int>> p;
    for (const auto &[i, j] : indexs)
      if (a[i][j] == '/' && j + 1 <= n && a[i][j + 1] == '\\') {
        p.emplace_back(i, j);
      }
    if (p.size() < 2) return 0;
    for (const auto &[i, j] : p) {
      int cur = 0;
      for (const auto &[x, y] : p) cur = max(cur, absi(x - i) + absi(y - j));
      // cerr << "peaks " << i << " " << j << " :: " << cur << endl;
      res += cur;
    }
  } else if (op == DRAKE_GRILL) {
    for (const auto &[i, j] : indexs)
      if (a[i][j] == 'D') {
        bool fl = false;
        if (!is_border(i - 1, j) && a[i - 1][j] == 'G') fl = true;
        if (!is_border(i + 1, j) && a[i + 1][j] == 'G') fl = true;
        if (!is_border(i, j - 1) && a[i][j - 1] == 'G') fl = true;
        if (!is_border(i, j + 1) && a[i][j + 1] == 'G') fl = true;
        if (fl) {
          ++res;
        }
      }
  } else if (op == MINIMUM_FREQUENCY) {
    map<char, int> mp;
    for (const auto &[i, j] : indexs)
      if (a[i][j] != ' ') {
        ++mp[a[i][j]];
      }
    int mn = INT_MAX;
    for (const auto &[x, y] : mp) {
      mn = min(mn, y);
    }
    for (const auto &[x, y] : mp) {
      if (y == mn) res += y;
    }
  } else if (op == EMPTY_FIELDS) {
    for (const auto &[i, j] : indexs) {
      if (a[i][j] == ' ') ++res;
    }
  } else if (op == ANIMALS2) {
    int cnt[] = {0, 0, 0};
    for (const auto &[i, j] : indexs) {
      if (a[i][j] == '!') ++cnt[0];
      if (a[i][j] == 'v') ++cnt[1];
      if (a[i][j] == 'D') ++cnt[2];
    }
    res = cnt[0] * cnt[1] * cnt[2];
  } else if (op == HOUSE_VIEW_DOWN) {
    return get(HOUSE_VIEW_UP);
  } else if (op == GIRLL_DRAKE) {
    for (const auto &[i, j] : indexs) {
      if (a[i][j] == 'D') {
        a[i][j] = 'G';
      } else if (a[i][j] == 'G') {
        a[i][j] = 'D';
      }
    }
    res = get(DRAKE_GRILL);
    for (const auto &[i, j] : indexs) {
      if (a[i][j] == 'D') {
        a[i][j] = 'G';
      } else if (a[i][j] == 'G') {
        a[i][j] = 'D';
      }
    }
  } else if (op == HOUSE_AND_GRILLS) {
    int cnt[] = {0, 0};
    for (const auto &[i, j] : indexs) {
      if (a[i][j] == '^') ++cnt[0];
      if (a[i][j] == 'G') ++cnt[1];
    }
    res = min(cnt[0], cnt[1]);
  }
  return res;
}
} // namespace mem
int main() {
#ifdef memset0
  freopen("A.in", "r", stdin);
#endif
  using namespace mem;
  ios::sync_with_stdio(0), cin.tie(0);
  string str;
  cin >> n, getline(cin, str);
  for (int i = 1; i <= n; i++) {
    getline(cin, str);
    for (int j = 1; j <= n; j++) {
      a[i][j] = str[j - 1];
      indexs.emplace_back(i, j);
    }
  }
  long long ans = 0;
  for (OPER op : opers) {
    int cnt = get(op);
    cerr << names[op] << ": " << cnt << " * " << values[op] << endl;
    ans += (long long)cnt * values[op];
  }
  cout << ans << endl;
}