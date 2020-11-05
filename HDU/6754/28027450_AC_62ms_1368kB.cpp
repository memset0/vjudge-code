#include <bits/stdc++.h>

const int mod = 998244353;

inline int read() {
    char c; int x; for (c = getchar(); !isdigit(c); c = getchar());
    for (x = 0; isdigit(c); c = getchar()) { x = x * 10 + c - '0'; } return x;
}

int n;

int main() {
    for (int T = read(); T; T--) {
        n = read();
        if (n == 1) {
            printf("26\n");
        } else if (n == 2) {
            printf("676\n");
        } else if (n == 3) {
            printf("17576\n");
        } else {
            printf("15600\n");
        }
    }
    return 0;
}