#include <bits/stdc++.h>
using namespace std;
int main() {
  int a, b, c;
  cin >> a >> b >> c;
  b += c / 25, c %= 25;
  a += b / 4, b %= 4;
  a = a / 10 + a % 10;
  cout << (a + b + c) << endl;
}