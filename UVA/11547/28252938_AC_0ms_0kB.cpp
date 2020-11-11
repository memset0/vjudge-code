#include <bits/stdc++.h>
using namespace std;

int sw(long long a) { return a / 10 % 10; }
long long js(long long a) { return (a * 567 / 9 + 7492) * 235 / 47 - 498; }

int main() {
  int t;
  cin >> t;
  long long a;
  for (t; t > 0; t--) {
    cin >> a;
    a = js(a);
    cout << abs(sw(a)) << endl;
  }
}