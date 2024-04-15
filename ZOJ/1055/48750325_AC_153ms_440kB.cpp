#include <cmath>
#include <cstdlib>
#include <iostream>
#include <math.h>
#include <queue>
#include <stack>
#include <stdio.h>
#include <string.h>
using namespace std;
const int AX = 30 + 6;
const int maxn = 5e5;
char G[AX][AX];
int vis[AX][AX];
int oddEven[AX][AX]; // 剪枝
int ibest;
double sum[AX][AX];
double res[AX][AX];
int n, m;
int dir[4][2] = {{1, 0}, {-1, 0}, {0, -1}, {0, 1}};
struct Node {
  int x, y;
  int step;
} q, pos;
void bfs(Node s, Node e) {
  queue<Node> que;
  s.step = 0;
  que.push(s);
  vis[s.x][s.y] = 1;
  ibest = -1;
  while (!que.empty()) {
    q = que.front();
    que.pop();
    if (q.x == e.x && q.y == e.y) {
      ibest = q.step;
      return;
    }
    for (int i = 0; i < 4; i++) {
      int xx = q.x + dir[i][0];
      int yy = q.y + dir[i][1];
      if (xx >= 0 && xx < m && yy >= 0 && yy < n && G[xx][yy] != 'X' && !vis[xx][yy]) {
        pos.x = xx;
        pos.y = yy;
        pos.step = q.step + 1;
        que.push(pos);
        vis[xx][yy] = 1;
      }
    }
  }
  return;
}
stack<Node> sb;
stack<Node> sb_copy;
int num;
void dfs(int x, int y, int val, int len, Node s, Node e) {
  if (num >= maxn) return;
  if (len > ibest) return;
  if (G[x][y] >= 'A' && G[x][y] <= 'Z') { // 建筑物不能走
    if (x == s.x && y == s.y) {
    } else if (x == e.x && y == e.y) {
      if (len == ibest) {
        num++;
        while (sb.size()) {
          sb_copy.push(sb.top());
          sb.pop();
        }
        Node tmp;
        while (sb_copy.size()) {
          tmp = sb_copy.top();
          if (tmp.x >= 0 && tmp.x < m && tmp.y >= 0 && tmp.y < n) {
            sum[tmp.x][tmp.y] += (double)(val);
            sb.push(tmp);
          }
          sb_copy.pop();
        }
      }
      return;
    } else {
      return;
    }
  }
  if (((ibest - len) % 2) != (abs(oddEven[x][y] - oddEven[e.x][e.y]) % 2)) { // 奇偶剪枝
    return;
  }
  for (int i = 0; i < 4; i++) {
    int xx = x + dir[i][0];
    int yy = y + dir[i][1];
    if (xx >= 0 && xx < m && yy >= 0 && yy < n && G[xx][yy] != 'X' && !vis[xx][yy]) {
      Node tmp;
      tmp.x = xx;
      tmp.y = yy;
      sb.push(tmp);
      vis[xx][yy] = 1;
      dfs(xx, yy, val, len + 1, s, e);
      sb.pop();
      vis[xx][yy] = 0;
    }
  }
}
int main() {
  scanf("%d%d", &n, &m);
  for (int i = 0; i < m; i++) {
    scanf("%s", G[i]);
  }
  char op[10];
  int t;
  // 奇偶剪枝数组初始化 TE的话就加上这个
  for (int i = 0; i < m; i++) {
    if (i % 2) {
      for (int j = 0; j < n; j++) {
        if (j % 2 == 1) {
          oddEven[i][j] = 1;
        } else {
          oddEven[i][j] = 0;
        }
      }
    } else {
      for (int j = 0; j < n; j++) {
        if (j % 2 == 1) {
          oddEven[i][j] = 0;
        } else {
          oddEven[i][j] = 1;
        }
      }
    }
  }
  while (scanf("%s%d", op, &t)) {
    memset(sum, 0.00, sizeof(sum));
    memset(vis, 0, sizeof(vis));
    if (!t) break;
    Node s, e;
    for (int i = 0; i < m; i++) {
      for (int j = 0; j < n; j++) {
        if (G[i][j] == op[0]) {
          s.x = i;
          s.y = j;
        } else if (G[i][j] == op[1]) {
          e.x = i;
          e.y = j;
        }
      }
    }
    if ((abs(s.x - e.x) == 1 && s.y == e.y) || (abs(s.y - e.y) == 1 && s.x == e.x)) {
    } else {
      // cout << s.x << ' ' << s.y << endl;
      bfs(s, e);
      num = 0;
      memset(vis, 0, sizeof(vis));
      memset(sum, 0.00, sizeof(sum));
      vis[s.x][s.y] = 1;
      while (sb.size()) sb.pop();
      while (sb_copy.size()) sb_copy.pop();
      dfs(s.x, s.y, t, 0, s, e);
      for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
          res[i][j] += double(sum[i][j] / num);
        }
      }
    }
  }
  double tmp = 0.00;
  for (int i = 0; i < m; i++) {
    for (int j = 0; j < n; j++) {
      if (j) printf(" ");
      if (G[i][j] == '.') printf("%6.2f", (double)res[i][j]);
      else
        printf("%6.2f", tmp);
    }
    cout << endl;
  }
  return 0;
}