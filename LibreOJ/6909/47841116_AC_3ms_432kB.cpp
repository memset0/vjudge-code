#include <bits/stdc++.h>
using namespace std;
const int N = (1 << 25) + 7;
char s[12][12], w[12][12];
int T, num[12][12], res[12][12], ans[N];
int a[123213];
bool dfs(int u) {
  if (ans[u] != -1) return ans[u];
  int T = 0;
  bool flag = 0;
  for (int i = 1; i <= 5; i++)
    for (int j = 1; j <= 5; j++) {
      bool fl = 0;
      for (int x = 0; x < 4; x++)
        for (int y = 0; y < 4; y++)
          if (w[x][y] == 'o' && res[i + x][y + j] == 0) fl = 1;
      if (fl == 0) {
        flag = 1;
        break;
      }
    }
  if (flag) {
    if (__builtin_popcount(u) % 3 != 0) {
      ans[u] = 1;
      return 1;
    }
    ans[u] = 0;
    return 0;
  }
  for (int i = 1; i <= 5; i++)
    for (int j = 1; j <= 5; j++) {
      if (res[i][j]) continue;
      res[i][j] = 1;
      if (!dfs(u | num[i][j])) {
        T = 1;
      }
      res[i][j] = 0;
      if (T) {
        ans[u] = T;
        return T;
      }
    }
  //	for(int i=1;i<=5;i++){
  //		for(int j=1;j<=5;j++){
  //			cout<<res[i][j];
  //		}
  //		cout<<endl;
  //	}
  //	cout<<T<<endl;
  ans[u] = T;
  return T;
}
signed main() {
  //	freopen("in.txt","w",stdout);
  cin >> T;
  while (T--) {
    int x = 10, y = 10, cnt = 0;
    for (int i = 1; i <= 5; i++)
      for (int j = 1; j <= 5; j++) num[i][j] = (1 << cnt), cnt++;
    for (int i = 1; i <= 9; i++)
      for (int j = 1; j <= 9; j++) s[i][j] = '.';
    for (int i = 1; i <= 5; i++)
      for (int j = 1; j <= 5; j++) {
        char g = getchar();
        while (g != '.' && g != 'o') s[i][j] = g, g = getchar();
        if (g == 'o') {
          x = min(x, i);
          y = min(y, j);
        }
        s[i][j] = g;
      }
    for (int c = 0; c < 4; c++)
      for (int d = 0; d < 4; d++) w[c][d] = s[x + c][y + d];
    memset(res, 0, sizeof(res));
    int R = 0, W = 0;
    for (int c = 0; c < 4; c++)
      for (int d = 0; d < 4; d++) {
        if (w[c][d] == 'o') R |= (1 << W);
        W++;
      }
    a[3] = 1;
    a[17] = 1;
    a[1] = 0;
    a[50] = 0;
    a[19] = 0;
    a[49] = 0;
    a[35] = 0;
    a[273] = 0;
    a[7] = 0;
    a[51] = 0;
    a[15] = 0;
    a[4369] = 0;
    a[54] = 1;
    a[99] = 1;
    a[561] = 1;
    a[306] = 1;
    a[562] = 1;
    a[305] = 1;
    a[114] = 1;
    a[39] = 1;
    a[51] = 0;
    a[802] = 1;
    a[785] = 1;
    a[547] = 1;
    a[275] = 1;
    a[116] = 1;
    a[71] = 1;
    a[23] = 1;
    a[113] = 1;
    if (a[R]) puts("Far");
    else
      puts("Away");
  }
  return 0;
}
