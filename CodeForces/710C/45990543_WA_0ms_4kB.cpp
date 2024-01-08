#include <bits/stdc++.h>
using namespace std;
int main() {
  ios::sync_with_stdio(0), cin.tie(0);
  int n;
  cin >> n;
  auto a = vector<vector<int>>(n, vector<int>(n, 0));
  for (int i = 0; i < n; i++) { a[i][i] = 1; }
  for (int i = 1; i < n; i += 2) { a[i][i] = 0; }
  for (int i = 0; i < n; i++)
    for (int j = i + 1; j < n; j++) { a[i][j] = 1; }
  int x[2] = {2, 1};
  for (int i = 0; i < n; i++)
    for (int j = 0; j < n; j++) {
      cout << x[a[i][j]] << " \n"[j + 1 == n];
      x[a[i][j]] += 2;
    }
}