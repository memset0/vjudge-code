#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, k;
	scanf("%d%d", &n, &k);
    if (n == 0 || (n == 1 && (k & 1) == 0))
        puts("Austin");
    else
        puts("Adrien");
    return 0;
}