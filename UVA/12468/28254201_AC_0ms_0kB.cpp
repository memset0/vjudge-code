#include <bits/stdc++.h>
using namespace std;
int main() {
  int a, b;
  while (1) {
    cin >> a >> b;
    if (a == -1 && b == -1)
      break;
    if (a < b)
      swap(a, b);
    cout << min(a - b, 100 - a + b) << endl;
  }
  return 0;
}