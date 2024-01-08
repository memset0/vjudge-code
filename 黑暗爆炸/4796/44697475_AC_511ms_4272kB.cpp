#include <cstdio>
#include <iostream>
using namespace std;
const int N = 3e5 + 5;
int n, a[N], ans[N];
int opt[] = {1, 2, 0, 1, 0, 0, 0, 2, 2, 0, 0, 0, 1, 0, 2, 1};
void read(){
    char ch = getchar();
    while (isdigit(ch)){
        a[++n] = ch ^ 48;
        ch = getchar();
    }
}
int main(){
    read();
    n /= 3;
    for (int i = 0; i < n; i++){
        int t, x = 3 * i;
        t = (a[x] << 3) + (a[x + 1] << 2) + (a[x + 2] << 1) + a[x + 3];
        if (opt[t]){
            ans[++*ans] = x + opt[t];
            a[x + opt[t]] ^= 1, a[x + opt[t] + 1] ^= 1;
        }
    }
    printf("%d\n", *ans);
    for (int i = 1; i <= *ans; i++) printf("%d ", ans[i]);
    return 0;
}