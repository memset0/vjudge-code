#include <bits/stdc++.h>
using namespace std;
int main() {
  long long a, b, c;
  cin >> a >> b >> c;
  if (a % c == 0 && b % c == 0) {
    cout << (a / c) * (b / c) << endl;
  } else {
    cout << -1 << endl;
  }
}