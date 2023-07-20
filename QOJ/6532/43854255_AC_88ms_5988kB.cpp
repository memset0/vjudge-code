#include <bits/stdc++.h>
using namespace std;
const int N = 1e6 + 9;
int t, n;
struct node {
  long long A, B;
} f[N];
inline bool cmp(const node &f1, const node &f2) { return f1.A < f2.A; }
int main() {
  ios::sync_with_stdio(0), cin.tie(0);
  cin >> t;
  while (t--) {
    cin >> n;
    for (int i = 1; i <= n; i++) cin >> f[i].A >> f[i].B;
    sort(f + 1, f + n + 1, cmp);
    int i = 1, j = n;
    long long s = 0;
    while (i < j) {
      long long c = min(f[j].B, f[i].B);
      // cerr << f[i].A << "," << f[i].B << "," << f[j].A << "," << f[j].B << endl;
      s += (f[j].A - f[i].A) * c;
      f[j].B -= c;
      f[i].B -= c;
      if (!f[i].B) i++;
      if (!f[j].B) j--;
    }
    cout << s << endl;
  }
}