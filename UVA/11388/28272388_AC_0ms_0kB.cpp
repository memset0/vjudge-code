#include <bits/stdc++.h>
using namespace std;

int main() {
  ios::sync_with_stdio(0);
  long long iNum1, iNum2;
  int nCount;

  cin >> nCount;
  for (int i = 1; i <= nCount; ++i) {
    cin >> iNum1 >> iNum2;
    if (iNum2 % iNum1 == 0) {
      cout << iNum1 << ' ' << iNum2 << endl;
    } else {
      cout << "-1\n";
    }
  }
}