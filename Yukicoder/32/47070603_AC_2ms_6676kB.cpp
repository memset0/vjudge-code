#include <bits/stdc++.h>
using namespace std;
int main() {
  int a, b, c;
  cin >> a >> b >> c;
  b += c / 25, c %= 25;
  a += b / 4, b %= 4;
  cout << (a % 10 + b + c) << endl;
}