#include <bits/stdc++.h>
using namespace std;

int main() {
  int a, b, c;
  while (scanf("%d%d%d", &a, &b, &c) == 3) {
    printf(b - c + a <= 0 ? "Props win!\n" : "Hunters win!\n");
  }
}