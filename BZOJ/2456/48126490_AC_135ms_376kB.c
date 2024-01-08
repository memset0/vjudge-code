#include <stdio.h>
int n, ans = -1, cnt = 1, x, c;
void read(int *x) {
  *x = 0;
  c = getchar();
  while ('0' <= c && c <= '9') {
    *x = *x * 10 + c - '0';
    c = getchar();
  }
}
int main() {
  read(&n);
  while (n--) {
    read(&x);
    if (x == ans) cnt++;
    else
      cnt--;
    if (cnt == 0) {
      ans = x;
      cnt = 1;
    }
  }
  printf("%d\n", ans);
}