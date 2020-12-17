#include <bits/stdc++.h>
using namespace std;
int n;

int prime(int x) {
  for (int i = 2; i <= sqrt(x); i++) {
    if (x % i == 0)
      return false;
  }
  return true;
}

int main() {
  while (true) {
    cin >> n;
    if (n == 0)
      break;
    for (int i = 1; i <= n; i++) {
      if (n % i == 0) {
        if (prime(n / i)) {
          printf("%d\n", n / i);
          break;
        }
      }
    }
  }
  return 0;
}