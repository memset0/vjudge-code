#include <bits/stdc++.h>

const int N = 1e4 + 5;

int n, a[N];
std::set<int> set;

int main() {
    scanf("%d", &n);
    n--;
    a[1] = 1;
    set.insert(1);
    for (int i = 2; i <= n; i++) {
        for (a[i] = a[i - 1] + 1; ; a[i]++) {
            int sum = 0;
            for (int j = i; j >= 1; j--) {
                sum += a[j];
                if (set.count(sum)) { sum = -1; break; }
            }
            if (sum != -1) {
                sum = 0;
                for (int j = i; j >= 1; j--) {
                    sum += a[j];
                    set.insert(sum);
                }
                break;
            }
        }
    }
    printf("%d\n", n);
    for (int i = 1; i <= n; i++) {
        printf("%d %d %d\n", i, i + 1, a[i]);
    }
    return 0;
}