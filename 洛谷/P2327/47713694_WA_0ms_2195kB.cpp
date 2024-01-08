#include <bits/stdc++.h>
using namespace std;
int main() {
    int n; cin>>n;
    srand(n);
    printf("%d\n", rand() % 3);
    return 0;
}