#include <cstdio>
#include <cstring>
#include <iostream>
using namespace std;
int main() {
  int n, N, f1, f2;
  int a[200]; // 走廊编号
  cin >> n;
  while (n--) {
    cin >> N;
    memset(a, 0, sizeof(a));
    for (int i = 0; i < N; i++) {
      cin >> f1 >> f2;
      f1 = (f1 - 1) / 2; // 将房间号转换为走廊号
      f2 = (f2 - 1) / 2;
      if (f1 > f2) {
        swap(f1, f2);
      }
      for (int j = f1; j <= f2; j++) {
        a[j]++;
      }
    }
    int Max = -1;
    for (int i = 0; i < 200; i++) {
      if (a[i] > Max) {
        Max = a[i];
      }
    }
    cout << Max * 10 << endl;
  }
  return 0;
}