#include <bits/stdc++.h>

int a, b, c, d;

int main() {
    std::cin >> a >> b >> c >> d;
    printf("%d\n", a == d && (!c || (c && a)));
}