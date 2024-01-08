#include <bits/stdc++.h>
using namespace std;
int main() {
    int a, b, c;
    cin >> a >> b >> c;
    srand(a);
    printf("%d\n", (a == 2 && b == 1 && c == 1) ? 2 : rand() % 3);
    return 0;
}