#include <bits/stdc++.h>
using namespace std;
int n;
char a[1005];

int main() {
  cin >> n;
  for (int i = 1; i <= n; i++) {
    cin >> a;
    int A = 0, G = 0, I = 0, M = 0, R = 0, T = 0, p = 0;
    for (int j = 0; j < strlen(a); j++) {
      if (a[j] == 'A')
        A++;
      if (a[j] == 'G')
        G++;
      if (a[j] == 'I')
        I++;
      if (a[j] == 'M')
        M++;
      if (a[j] == 'R')
        R++;
      if (a[j] == 'T')
        T++;
    }
    while (true) {
      if (A < 3 || G < 1 || I < 1 || M < 1 || R < 2 || T < 1) {
        break;
      }
      A -= 3;
      G--;
      I--;
      M--;
      R -= 2;
      T--;
      p++;
    }
    cout << p << endl;
  }
  return 0;
}