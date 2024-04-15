#include <algorithm>
#include <cstdio>
#include <map>
#include <vector>
 
using namespace std;
 
int n;
vector<int> board[6][6];
int capacity[6][6];
 
void Move(int k, vector<int>* x, vector<int>* y) {
  y->insert(y->end(), x->end() - k, x->end());
  x->erase(x->end() - k, x->end());
}
 
void Walk(pair<int, int> src, pair<int, int> dst) {
  for (; src.first != dst.first; ++src.first) {
    printf("%d %d D 1\n", src.first + 1, src.second + 1); 
    Move(1, &board[src.first][src.second], &board[src.first + 1][src.second]);
  }
  for (; src.second != dst.second; ++src.second) {
    printf("%d %d R 1\n", src.first + 1, src.second + 1); 
    Move(1, &board[src.first][src.second], &board[src.first][src.second + 1]);
  }
}
 
void Solve(int r, int c, int a, int b) {
  if (r == 5 && c == 5) {
    return;
  }
  if ((r + c == 9) && (b - a + 1 == 2)) {
    const char dir = (r == 5) ? 'R' : 'D';
    if (board[r][c].back() == b) {
      printf("%d %d %c 1\n", r + 1, c + 1, dir);
      printf("%d %d %c 1\n", r + 1, c + 1, dir);
    } else {
      printf("%d %d %c 2\n", r + 1, c + 1, dir);
    }
    return;
  }
  map<int, pair<int, int>> target;
  map<pair<int, int>, int> lo;
  map<pair<int, int>, int> hi;
  int next = b;
  for (int i = 5; i >= r; --i) {
    for (int j = 5; j >= c; --j) {
      if (i == r && j == c) continue;
      if (next < a) continue;
      const pair<int, int> p(i, j);
      hi[p] = next;
      for (int k = 0; k < capacity[i][j] && next >= a; ++k) {
        lo[p] = next;
        target[next--] = p;
      }
    }
  }
 
  const int k = b - a + 1;
  for (int i = 0; i < k; ++i) {
    int x = board[r][c].back();
    Walk(make_pair(r, c), target[x]);
  }
  for (int i = 5; i >= r; --i) {
    for (int j = 5; j >= c; --j) {
      const pair<int, int> p(i, j);
      if (!hi.count(p)) continue;
      Solve(i, j, lo[p], hi[p]);
    }
  }
}
 
int main() {
  capacity[5][5] = 1;
  capacity[4][5] = 2;
  capacity[5][4] = 2;
  for (int r = 5; r >= 0; --r) {
    for (int c = 5; c >= 0; --c) {
      if (capacity[r][c] == 0) {
        for (int i = r; i <= 5; ++i) {
          for (int j = c; j <= 5; ++j) {
            if (i == r && j == c) continue;
            capacity[r][c] += capacity[i][j];
          }
        }
      }
    }
  }
 
  scanf("%d", &n);
  board[0][0].resize(n);
  for (int i = 0; i < n; ++i) scanf("%d", &board[0][0][i]);
 
  Solve(0, 0, 1, n);
  
  return 0;
}