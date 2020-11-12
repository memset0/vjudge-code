#include <bits/stdc++.h>

inline int read() {
  char c, _c;
  int x;
  for (c = _c = getchar(); !isdigit(c); c = getchar()) {
    _c = c;
  }
  for (x = 0; isdigit(c); c = getchar()) {
    x = x * 10 + c - '0';
  }
  return _c == '-' ? -x : x;
}

const double pi = acos(-1);

int T, xa, ya, xb, yb, xc, yc;

bool check() {
  double a = atan2(yb, xb) - atan2(ya, xa);
  double b = atan2(yc, xc) - atan2(ya, xa);
  if (a < 0) {
    a += pi * 2;
  }
  if (b < 0) {
    b += pi * 2;
  }
  return a > b;
}

int main() {
  for (int T = read(); T; T--) {
    xa = read();
    ya = read();
    xb = read();
    yb = read();
    xc = read();
    yc = read();
    printf("%s\n", check() ? "Clockwise" : "Counterclockwise");
  }
  return 0;
}