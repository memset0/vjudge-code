#include <cstdio>
#include <cstring>
#include <iostream>
using namespace std;
int main() {
  int m, a[12][12], cnt = 0;
  char s[100][100];
  int flag[100][100];
  bool fir = true;
  while (cin >> m && m) {
    memset(s, 0, sizeof(s));
    memset(flag, 0, sizeof(flag));
    if (fir) {
      fir = false;
    } else {
      cout << endl;
    }
    // 依照规律，将区域初始化
    for (int i = 0; i < 4 * m + 3; ++i) {
      s[0][i] = '*';
      s[4 * m - 2][i] = '*';
    }
    for (int i = 0; i < 4 * m - 1; ++i) {
      s[i][0] = '*';
      s[i][4 * m + 2] = '*';
    }
    /*for(int i=0;i<4*m+3;++i)
        for(int j=0;j<4*m+3;++j)
    {
        cout<<s[i][j];
        if(j==4*m+2) cout<<endl;
    }*/
    for (int i = 1; i <= 4 * m - 3; i = i + 4)
      for (int j = 1; j <= 4 * m + 1; ++j) {
        if (j % 4 == 1) s[i][j] = 'H';
        if (j % 4 == 2 || j % 4 == 0) s[i][j] = ' ';
        if (j % 4 == 3) s[i][j] = 'O';
      }
    for (int i = 3; i <= 4 * m - 5; i = i + 4)
      for (int j = 1; j <= 4 * m + 1; ++j) {
        if (j % 4 == 3) s[i][j] = 'H';
        else
          s[i][j] = ' ';
      }
    for (int i = 2; i <= 4 * m - 4; i = i + 2)
      for (int j = 1; j <= 4 * m + 1; ++j) {
        s[i][j] = ' ';
      }
    /*for(int i=0;i<4*m+3;++i)
        for(int j=0;j<4*m+3;++j)
    {
        cout<<s[i][j];
        if(j==4*m+2) cout<<endl;
    }*/
    for (int i = 0; i < m; ++i)
      for (int j = 0; j < m; ++j) {
        cin >> a[i][j];
      }
    // 将易确定的1和-1先确定下来
    for (int i = 0; i < m; ++i)
      for (int j = 0; j < m; ++j) {
        if (a[i][j] == 1) {
          flag[4 * i + 1][4 * j + 3] = 1;
          flag[4 * i + 1][4 * j + 1] = 1;
          flag[4 * i + 1][4 * j + 5] = 1;
          s[4 * i + 1][4 * j + 2] = '-';
          s[4 * i + 1][4 * j + 4] = '-';
        } else if (a[i][j] == -1) {
          flag[4 * i + 1][4 * j + 3] = 1;
          flag[4 * i - 1][4 * j + 3] = 1;
          flag[4 * i + 3][4 * j + 3] = 1;
          s[4 * i][4 * j + 3] = '|';
          s[4 * i + 2][4 * j + 3] = '|';
        }
      }
    for (int i = 0; i < m; ++i)
      for (int j = 0; j < m; ++j) {
        if (a[i][j] == 0) {
          if (flag[4 * i + 1][4 * j + 1] == 1) {
            s[4 * i + 1][4 * j + 4] = '-';
            flag[4 * i + 1][4 * j + 5] = 1;
          } else {
            flag[4 * i + 1][4 * j + 1] = 1;
            s[4 * i + 1][4 * j + 2] = '-';
          }
          if (4 * i - 1 > 0 && flag[4 * i - 1][4 * j + 3] != 1) {
            flag[4 * i - 1][4 * j + 3] = 1;
            s[4 * i][4 * j + 3] = '|';
          } else if (4 * i + 3 < 4 * m - 2 && flag[4 * i + 3][4 * j + 3] != 1) {
            flag[4 * i + 3][4 * j + 3] = 1;
            s[4 * i + 2][4 * j + 3] = '|';
          }
        }
      }
    cout << "Case " << ++cnt << ":" << endl << endl;
    for (int i = 0; i < 4 * m - 1; ++i)
      for (int j = 0; j < 4 * m + 3; ++j) {
        cout << s[i][j];
        if (j == 4 * m + 2) cout << endl;
      }
  }
  return 0;
}