#include <bits/stdc++.h>
using namespace std;
const int mod = 233333;

int a[50010], ha[mod], ans = 199, last[50010], n;

void add(int k, int i) {
  int x = k % mod;
  last[i] = ha[x];
  ha[x] = i;
}

bool find(int k) {
  if (k > a[n]) {
    return 0;
  }
  for (int i = ha[k % mod]; i; i = last[i])
    if (a[i] == k) {
      return 1;
    }
  return 0;
}

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0);
  cin >> n;
  for (int i = 1; i <= n; i++) {
    cin >> a[i];
  }
  sort(a + 1, a + n + 1);
  for (int i = 1; i <= n; i++) {
    add(a[i], i);
  }
  for (int i = 2; i <= n - ans; i++) {
    int j = i - 1, k = i + 1;
    while (j > 0 && k <= n) {
      if (a[j] + a[k] > 2 * a[i]) {
        j--;
      } else if (a[j] + a[k] < 2 * a[i]) {
        k++;
      } else {
        long long d = a[i] - a[j];
        long long maxn = d * (long long)ans + (long long)a[j];
        if (maxn > a[n])
          break;
        int now = 3, now1 = a[k] + d;
        for (; find(now1); now1 += d)
          now++;
        ans = max(ans, now);
        j--;
        k++;
      }
    }
  }
  // cout<<ans<<endl;
  if (ans >= 200) {
    printf("%d\n", ans);
  } else {
    printf("No Solution\n");
  }
  return 0;
}