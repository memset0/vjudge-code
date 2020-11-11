#include <bits/stdc++.h>
using namespace std;

int zjy;
double h, u, d, f, k, gy;

int main() {
  while (1) {
    cin >> h >> u >> d >> f;
    if (h == 0) {
      break;
    }
    zjy = 0;
    k = 0;
    gy = u * f / 100;
    f /= 100;
    while (1) {
      zjy++;
      k += u;
      if (k > h) {
        break;
      }
      k -= d;
      if (k < 0) {
        break;
      }
      u -= gy;
      if (u < 0) {
        u = 0;
      }
    }
    if (k > h) {
      printf("success on day %d\n", zjy);
    }
    if (k < 0) {
      printf("failure on day %d\n", zjy);
    }
  }
  return 0;
}