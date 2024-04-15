#include <algorithm>
#include <cmath>
#include <float.h>
#include <iomanip>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define sf scanf
#define pf printf
#define pb push_back
#define mm(x, b) memset((x), (b), sizeof(x))
#include <map>
#include <vector>
#define rep(i, a, n) for (int i = a; i < n; i++)
#define per(i, a, n) for (int i = a; i >= n; i--)
typedef long long ll;
typedef long double ld;
typedef double db;
const ll mod = 1e12 + 100;
const db e = exp(1);
using namespace std;
const double pi = acos(-1.0);
char a[25][25];
int sum;
void dfs(int x, int y) {
  //	cout<<x<<" "<<y<<endl;

  a[x][y] = 'a'; // 把经过的位置改变

  if (a[x + 1][y] == '.') sum++;
  if (a[x - 1][y] == '.') sum++;
  if (a[x][y + 1] == '.') sum++;
  if (a[x][y - 1] == '.') sum++;
  if (a[x - 1][y - 1] == 'X') // 左上
    dfs(x - 1, y - 1);
  if (a[x - 1][y + 1] == 'X') // 右上
    dfs(x - 1, y + 1);
  if (a[x + 1][y - 1] == 'X') // 左下
    dfs(x + 1, y - 1);
  if (a[x + 1][y + 1] == 'X') // 右下
    dfs(x + 1, y + 1);
  if (a[x - 1][y] == 'X') // 上
    dfs(x - 1, y);
  if (a[x][y - 1] == 'X') // 左
    dfs(x, y - 1);
  if (a[x][y + 1] == 'X') // 右
    dfs(x, y + 1);
  if (a[x + 1][y] == 'X') // 下
    dfs(x + 1, y);
}
int main() {
  int n, m, x, y;
  while (1) {
    sum = 0;
    char d[25][25];
    sf("%d%d%d%d", &n, &m, &x, &y);
    if (!n && !m) return 0;
    mm(a, '.');
    rep(i, 1, n + 1) {
      sf("%s", &a[i][1]);
      // pf("1%s\n",&d[i]);
      a[i][m + 1] = '.';
    }
    dfs(x, y);
    pf("%d\n", sum);
  }
}
