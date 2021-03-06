#include <bits/stdc++.h>
using namespace std;

const int N = 100005;

int n, m, mu[N], a[N], b[N];
vector<int> va[N], vb[N];

long long solve(int x, int mid) {
  int n = va[x].size();
  int j = 0;
  long long ans = 0;
  for (int i = 0; i < n; ++i) {
    while (j < n && va[x][i] - vb[x][j] >= mid) {
      ++j;
    }
    ans += j;
  }
  j = n - 1;
  for (int i = n - 1; ~i; --i) {
    while (~j && vb[x][j] > va[x][i] && vb[x][j] - va[x][i] >= mid) {
      --j;
    }
    ans += n - j - 1;
  }
  return ans;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);

  cin >> n;
  for (int i = 1; i <= n; ++i) {
    cin >> a[i];
    m = max(m, a[i]);
  }
  for (int i = 1; i <= n; ++i) {
    cin >> b[i];
    m = max(m, b[i]);
  }

  mu[1] = 1;
  for (int i = 1; i <= n; ++i) {
    for (int j = i + i; j <= n; j += i) {
      mu[j] -= mu[i];
    }
  }
  for (int i = 1; i <= n; ++i) {
    va[i].resize(n / i), vb[i].resize(n / i);
    for (int j = 0; j < (int)va[i].size(); ++j) {
      va[i][j] = a[i * (j + 1)];
      vb[i][j] = b[i * (j + 1)];
    }
    sort(va[i].begin(), va[i].end());
    sort(vb[i].begin(), vb[i].end());
  }
  for (int k = 1; k <= n; ++k) {
    int l = 0, r = m, ans = -1;
    while (l <= r) {
      int mid = (l + r) >> 1;
      long long sum = 0;
      for (int d = 1; d <= n / k; ++d) {
        sum += mu[d] * solve(k * d, mid);
      }
      if (sum > 0) {
        ans = mid;
        l = mid + 1;
      } else {
        r = mid - 1;
      }
    }
    cout << ans << " \n"[k == n];
  }
}