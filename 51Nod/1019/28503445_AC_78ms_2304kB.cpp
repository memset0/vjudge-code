#include <bits/stdc++.h>
using namespace std;

const int N = 5e4+9;
int a[N], b[N];
long long ans;

void Count(int Sta, int Mid, int End) {
  int i = Sta, j = Mid + 1, k = Sta;
  while (i <= Mid && j <= End) {
    if (a[i] <= a[j]) {
      b[k++] = a[i++];
    } else {
      ans += j - k;
      b[k++] = a[j++];
    }
  }
  while (i <= Mid) {
    b[k++] = a[i++];
  }
  while (j <= End) {
    b[k++] = a[j++];
  }
  for (int i = Sta; i <= End; i++) {
    a[i] = b[i];
  }
}

void MergeCount(int Sta, int End) {
  if (Sta < End) {
    int Mid = (Sta + End) / 2;
    MergeCount(Sta, Mid);
    MergeCount(Mid + 1, End);
    Count(Sta, Mid, End);
  }
}

int main() {
  int n;
  cin >> n;
  ans = 0;
  for (int i = 1; i <= n; ++i) {
    cin >> a[i];
  }
  MergeCount(1, n);
  cout << ans << endl;
  return 0;
}