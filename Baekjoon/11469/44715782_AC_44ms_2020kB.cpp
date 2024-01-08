#include <bits/stdc++.h>
using namespace std;

int T;
long long n;
vector<long long> ans;

void divide(long long n, long long x) {
  if (!n)
    return;
  if (n % 2 == 0) {
    divide(n / 2, x * 2);
  } else if (n % 3 == 0) {
    divide(n / 3, x * 3);
  } else {
    long long tmp = 1;
    while (tmp * 3 <= n) {
      tmp *= 3;
    }
    ans.push_back(x * tmp);
    divide(n - tmp, x);
  }
}

int main() {
  ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
  for (cin >> T; T; --T) {
    ans.clear();
    cin >> n;
    divide(n, 1);
    cout << ans.size() << endl;
    for (int i = 0; i < (int)ans.size(); i++) {
      cout << ans[i] << " \n"[i + 1 == ans.size()];
    }
  }
}