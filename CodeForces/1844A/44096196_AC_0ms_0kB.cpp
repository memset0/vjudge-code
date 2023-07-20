#include <bits/stdc++.h>
#define ll long long
#define pb push_back
#define eb emplace_back
#define rep(i, l, r) for (int i = (l), i##end = (r); i <= i##end; i++)
#define per(i, r, l) for (int i = (r), i##end = (l); i >= i##end; i--)
using namespace std;

const int N = 1e6 + 9;
int T, a, b;

int main() {
#ifdef memset0
  freopen("A.in", "r", stdin);
#endif
  cin >> T;
  while (T--) {
    cin >> a >> b;
    cout << a + b << endl;
  }
}