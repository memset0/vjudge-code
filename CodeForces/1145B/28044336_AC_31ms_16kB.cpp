#include<bits/stdc++.h>

int n, a[10];
int main() {
    a[1] = a[7] = a[9] = 1;
    std::cin >> n;
    if ((a[n % 10] || (n > 9 && n < 30) || a[n / 10]) && n != 12)
        std::cout << "NO" << std::endl;
    else
        std::cout << "YES" << std::endl;
}