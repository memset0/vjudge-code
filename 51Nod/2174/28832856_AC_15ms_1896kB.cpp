#include <bits/stdc++.h>
using namespace std;

const int N = 4e6;
int T, n;
vector<int> fib;

int main() {
#ifdef memset0
  freopen("1.in", "r", stdin);
#endif
  ios::sync_with_stdio(false), cin.tie(0), cout.tie(0);

  fib.push_back(1), fib.push_back(2);
  int i = 2;
  while (fib[i - 2] + fib[i - 1] <= N) {
    fib.push_back(fib[i - 2] + fib[i - 1]);
    i++;
  }

  cin >> T;
  while (T--) {
    cin >> n;
    int it = fib.size() - 1;
    for (int i = 0; i < (int)fib.size(); i++) {
      if (fib[i] >= n) {
        it = i;
        break;
      }
    }
    if (fib[it] > n)
      it--;
    long long sum = 0;
    for (int i = 0; i <= it; i++)
      if (!(fib[i] & 1)) {
        sum += fib[i];
      }
    cout << sum << endl;
  }
}