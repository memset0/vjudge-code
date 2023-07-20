#include <bits/stdc++.h>
using namespace std;

const int N = 1e5 + 9;
int n, a[N];
long long sum, ans;
vector<pair<int, int>> loc;

int main() {
#ifdef memset0
  freopen("1.in", "r", stdin);
#endif
  ios::sync_with_stdio(0), cin.tie(0);
  cin >> n;
  for (int i = 1; i <= n; i++) {
    cin >> a[i];
    loc.emplace_back(a[i], i);
  }
  sort(loc.begin(), loc.end());
  int p = 0;
  for (int x = 1; x <= n; x++) {
    int cnt = 0;
    ans -= sum; 
    fprintf(stderr, "%d : ans -= %lld\n", x, sum);
    ans += (long long)p * (x + 1);
    fprintf(stderr, "%d : ans += %lld\n", x, (long long)p * (x + 1));
    while (p < loc.size() && loc[p].first == x) {
      int i = loc[p].second;
      if (i - 1 >= 1 && a[i] > a[i - 1]) {
        cerr << "<<" << i << " " << a[i - 1] << endl;
        sum += a[i - 1];
      }
      if (i + 1 <= n && a[i] >= a[i + 1]) {
        cerr << ">>" << i << " " << a[i - 1] << endl;
        sum += a[i + 1];
      }
      p++, cnt++;
    }
    ans += (long long)cnt * x;
    fprintf(stderr, "%d : ans += %lld\n", x, (long long)cnt * x);
    sum += (long long)cnt * x;
    fprintf(stderr, "%d : sum* += %lld\n", x, (long long)cnt * x);
    cerr << endl;
  }
  cerr << ans << endl;
  p = 0;
  for (int x = 1; x <= n; x++) {
    int lst = -1, cnt = 0;
    while (p < loc.size() && loc[p].first == x) {
      if (loc[p].second != lst + 1) {
        cnt++;
      }
      lst = loc[p].second;
      p++;
    }
    ans += cnt;
  }
  cout << ans << endl;
}