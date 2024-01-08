#include <bits/stdc++.h>
using namespace std;
const int N = 1e6 + 9;
int n;
vector<int> a;
int main() {
  cin >> n;
  while (n != 1) {
    a.push_back(n);
    if (n % 2 == 0) {
      n /= 2;
    } else {
      n = 3 * n + 1;
    }
  }
  a.push_back(1);
  reverse(a.begin(), a.end());
  for (int i = 0; i < a.size(); i++) { cout << a[i] << " \n"[i + 1 == a.size()]; }
}