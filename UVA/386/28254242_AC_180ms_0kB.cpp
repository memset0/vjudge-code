#include <cstdio>
using namespace std;

int n, cnt, m;
inline int s(int n) { return n * n * n; }

int main() {
  for (int i = 1; i <= 200; ++i) {
    for (int j = 2; j <= 200; ++j) {
      for (int k = j + 1; k <= 200; ++k) {
        for (int l = k + 1; l <= 200; ++l) {
          if (s(i) == s(j) + s(k) + s(l)) {
            printf("Cube = %d, Triple = (%d,%d,%d)\n", i, j, k, l);
          }
        }
      }
    }
  }
}