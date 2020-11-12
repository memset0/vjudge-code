#include <bits/stdc++.h>
using namespace std;

const string mark = "111110111100 110000100000";
unordered_set<string> us;
int n;
struct node {
  string s;
  int num;
};

int bfs(node start) {
  queue<node> Q;
  Q.push(start);
  while (!Q.empty()) {
    node head = Q.front();
    Q.pop();
    if (head.s == mark) {
      return head.num;
    }
    if (head.num >= 10) {
      continue;
    }
    int blank_pos = head.s.find(' ');
    int blank_row = blank_pos / 5;
    int blank_col = blank_pos % 5;
    for (int row = -2; row <= 2; row++) {
      for (int col = -2; col <= 2; col++) {
        if (abs(row) == abs(col) || row == 0 || col == 0)
          continue;
        if (blank_row + row < 0 || blank_row + row > 4 || blank_col + col < 0 ||
            blank_col + col > 4)
          continue;
        int pos = (blank_row + row) * 5 + (blank_col + col);
        node tmp = head;
        swap(tmp.s[blank_pos], tmp.s[pos]);
        if (us.find(tmp.s) != us.end())
          continue;
        us.insert(tmp.s);
        tmp.num++;
        Q.push(tmp);
        if (tmp.s == mark)
          return tmp.num;
      }
    }
  }
  return 11;
}

int main() {
  ios::sync_with_stdio(false), cin.tie(0), cout.tie(0);
  cin >> n;
  cin.ignore();
  while (n--) {
    us.clear();
    string s;
    for (int i = 1; i <= 5; i++) {
      string tmp;
      getline(cin, tmp);
      s += tmp;
    }
    node start;
    start.s = s;
    start.num = 0;
    int ans = bfs(start);
    if (ans < 11) {
      cout << "Solvable in " << ans << " move(s)." << endl;
    } else {
      cout << "Unsolvable in less than " << ans << " move(s)." << endl;
    }
  }
}