#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <list>
#include <set>
#include <stack>
#include <string>
#include <vector>

using namespace std;

int main() {
#ifdef memset0
  freopen("temp.in", "r", stdin);
#endif
  int n;
  while (cin >> n, cin.ignore() && n) {
    int board[52][52];

    for (int i = 0; i < 52; ++i) {
      for (int j = 0; j < 52; ++j) {
        if (i == 0 || i == 51 || j == 0 || j == 51) board[i][j] = -1;
        else if (i == 25 && j >= 11 && j <= 30)
          board[i][j] = j - 10;
        else
          board[i][j] = 0;
      }
    }

    // for (int i = 0; i < 52; ++i) {
    //   for (int j = 0; j < 52; ++j) {
    //     cout << board[i][j];
    //   }
    //   cout << endl;
    // }

    // char illegalMove = 'W';
    pair<int, int> head(25, 30), tail(25, 11);
    int h = 20, t = 1, m = 0;
    while (m++ < n) {
      int r, c;
      char ch = getchar();
      switch (ch) {
      case 'W':
        head.second--;
        break;
      case 'E':
        head.second++;
        break;
      case 'N':
        head.first--;
        break;
      case 'S':
        head.first++;
        break;
      default:
        break;
      }
      if (board[head.first][head.second] == -1) {
        cout << "The worm ran off the board on move " << m << "." << endl;
        break;
      } else if (board[head.first][head.second] > t) {
        cout << "The worm ran into itself on move " << m << "." << endl;
        break;
      } else {
        board[head.first][head.second] = ++h;
        ++t;
      }
    }
    if (m == n + 1) cout << "The worm successfully made all " << n << " moves." << endl;
    while (m++ < n) getchar();
  }
}