#include <bits/stdc++.h>
using namespace std;

inline bool cmp(int x, int y) { return x < y; }
inline bool triangle(int x, int y, int z) {
  int ary[3] = {x, y, z};
  sort(ary, ary + 3, cmp);

  if ((ary[0] + ary[1]) > ary[2]) {
    return true;
  }
  return false;
}

int main() {
  int n = 0;
  cin >> n;

  struct node {
    int a;
    int b;
    int c;
    bool can;
  } st[n + 5];

  for (int i = 0; i < n; i++) {
    cin >> st[i].a >> st[i].b >> st[i].c;
    st[i].can = false;
  }

  for (int i = 0; i < n; i++) {
    st[i].can = triangle(st[i].a, st[i].b, st[i].c);
  }
  for (int i = 0; i < n; i++) {
    if (st[i].can == false) {
      cout << "Wrong!!" << endl;
    } else {
      cout << "OK" << endl;
    }
  }

  return 0;
}