#include <cstdio>
#include <iostream>
int main() {
  int n;
  scanf("%d", &n);
  printf("%d\n", std::max(1, n - 2));
  return 0;
}